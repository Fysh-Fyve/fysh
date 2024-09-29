import {
  createConnection,
  TextDocuments,
  Diagnostic,
  DiagnosticSeverity,
  ProposedFeatures,
  InitializeParams,
  DidChangeConfigurationNotification,
  CompletionItem,
  CompletionItemKind,
  TextDocumentPositionParams,
  TextDocumentSyncKind,
  InitializeResult,
  Connection,
} from "vscode-languageserver/node";

import { TextDocument } from "vscode-languageserver-textdocument";

import Parser, { type Tree } from "web-tree-sitter";
import { join, relative } from "path";

class FyshLS {
  #parser = new Parser();
  #trees = new Map<string, Tree>();

  async initialize(connection: Connection, params: InitializeParams) {
    await Parser.init();
    const pathToFyshWASM = relative(
      process.cwd(),
      join(__dirname, "..", "tree-sitter-fysh.wasm")
    );
    connection.console.info(
      `Loading Tree Sitter Fysh WASM from ${pathToFyshWASM}`
    );
    const language = await Parser.Language.load(pathToFyshWASM);
    this.#parser.setLanguage(language);

    const result: InitializeResult = {
      serverInfo: {
        name: "fyshls",
      },
      capabilities: {
        textDocumentSync: TextDocumentSyncKind.Full,
      },
    };
    if (params.capabilities.textDocument.definition) {
      result.capabilities.definitionProvider = true;
    }
    if (params.capabilities.textDocument.completion) {
      result.capabilities.completionProvider = {
        triggerCharacters: [
          "0",
          "1",
          "2",
          "3",
          "4",
          "5",
          "6",
          "7",
          "8",
          "9",
          "-",
          "^",
          "*",
        ],
      };
    }
    if (params.capabilities.textDocument.hover) {
      result.capabilities.hoverProvider = true;
    }
    return result;
  }
}

function initialize() {
  // Create a connection for the server, using Node's IPC as a transport.
  // Also include all preview / proposed LSP features.
  const connection = createConnection(ProposedFeatures.all);
  const fyshLS = new FyshLS();
  connection.onInitialize((params) => fyshLS.initialize(connection, params));

  const documents = new TextDocuments(TextDocument);

  documents.onDidOpen((doc) => {
    doc.document.uri;
  });

  documents.listen(connection);

  connection.listen();
}

initialize();
