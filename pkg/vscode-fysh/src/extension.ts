import { ExtensionContext } from "vscode";
import { FyshUtils } from "./utils";

let utils: FyshUtils;

export async function activate(context: ExtensionContext) {
  const utils = new FyshUtils(context);
  await utils.initialize();
}

export function deactivate(): Thenable<void> | undefined {
  return utils?.dispose();
}
