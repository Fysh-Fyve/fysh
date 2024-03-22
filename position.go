package main

import (
	sitter "github.com/smacker/go-tree-sitter"
	protocol "github.com/tliron/glsp/protocol_3_16"
)

func fromPoint(p sitter.Point) (uint32, uint32) {
	return p.Row, p.Column
}

func fromPosition(p protocol.Position) (uint32, uint32) {
	return p.Line, p.Character
}

func toPosition(p sitter.Point) protocol.Position {
	return protocol.Position{Line: p.Row, Character: p.Column}
}
