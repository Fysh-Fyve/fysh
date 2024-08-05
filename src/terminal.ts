import { commands, ExtensionContext, Uri, window } from "vscode";
import { Executables, ExtensionState, findExecutable, FyshCommands } from "./common";

const exe = Executables.Fysh;

export function execInterminal(
  context: ExtensionContext,
  state: ExtensionState
) {
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

function promptInstall(context: ExtensionContext, state: ExtensionState) {
    throw new Error("Function not implemented.");
}
