package main

import (
	"strconv"
	"strings"

	protocol "github.com/tliron/glsp/protocol_3_16"
)

func tryNumberCompletion(text string, rang protocol.Range) (protocol.CompletionItem, error) {
	v, err := strconv.ParseInt(strings.TrimSpace(text), 10, 64)
	if err == nil {
		return protocol.CompletionItem{
			Label: text,
			TextEdit: protocol.TextEdit{
				Range:   rang,
				NewText: getFysh(v),
			},
		}, nil
	} else {
		return protocol.CompletionItem{}, err
	}
}
