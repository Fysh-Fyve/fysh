package main

import (
	"strconv"
	"strings"

	sitter "github.com/smacker/go-tree-sitter"
	protocol "github.com/tliron/glsp/protocol_3_16"
)

func tryNumberCompletion(text string, start, end sitter.Point) (protocol.CompletionItem, error) {
	v, err := strconv.ParseInt(strings.TrimSpace(text), 10, 64)
	if err == nil {
		return protocol.CompletionItem{
			Label: text,
			TextEdit: protocol.TextEdit{
				Range: protocol.Range{
					Start: toPosition(start),
					End:   toPosition(end),
				},
				NewText: getFysh(v),
			},
		}, nil
	} else {
		return protocol.CompletionItem{}, err
	}
}
