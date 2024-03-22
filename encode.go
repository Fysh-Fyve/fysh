package main

import (
	_ "embed"

	fysh "github.com/Fysh-Fyve/fyshls/bindings"
	"github.com/Fysh-Fyve/fyshls/support"
	sitter "github.com/smacker/go-tree-sitter"
	protocol "github.com/tliron/glsp/protocol_3_16"
)

//go:embed tree-sitter-fysh/queries/highlights.scm
var highlights []byte

func (s *Server) highlight(uri string) {
	// TODO: Use this instead to be consistent with tree-sitter
	n := s.trees[uri]
	sourceCode := s.documents[uri]
	q, err := sitter.NewQuery(highlights, fysh.GetLanguage())
	if err != nil {
		panic(err)
	}
	qc := sitter.NewQueryCursor()
	qc.Exec(q, n.RootNode())

	for {
		m, ok := qc.NextMatch()
		if !ok {
			break
		}
		// Apply predicates filtering
		m = qc.FilterPredicates(m, sourceCode)
		for _, c := range m.Captures {
			s.log.Println(q.CaptureNameForId(c.Index), c.Node.Content(sourceCode))
		}
	}
}

func encode(n *sitter.Node) []protocol.UInteger {
	// TODO: Use tree-sitter query instead of manually searching
	data := []protocol.UInteger{}
	var row, column uint32 = 0, 0
	handle := func(t uint32, node *sitter.Node) {
		r, c := fromPoint(node.StartPoint())
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
	_, m := support.GetTokenTypes()
	sitter.NewIterator(n, sitter.DFSMode).ForEach(func(node *sitter.Node) error {
		switch node.Type() {
		case "comment":
			handle(m[protocol.SemanticTokenTypeComment], node)
		case "zero":
			handle(m[protocol.SemanticTokenTypeString], node)
		case "one":
			handle(m[protocol.SemanticTokenTypeNumber], node) // number
		default:
		}
		return nil
	})

	return data
}
