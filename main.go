package main

import (
	ctx "context"
	"encoding/json"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"strconv"
	"strings"

	fysh "github.com/Fysh-Fyve/fyshls/bindings"
	"github.com/Fysh-Fyve/fyshls/support"
	"github.com/Fysh-Fyve/fyshls/version"
	sitter "github.com/smacker/go-tree-sitter"
	"github.com/tliron/glsp"
	protocol "github.com/tliron/glsp/protocol_3_16"
	"github.com/tliron/glsp/server"
)

func getLogger(file string) io.WriteCloser {
	if version.LogStderr == "true" && file == "-" {
		return os.Stderr
	} else {
		// file, err := os.CreateTemp(".", "fyshls")
		if file == "-" {
			file = "log.txt"
		}
		f, err := os.Create(file)
		if err != nil {
			panic(err)
		}
		return f
	}
}

func main() {
	file := flag.String("output", "-", "log output destination")
	_ = flag.Bool("stdio", true, "Make VS C*de stop erroring out")
	flag.Parse()
	w := getLogger(*file)
	defer w.Close()
	logger := log.New(w, "[fyshls] ", log.LstdFlags|log.Lshortfile)
	fysh := NewFyshLs(logger)
	fysh.RunStdio()
}

type Server struct {
	name      string
	version   string
	log       *log.Logger
	documents map[string][]byte
	trees     map[string]*sitter.Tree

	handler protocol.Handler
}

func NewFyshLs(logger *log.Logger) *Server {
	s := &Server{
		name:      "fyshls",
		version:   version.BuildVersion(),
		log:       logger,
		documents: map[string][]byte{},
		trees:     map[string]*sitter.Tree{},
	}

	s.handler = protocol.Handler{
		LogTrace:   s.logTrace,
		Initialize: s.initialize,
		Shutdown:   s.shutdown,

		TextDocumentDidOpen:   s.openDocument,
		TextDocumentDidSave:   s.saveDocument,
		TextDocumentDidChange: s.changeDocument,

		TextDocumentHover:      s.hover,
		TextDocumentDefinition: s.definition,
		TextDocumentCompletion: s.completion,

		TextDocumentSemanticTokensFull: s.semanticTokensFull,
	}
	return s
}

func (s *Server) logTrace(context *glsp.Context, params *protocol.LogTraceParams) error {
	s.log.Println(params.Message)
	return nil
}

func getTree(content []byte) (*sitter.Tree, error) {
	p := sitter.NewParser()
	p.SetLanguage(fysh.GetLanguage())
	tree, err := p.ParseCtx(ctx.Background(), nil, content)
	if err != nil {
		return nil, err
	}
	return tree, nil
}

func (s *Server) saveDocument(
	context *glsp.Context,
	params *protocol.DidSaveTextDocumentParams,
) error {
	if params.Text != nil {
		return s.updateDoc(params.TextDocument.URI, *params.Text)
	}
	return nil
}

func (s *Server) definition(
	context *glsp.Context,
	params *protocol.DefinitionParams,
) (any, error) {
	return nil, nil
}

func (s *Server) hover(
	context *glsp.Context,
	params *protocol.HoverParams,
) (*protocol.Hover, error) {
	return nil, nil
}

func (s *Server) updateDoc(uri, text string) error {
	file := []byte(text)
	s.documents[uri] = file
	var err error
	if s.trees[uri], err = getTree(file); err != nil {
		return fmt.Errorf("failed to get root node: %v", err)
	}
	return nil
}

func (s *Server) changeDocument(
	context *glsp.Context,
	params *protocol.DidChangeTextDocumentParams,
) error {
	for _, changes := range params.ContentChanges {
		c, ok := changes.(protocol.TextDocumentContentChangeEventWhole)
		if ok {
			err := s.updateDoc(params.TextDocument.URI, c.Text)
			if err != nil {
				return err
			}
		} else {
			return fmt.Errorf("change event not supported")
		}
	}
	return nil
}

func (s *Server) openDocument(
	context *glsp.Context,
	params *protocol.DidOpenTextDocumentParams,
) error {
	return s.updateDoc(params.TextDocument.URI, params.TextDocument.Text)
}

func getFysh(v int64) string {
	format, zero, one := "><%s°>", "(", "{"
	if v < 0 {
		v, format, zero, one = -v, "<°%s><", ")", "}"
	}
	binary := strconv.FormatInt(v, 2)
	return fmt.Sprintf(
		format,
		strings.ReplaceAll(strings.ReplaceAll(binary, "0", zero), "1", one),
	)
}

func (s *Server) completion(
	context *glsp.Context,
	params *protocol.CompletionParams,
) (any, error) {
	n := s.trees[params.TextDocument.URI]
	it := sitter.NewIterator(n.RootNode(), sitter.BFSMode)
	r, c := fromPosition(params.Position)
	for {
		n, err := it.Next()
		if err != nil {
			if err == io.EOF {
				return []protocol.CompletionItem{}, nil
			} else {
				s.log.Println("completion: error iterating", err)
				return nil, err
			}
		}
		start, end := n.StartPoint(), n.EndPoint()
		if r >= start.Row && r <= end.Row && c >= start.Column && c <= end.Column {
			if n.ChildCount() == 0 {
				// this is the node
				return []protocol.CompletionItem{}, nil
			} else if n.IsError() {
				text := n.Content(s.documents[params.TextDocument.URI])
				completionList := []protocol.CompletionItem{}
				item, err := tryNumberCompletion(text, start, end)
				if err == nil {
					completionList = append(completionList, item)
				}
			} else {
				s.log.Println("completion: new iter: ", n.Content(s.documents[params.TextDocument.URI]))
				it = sitter.NewIterator(n, sitter.BFSMode)
			}
		}
	}
}

func (s *Server) semanticTokensFull(
	context *glsp.Context,
	params *protocol.SemanticTokensParams,
) (*protocol.SemanticTokens, error) {
	data := encode(s.trees[params.TextDocument.URI].RootNode())
	var lineNum uint32 = 0
	for i := 0; i < len(data)/5; i++ {
		lineNum += data[i*5]
		s.log.Println(lineNum, data[i*5:i*5+5])
	}
	return &protocol.SemanticTokens{Data: data}, nil
}

func (s *Server) initialize(
	context *glsp.Context,
	params *protocol.InitializeParams,
) (any, error) {
	capabilities := s.handler.CreateServerCapabilities()

	// FULL sync only
	capabilities.TextDocumentSync = 1
	capabilities.HoverProvider = true
	capabilities.DefinitionProvider = true
	capabilities.CompletionProvider = &protocol.CompletionOptions{
		TriggerCharacters: []string{"0", "1", "2", "3", "4", "5", "6", "7", "8",
			"9", "0", "-"},
	}

	tokenTypes, _ := support.GetTokenTypes()
	tokenModifiers, _ := support.GetTokenModifiers()
	capabilities.SemanticTokensProvider = &protocol.SemanticTokensOptions{
		Full: true,
		Legend: protocol.SemanticTokensLegend{
			TokenTypes:     tokenTypes,
			TokenModifiers: tokenModifiers,
		},
	}

	n, err := json.MarshalIndent(params, "", " ")
	if err != nil {
		s.log.Fatal(err)
	}
	s.log.Println(string(n))

	return protocol.InitializeResult{
		Capabilities: capabilities,
		ServerInfo: &protocol.InitializeResultServerInfo{
			Name:    s.name,
			Version: &s.version,
		},
	}, nil
}

func (s *Server) shutdown(context *glsp.Context) error {
	return nil
}

func (s *Server) RunStdio() {
	s.log.Printf("%s - Starting server...", s.version)
	server := server.NewServer(&s.handler, s.name, true)
	server.RunStdio()
}
