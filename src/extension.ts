import { join } from "path";
import { ExtensionContext } from "vscode";
import {
  Executable,
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind,
} from "vscode-languageclient/node";
import { activateAutocomplete } from "./autocomplete";
import { findExecutable, state } from "./common";
import { installFysh } from "./install";
import { execInterminal } from "./terminal";

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
