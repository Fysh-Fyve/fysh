import AdmZip from "adm-zip";
import { spawn } from "child_process";
import { createHash } from "crypto";
import type { PathLike } from "fs";
import { createReadStream } from "fs";
import { mkdir, stat, writeFile } from "fs/promises";
import { delimiter, extname, join } from "path";
import type { Terminal, Uri } from "vscode";
import {
  ConfigurationTarget,
  ExtensionContext,
  ProgressLocation,
  commands,
  window,
  workspace,
} from "vscode";
import {
  Executable,
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind,
} from "vscode-languageclient/node";

const exe = "fysh";

type ExtensionState = {
  terminal?: Terminal;
  client?: LanguageClient;
  binPath: string;
};

function installFysh(state: ExtensionState) {
  async function commandHandler() {
    if (await findExecutable(exe, state.binPath)) {
      window.showInformationMessage(`${exe} is installed!`);
      return;
    }
    await mkdir(state.binPath, { recursive: true });
    await install(state.binPath);
  }

  return commands.registerCommand(FyshCommands.InstallFysh, commandHandler);
}

async function promptInstall(context: ExtensionContext, state: ExtensionState) {
  const res = await window.showWarningMessage(
    `${exe}, the Fysh interpreter, was not found, would you like to install it from GitHub?`,
    "Install",
    "Do not show again"
  );
  if (res === "Do not show again") {
    window.showInformationMessage(
      `If you change your mind, ${exe} can be installed from the command prompt.`
    );
    return context.globalState.update("promptInstall", false);
  } else if (res === "Install") {
    return commands.executeCommand(FyshCommands.InstallFysh, state);
  }
}

function q(s: string): string {
  if (s.includes(" ")) {
    return `"${s}"`;
  } else {
    return s;
  }
}

function execInterminal(context: ExtensionContext, state: ExtensionState) {
  async function commandHandler(file: Uri) {
    const executable = await findExecutable(exe, state.binPath);
    if (!executable) {
      if (context.globalState.get("promptInstall") === false) {
        throw new Error(`${exe} not found!`);
      }
      return promptInstall(context, state);
    }

    // TODO: Make sending commands more robust. See vscode-python for example.
    if (!state.terminal || state.terminal?.exitStatus) {
      if (state.terminal?.exitStatus) {
        state.terminal.dispose();
      }
      state.terminal = window.createTerminal({ name: "Fysh" });
    }
    state.terminal.show();
    state.terminal.sendText(`${q(executable)} ${q(file.fsPath)}`);
  }

  return commands.registerCommand(FyshCommands.ExecInTerminal, commandHandler);
}

type OSArch = `${typeof process.platform}-${typeof process.arch}`;

function findExecutableOSArch(): string {
  const valid = {
    "darwin-arm64": "darwin-arm64",
    "darwin-x64": "darwin-amd64",
    "linux-ia32": "linux-386",
    "linux-x64": "linux-amd64",
    "win32-ia32": "windows-386",
    "win32-x64": "windows-amd64",
  } satisfies Partial<Record<OSArch, string>>;
  const platform = `${process.platform}-${process.arch}` as const;
  if (!(platform in valid)) {
    throw new Error(
      `Unsupported platform '${platform}'. Must compile interpreter with Go.`
    );
  }
  return valid[platform];
}

function calculateMD5Hash(filePath: string) {
  return new Promise<string>((resolve, reject) => {
    const hash = createHash("md5");
    const stream = createReadStream(filePath);

    stream.on("data", (data) => {
      hash.update(data);
    });

    stream.on("end", () => {
      resolve(hash.digest("hex"));
    });

    stream.on("error", (err) => {
      reject(err);
    });
  });
}

async function install(binPath: string) {
  await window.withProgress(
    {
      location: ProgressLocation.Notification,
      title: "Installing Fysh",
      cancellable: false,
    },
    (progress) => installWithProgress(progress, binPath)
  );
  window.showInformationMessage(`${exe} was installed!`);
}

type Progress = Parameters<Parameters<typeof window.withProgress>[1]>[0];
async function installWithProgress(progress: Progress, binPath: string) {
  progress.report({ increment: 0 });
  const osArch = findExecutableOSArch();
  progress.report({ increment: 10, message: "Fetching latest release..." });
  const assets = await fetch(
    "https://api.github.com/repos/Fysh-Fyve/fysh/releases/latest"
  )
    .then((res) => res.json())
    .then((res) => {
      if (
        typeof res === "object" &&
        "assets" in res &&
        Array.isArray(res.assets)
      ) {
        return res.assets;
      } else {
        throw new Error("No assets!");
      }
    })
    .then((assets) => assets.filter((a) => a.name.includes(osArch)));

  const md5Hash = await fetch(
    assets.filter((a) => a.name.includes("md5"))[0].browser_download_url
  )
    .then((res) => res.text())
    .then((hash) => hash.trim());

  const archive: { name: string; browser_download_url: string } = assets.filter(
    (a) => !a.name.includes("md5")
  )[0];
  progress.report({ increment: 10, message: "Fetching executable archive..." });

  const buffer = await fetch(archive.browser_download_url)
    .then((r) => r.blob())
    .then((r) => r.arrayBuffer())
    .then((b) => Buffer.from(b));

  const archivePath = join(binPath, archive.name);
  progress.report({ increment: 50, message: "Saving executable archive..." });
  const fileHash = await writeFile(archivePath, buffer).then(() =>
    calculateMD5Hash(archivePath)
  );

  progress.report({ increment: 55, message: "Checking archive integrity..." });

  if (fileHash !== md5Hash) {
    throw new Error("File did not pass integrity check!");
  }

  if (extname(archivePath) === "zip") {
    progress.report({
      increment: 90,
      message: "Extracting executable from zipfile...",
    });
    const zip = new AdmZip(archivePath);
    zip.extractEntryTo(exe, binPath, false, true);
  } else {
    // tar.gz
    progress.report({
      increment: 90,
      message: "Extracting executable from tarball...",
    });
    return new Promise<void>((resolve, reject) => {
      const process = spawn("tar", [
        "-C",
        binPath,
        "-x",
        "-z",
        "-f",
        archivePath,
      ]);
      process.on("close", (code) => {
        if (code === 0) {
          resolve();
        } else {
          reject(new Error("tar exited with a non-zero code."));
        }
      });
      process.on("error", (err) => {
        reject(err);
      });
    });
  }
}

async function createLSPClient() {
  if (!(await findExecutable("fyshls"))) {
    return null;
  }

  // If the extension is launched in debug mode then the debug server options are used
  // Otherwise the run options are used
  const executable: Executable = {
    command: "fyshls",
    transport: TransportKind.stdio,
  };
  const serverOptions: ServerOptions = {
    run: executable,
    debug: executable,
  };

  // Options to control the language client
  const clientOptions: LanguageClientOptions = {
    // Register the server for plain text documents
    documentSelector: [{ scheme: "file", language: "fysh" }],
  };

  // Create the language client and start the client.
  const client = new LanguageClient(
    "fyshls",
    "Fysh Language Server",
    serverOptions,
    clientOptions
  );

  return client;
}

enum FyshCommands {
  ExecInTerminal = "fysh.execInTerminal",
  InstallFysh = "fysh.installFysh",
}

import colours from "./fysh.colours.json";

function addPynkHeart() {
  const config = workspace.getConfiguration();
  const tokenRules: { textMateRules?: object[] } = config.get(
    "editor.tokenColorCustomizations"
  );

  const updatedTokenSettings: { textMateRules?: object } = {
    ...tokenRules,
    textMateRules: (tokenRules.textMateRules || []).concat(
      colours["editor.tokenColorCustomizations"].textMateRules
    ),
  };

  config.update(
    "editor.semanticTokenColorCustomizations",
    updatedTokenSettings,
    ConfigurationTarget.Global
  );

  const semanticRules: { rules?: object } = config.get(
    "editor.semanticTokenColorCustomizations"
  );

  const updatedSettings = {
    ...semanticRules,
    // Add or modify settings
    rules: {
      ...semanticRules.rules,
      "enumMember:fysh": { foreground: "#e83d96", bold: true },
    },
  };

  config.update(
    "editor.semanticTokenColorCustomizations",
    updatedSettings,
    ConfigurationTarget.Global
  );
}

const state: ExtensionState = {
  binPath: "",
};

/**
 * Easy executable check (cross-platform!)
 * https://abdus.dev/posts/checking-executable-exists-in-path-using-node/
 * @param {string} exe executable name (without extension if on Windows)
 * @return {Promise<string|null>} executable path if found
 * */
async function findExecutable(
  exe: PathLike,
  ...paths: string[]
): Promise<string | null> {
  const envPath = process.env.PATH || "";
  const envExt = process.env.PATHEXT || "";
  const pathDirs = envPath
    .replace(/["]+/g, "")
    .split(delimiter)
    .filter(Boolean)
    .concat(paths);
  const extensions = envExt.split(";");
  const candidates = pathDirs.flatMap((d) =>
    extensions.map((ext) => join(d, exe + ext))
  );
  try {
    return await Promise.any(candidates.map(checkFileExists));
  } catch (e) {
    return null;
  }

  async function checkFileExists(filePath: string) {
    if ((await stat(filePath)).isFile()) {
      return filePath;
    }
    throw new Error("Not a file");
  }
}

export async function activate(context: ExtensionContext) {
  state.binPath = join(context.globalStorageUri.fsPath, "bin");
  state.client = await createLSPClient();
  // TODO: Maybe ask if they would like to install the LSP
  state.client?.start();
  context.subscriptions.push(
    execInterminal(context, state),
    installFysh(state)
  );
  addPynkHeart();
}

export function deactivate(): Thenable<void> | undefined {
  return state.client?.stop();
}
