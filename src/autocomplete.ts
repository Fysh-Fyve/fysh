/**
 * Put together by Jippity and dreams
 */
import {
  commands,
  ExtensionContext,
  Position,
  Range,
  TextDocument,
  TextEditor,
  TextLine,
  window,
  workspace,
} from "vscode";

export function activateAutocomplete(context: ExtensionContext) {
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
