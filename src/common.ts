import { PathLike } from "fs";
import { stat } from "fs/promises";
import { delimiter, join } from "path";
import { Terminal } from "vscode";
import { LanguageClient } from "vscode-languageclient/node";

export enum Executables {
  Fysh = "fysh",
  FyshLS = "fyshls",
}

export enum FyshCommands {
  ExecInTerminal = "fysh.execInTerminal",
  InstallFysh = "fysh.installFysh",
}

export type ExtensionState = {
  terminal?: Terminal;
  client?: LanguageClient;
  binPath: string;
};

export const state: ExtensionState = {
  binPath: "",
};

/**
 * Easy executable check (cross-platform!)
 * https://abdus.dev/posts/checking-executable-exists-in-path-using-node/
 * @param {string} exe executable name (without extension if on Windows)
 * @return {Promise<string|null>} executable path if found
 * */
export async function findExecutable(
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
