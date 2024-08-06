import AdmZip from "adm-zip";
import { spawn } from "child_process";
import { createHash } from "crypto";
import { createReadStream, PathLike } from "fs";
import { mkdir, stat, writeFile } from "fs/promises";
import { delimiter, extname, join } from "path";
import {
  commands,
  ExtensionContext,
  Position,
  ProgressLocation,
  Range,
  Terminal,
  TextDocument,
  TextEditor,
  TextLine,
  Uri,
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


export async function activate(context: ExtensionContext) {
  state.binPath = join(context.globalStorageUri.fsPath, "bin");
  state.client = await createLSPClient();
  // TODO: Maybe ask if they would like to install the LSP
  state.client?.start();
  context.subscriptions.push(
    execInterminal(context, state),
    installFysh(state)
  );

  activateAutocomplete(context);
}

export function deactivate(): Thenable<void> | undefined {
  return state.client?.stop();
}

enum Executables {
  Fysh = "fysh",
  FyshLS = "fyshls",
}

enum FyshCommands {
  ExecInTerminal = "fysh.execInTerminal",
  InstallFysh = "fysh.installFysh",
}

type ExtensionState = {
  terminal?: Terminal;
  client?: LanguageClient;
  binPath: string;
};

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

async function createLSPClient() {
  if (!(await findExecutable(Executables.FyshLS))) {
    return null;
  }

  // If the extension is launched in debug mode then the debug server options are used
  // Otherwise the run options are used
  const executable: Executable = {
    command: Executables.FyshLS,
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
    Executables.FyshLS,
    "Fysh Language Server",
    serverOptions,
    clientOptions
  );

  return client;
}

const exe = Executables.Fysh;

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

    // Add quotes to text if it contains spaces
    function quote(s: string): string {
      return s.includes(" ") ? `"${s}"` : s;
    }

    state.terminal.sendText(`${quote(executable)} ${quote(file.fsPath)}`);
  }

  return commands.registerCommand(FyshCommands.ExecInTerminal, commandHandler);
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

/**
 * Put together by Jippity and dreams
 */

function activateAutocomplete(context: ExtensionContext) {
  const disposable = commands.registerCommand(
    "extension.convertDecimalToBinary",
    () => {
      const editor = window.activeTextEditor;
      if (!editor) {
        return;
      }

      const { document, selection } = editor;

      const selectedText = document.getText(selection);
      const decimalNumber = Number(selectedText);

      if (isNaN(decimalNumber)) {
        window.showErrorMessage("Selected text is not a valid decimal number.");
        return;
      }

      const binaryNumber = convertDecimalToBinaryString(decimalNumber);

      editor.edit((editBuilder) => {
        editBuilder.replace(selection, binaryNumber);
      });
    }
  );

  context.subscriptions.push(disposable);

  context.subscriptions.push(
    workspace.onDidChangeTextDocument((event) => {
      const editor = window.activeTextEditor;
      if (!editor) {
        return;
      }

      const { document } = editor;
      const position = editor.selection.active;

      if (document === event.document && event.contentChanges.length > 0) {
        const change = event.contentChanges[0];
        const line = document.lineAt(position.line);

        if (isCursorAtEndOfDecimalNumber(document, line, position)) {
          convertLineToBinary(editor, line);
        }
      }
    })
  );

  context.subscriptions.push(
    commands.registerTextEditorCommand(
      "extension.convertLineToBinary",
      (editor) => {
        const document = editor.document;
        const position = editor.selection.active;

        const line = document.lineAt(position.line);
        convertLineToBinary(editor, line);
      }
    )
  );

  context.subscriptions.push(
    commands.registerCommand("type", async ({ text }) => {
      const editor = window.activeTextEditor;
      if (editor) {
        const position = editor.selection.active;
        const line = editor.document.lineAt(position.line);
        if (
          (text === " " || text === "\t") &&
          isCursorAtEndOfDecimalNumber(editor.document, line, position)
        ) {
          await commands.executeCommand("extension.convertLineToBinary");
        }
        await commands.executeCommand("default:type", { text });
      } else {
        await commands.executeCommand("default:type", { text });
      }
    })
  );
}

function isCursorAtEndOfDecimalNumber(
  document: TextDocument,
  line: TextLine,
  position: Position
): boolean {
  const text = line.text;
  const regex = /-?\b\d+\b/g; // Changed regex to handle negative numbers properly
  let match: RegExpExecArray | null;
  while ((match = regex.exec(text)) !== null) {
    const start = line.range.start.translate(0, match.index);
    const end = line.range.start.translate(0, match.index + match[0].length);
    const range = new Range(start, end);
    if (range.end.isEqual(position)) {
      return true;
    }
  }
  return false;
}

function convertDecimalToBinaryString(decimalNumber: number): string {
  let binaryNumber = Math.abs(decimalNumber).toString(2);
  if (decimalNumber < 0) {
    binaryNumber =
      "<°" + binaryNumber.replace(/1/g, "}").replace(/0/g, ")") + "><";
  } else {
    binaryNumber =
      "><" + binaryNumber.replace(/1/g, "{").replace(/0/g, "(") + "°>";
  }
  return binaryNumber;
}

function convertLineToBinary(editor: TextEditor, line: TextLine) {
  const text = line.text;
  const regex = /-?\b\d+\b/g; // Changed regex to handle negative numbers properly
  let match: RegExpExecArray | null;

  const edits = [];

  while ((match = regex.exec(text)) !== null) {
    const decimalNumber = Number(match[0]);
    if (!isNaN(decimalNumber)) {
      const binaryNumber = convertDecimalToBinaryString(decimalNumber);
      const start = line.range.start.translate(0, match.index);
      const end = line.range.start.translate(0, match.index + match[0].length);
      const range = new Range(start, end);
      edits.push({ range, binaryNumber });
    }
  }

  editor.edit((editBuilder) => {
    for (const edit of edits) {
      editBuilder.replace(edit.range, edit.binaryNumber);
    }
  });
}
