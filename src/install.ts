import AdmZip from "adm-zip";
import { spawn } from "child_process";
import { createHash } from "crypto";
import { createReadStream } from "fs";
import { mkdir, writeFile } from "fs/promises";
import { extname, join } from "path";
import { commands, ExtensionContext, ProgressLocation, window } from "vscode";
import { Executables, ExtensionState, findExecutable, FyshCommands } from "./common";

const exe = Executables.Fysh;

export function installFysh(state: ExtensionState) {
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
