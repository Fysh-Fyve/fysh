package server

import (
	_ "embed"
	"fmt"

	"github.com/Fysh-Fyve/fyshls/support"
	fysh "github.com/Fysh-Fyve/tree-sitter-fysh"
	queries "github.com/Fysh-Fyve/tree-sitter-fysh/queries"
	sitter "github.com/smacker/go-tree-sitter"
	protocol "github.com/tliron/glsp/protocol_3_16"
)

func Encode(sourceCode []byte, n *sitter.Tree) []protocol.UInteger {
	q, err := sitter.NewQuery(queries.Highlights, fysh.GetLanguage())
	if err != nil {
		panic(fmt.Errorf("highlight.scm: %v", err))
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
			case "hearts":
				typ = mTyp[protocol.SemanticTokenTypeEnumMember] // EnumMember is a placeholder since we can't have custom types
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
