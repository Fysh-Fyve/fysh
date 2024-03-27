package main

import (
	"io"

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

// Tries to find the tree-sitter node from `root` in the position `p`
func getNodeFromPosition(
	root *sitter.Node,
	p protocol.Position,
) (*sitter.Node, error) {
	it := sitter.NewIterator(root, sitter.BFSMode)
	r, c := fromPosition(p)
	for {
		n, err := it.Next()
		if err != nil {
			if err == io.EOF {
				return nil, io.EOF
			} else {
				return nil, err
			}
		}
		start, end := n.StartPoint(), n.EndPoint()
		if (r >= start.Row && r <= end.Row) &&
			(r != start.Row || c >= start.Column) &&
			(r != end.Row || c <= end.Column) {
			if n.ChildCount() == 0 {
				// this is the node
				return n, nil
			} else {
				it = sitter.NewIterator(n, sitter.BFSMode)
				// This is the node rn, skip
				it.Next()
			}
		}
	}

}
