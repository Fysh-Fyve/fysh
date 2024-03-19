package main

import (
	"context"
	_ "embed"
	"fmt"
	"log"
	"net/url"
	"os"
	"strings"

	fysh "github.com/Fysh-Fyve/fyshls/bindings"
	sitter "github.com/smacker/go-tree-sitter"
	"github.com/tliron/glsp"
	protocol "github.com/tliron/glsp/protocol_3_16"
	"github.com/tliron/glsp/server"
)

//go:embed tree-sitter-fysh/queries/highlights.scm
var highlights []byte

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
	_ *glsp.Context,
	params *protocol.CompletionParams,
) (any, error) {
	// TODO: complete??
	f, err := openFileFromURI(params.TextDocument.URI)
	if err != nil {
		log.Println(err)
		return nil, err
	}
	log.Println(f)
	return []protocol.CompletionItem{}, nil
}

func (ls *FyshLs) semanticTokensFull(
	_ *glsp.Context,
	params *protocol.SemanticTokensParams,
) (*protocol.SemanticTokens, error) {
	log.Println("semantic", params.TextDocument.URI)
	f, err := openFileFromURI(strings.TrimSpace(params.TextDocument.URI))
	if err != nil {
		log.Println(err)
		return nil, err
	}
	n, err := sitter.ParseCtx(context.Background(), f, fysh.GetLanguage())
	if err != nil {
		log.Println(err)
		return nil, err
	}
	data := []protocol.UInteger{}
	log.Println(n.ChildCount())
	sitter.NewIterator(n, sitter.BFSMode).ForEach(func(node *sitter.Node) error {
		switch node.Type() {
		case "zero":
		case "one":
		}
		return nil
	})
	return &protocol.SemanticTokens{Data: data}, nil
}

func (ls *FyshLs) initialize(
	_ *glsp.Context,
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

func (ls *FyshLs) shutdown(_ *glsp.Context) error {
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

func openFileFromURI(uri string) ([]byte, error) {
	// Parse the URI
	u, err := url.Parse(uri)
	if err != nil {
		return nil, err
	}

	// Check if the scheme is 'file'
	if u.Scheme != "file" {
		return nil, fmt.Errorf("unsupported scheme: %s", u.Scheme)
	}

	// Open the file
	file, err := os.Open(u.Path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	// Read file contents
	fileInfo, err := file.Stat()
	if err != nil {
		return nil, err
	}

	fileSize := fileInfo.Size()
	content := make([]byte, fileSize)
	_, err = file.Read(content)
	if err != nil {
		return nil, err
	}

	return content, nil
}
