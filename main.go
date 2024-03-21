package main

import (
	ctx "context"
	_ "embed"
	"fmt"
	"io"
	"log"
	"os"

	fysh "github.com/Fysh-Fyve/fyshls/bindings"
	"github.com/Fysh-Fyve/fyshls/version"
	sitter "github.com/smacker/go-tree-sitter"
	"github.com/tliron/glsp"
	protocol "github.com/tliron/glsp/protocol_3_16"
	"github.com/tliron/glsp/server"
)

//go:embed tree-sitter-fysh/queries/highlights.scm
var highlights []byte

func getLogger() io.WriteCloser {
	if version.LogStderr == "true" {
		return os.Stderr
	} else {
		file, err := os.CreateTemp(".", "fyshls")
		if err != nil {
			panic(err)
		}
		return file
	}
}

func main() {
	w := getLogger()
	defer w.Close()
	logger := log.New(w, "[fyshls] ", log.LstdFlags|log.Lshortfile)
	fysh := NewFyshLs(logger)
	fysh.RunStdio()
}

type FyshLS struct {
	name      string
	version   string
	logger    *log.Logger
	documents map[string][]byte
	trees     map[string]*sitter.Node

	handler protocol.Handler
}

func NewFyshLs(logger *log.Logger) *FyshLS {
	ls := &FyshLS{
		name:      "fyshls",
		version:   version.BuildVersion(),
		logger:    logger,
		documents: map[string][]byte{},
		trees:     map[string]*sitter.Node{},
	}

	ls.handler = protocol.Handler{
		LogTrace:   ls.logTrace,
		Initialize: ls.initialize,
		Shutdown:   ls.shutdown,

		TextDocumentDidOpen:   ls.openDocument,
		TextDocumentDidSave:   ls.saveDocument,
		TextDocumentDidChange: ls.changeDocument,

		TextDocumentHover:      ls.hover,
		TextDocumentDefinition: ls.definition,
		TextDocumentCompletion: ls.completion,

		TextDocumentSemanticTokensFull: ls.semanticTokensFull,
	}
	return ls
}

func (ls *FyshLS) logTrace(context *glsp.Context, params *protocol.LogTraceParams) error {
	ls.log(params.Message)
	return nil
}

func getTree(file []byte) (*sitter.Node, error) {
	n, err := sitter.ParseCtx(ctx.Background(), file, fysh.GetLanguage())
	if err != nil {
		return nil, err
	}
	return n, nil
}

func (ls *FyshLS) saveDocument(
	context *glsp.Context,
	params *protocol.DidSaveTextDocumentParams,
) error {
	if params.Text != nil {
		return ls.updateDoc(params.TextDocument.URI, *params.Text)
	}
	return nil
}

func (ls *FyshLS) definition(
	context *glsp.Context,
	params *protocol.DefinitionParams,
) (any, error) {
	return nil, nil
}

func (ls *FyshLS) hover(
	context *glsp.Context,
	params *protocol.HoverParams,
) (*protocol.Hover, error) {
	return nil, nil
}

func (ls *FyshLS) updateDoc(uri, text string) error {
	file := []byte(text)
	ls.documents[uri] = file
	var err error
	if ls.trees[uri], err = getTree(file); err != nil {
		return fmt.Errorf("failed to get root node: %v", err)
	}
	return nil
}

func (ls *FyshLS) changeDocument(
	context *glsp.Context,
	params *protocol.DidChangeTextDocumentParams,
) error {
	for _, changes := range params.ContentChanges {
		c, ok := changes.(protocol.TextDocumentContentChangeEventWhole)
		if ok {
			err := ls.updateDoc(params.TextDocument.URI, c.Text)
			if err != nil {
				return err
			}
		} else {
			return fmt.Errorf("change event not supported")
		}
	}
	return nil
}

func (ls *FyshLS) openDocument(
	context *glsp.Context,
	params *protocol.DidOpenTextDocumentParams,
) error {
	return ls.updateDoc(params.TextDocument.URI, params.TextDocument.Text)
}

func (ls *FyshLS) completion(
	context *glsp.Context,
	params *protocol.CompletionParams,
) (any, error) {
	// TODO: complete??
	return []protocol.CompletionItem{}, nil
}

func (ls *FyshLS) semanticTokensFull(
	context *glsp.Context,
	params *protocol.SemanticTokensParams,
) (*protocol.SemanticTokens, error) {
	n := ls.trees[params.TextDocument.URI]
	data := []protocol.UInteger{}
	var row, column uint32 = 0, 0
	handle := func(t uint32, node *sitter.Node) {
		sp := node.StartPoint()
		r, c := sp.Row, sp.Column
		dRow := r - row
		dCol := c
		if row == r {
			dCol = c - column
		}
		tokLen := node.EndByte() - node.StartByte()
		data = append(data, dRow, dCol, tokLen, t, 0)
		row = r
		column = c
	}
	sitter.NewIterator(n, sitter.BFSMode).ForEach(func(node *sitter.Node) error {
		switch node.Type() {
		case "comment":
			handle(0, node) // comment
		case "zero":
			handle(1, node) // string
		case "one":
			handle(2, node) // number
		default:
			ls.log("unhandled:", node.Type())
		}
		return nil
	})
	for i := 0; i < len(data)/5; i++ {
		ls.log(data[i*5 : i*5+5])
	}
	return &protocol.SemanticTokens{Data: data}, nil
}

func (ls *FyshLS) initialize(
	context *glsp.Context,
	params *protocol.InitializeParams,
) (any, error) {
	capabilities := ls.handler.CreateServerCapabilities()

	// FULL sync only
	capabilities.TextDocumentSync = 1
	capabilities.HoverProvider = true
	capabilities.DefinitionProvider = true
	capabilities.CompletionProvider = &protocol.CompletionOptions{
		TriggerCharacters: []string{"0", "1", "2", "3", "4", "5", "6", "7", "8",
			"9", "0", "-"},
	}
	capabilities.SemanticTokensProvider = &protocol.SemanticTokensOptions{
		Full: true,
		Legend: protocol.SemanticTokensLegend{
			TokenTypes: []string{
				string(protocol.SemanticTokenTypeComment),
				string(protocol.SemanticTokenTypeKeyword),
				string(protocol.SemanticTokenTypeNumber),
			},
			TokenModifiers: []string{},
		},
	}

	// n, err := json.MarshalIndent(params.Capabilities.TextDocument.ColorProvider, "", " ")
	// if err != nil {
	// 	ls.logger.Fatal(err)
	// }
	// ls.log(string(n))

	return protocol.InitializeResult{
		Capabilities: capabilities,
		ServerInfo: &protocol.InitializeResultServerInfo{
			Name:    ls.name,
			Version: &ls.version,
		},
	}, nil
}

func (ls *FyshLS) log(v ...any) {
	ls.logger.Println(v...)
}

func (ls *FyshLS) shutdown(context *glsp.Context) error {
	return nil
}

func (ls *FyshLS) RunStdio() {
	ls.logger.Printf("%s - Starting server...", ls.version)
	server := server.NewServer(&ls.handler, ls.name, true)
	server.RunStdio()
}
