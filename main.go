package main

import (
	"log"

	"github.com/tliron/glsp"
	protocol "github.com/tliron/glsp/protocol_3_16"
	"github.com/tliron/glsp/server"
)

var version string = "0.0.1"

type FyshLs struct {
	name    string
	version string
	handler protocol.Handler
}

func NewFyshLs() *FyshLs {
	ls := &FyshLs{}

	ls.handler = protocol.Handler{
		Initialize:                     ls.initialize,
		Shutdown:                       ls.shutdown,
		TextDocumentCompletion:         ls.completion,
		TextDocumentSemanticTokensFull: ls.semanticTokensFull,
	}
	return ls
}
func (ls *FyshLs) completion(
	context *glsp.Context,
	params *protocol.CompletionParams,
) (any, error) {
	// TODO: complete??
	log.Println("completion", params.TextDocument.URI)
	return []protocol.CompletionItem{}, nil
}

func (ls *FyshLs) semanticTokensFull(
	context *glsp.Context,
	params *protocol.SemanticTokensParams,
) (*protocol.SemanticTokens, error) {
	log.Println("semantic", params.TextDocument.URI)
	return &protocol.SemanticTokens{
		Data: []protocol.UInteger{},
	}, nil
}

func (ls *FyshLs) initialize(
	context *glsp.Context,
	params *protocol.InitializeParams,
) (any, error) {
	capabilities := ls.handler.CreateServerCapabilities()

	capabilities.CompletionProvider = &protocol.CompletionOptions{
		TriggerCharacters: []string{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-"},
	}
	capabilities.SemanticTokensProvider = &protocol.SemanticTokensOptions{
		Full: true,
	}

	return protocol.InitializeResult{
		Capabilities: capabilities,
		ServerInfo: &protocol.InitializeResultServerInfo{
			Name:    ls.name,
			Version: &ls.version,
		},
	}, nil
}

func (ls *FyshLs) shutdown(context *glsp.Context) error {
	return nil
}

func (ls *FyshLs) RunStdio() {
	log.Println("Starting server...")
	server := server.NewServer(&ls.handler, ls.name, true)
	server.RunStdio()
}

func main() {
	fysh := NewFyshLs()
	fysh.RunStdio()
}
