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

func Encode(sourceCode []byte, n *sitter.Tree) []protocol.UInteger {
	q, err := sitter.NewQuery(highlights, fysh.GetLanguage())
	if err != nil {
		panic(err)
	}
	qc := sitter.NewQueryCursor()
	qc.Exec(q, n.RootNode())

	x := []protocol.UInteger{}
	first := true
	var lastLine, lastStart uint32

	_, mTyp := support.GetTokenTypes()
	for {
		m, ok := qc.NextMatch()
		if !ok {
			break
		}
		// Apply predicates filtering
		m = qc.FilterPredicates(m, sourceCode)
		for _, c := range m.Captures {
			curLine, curStart := fromPoint(c.Node.StartPoint())
			// // We can't re-apply highlighting...
			// if curLine == lastLine && curStart == lastStart {
			// 	continue
			// }
			// JK we can and we will!

			var typ uint32
			switch q.CaptureNameForId(c.Index) {
			case "comment":
				typ = mTyp[protocol.SemanticTokenTypeComment]
			case "spell":
				// Also comment
				typ = mTyp[protocol.SemanticTokenTypeComment]
			case "type":
				// Positive identifier
				typ = mTyp[protocol.SemanticTokenTypeClass]
			case "type.definition":
				// Negative identifier
				typ = mTyp[protocol.SemanticTokenTypeEnum]
			case "punctuation.special":
				// One
				typ = mTyp[protocol.SemanticTokenTypeNumber]
			case "constant":
				// Zero
				typ = mTyp[protocol.SemanticTokenTypeString]
			case "punctuation.bracket":
				// Bracket
				typ = mTyp[protocol.SemanticTokenTypeRegexp]
			case "keyword":
				typ = mTyp[protocol.SemanticTokenTypeKeyword]
			case "operators":
				typ = mTyp[protocol.SemanticTokenTypeOperator]
			}
			line, start := curLine, curStart
			if !first {
				line -= lastLine
				if line == 0 {
					start -= lastStart
				}
			} else {
				first = !first
			}
			tokLen := c.Node.EndByte() - c.Node.StartByte()
			x = append(x, line, start, tokLen, typ, 0)
			lastLine, lastStart = curLine, curStart
		}
	}

	return x
}
