package tree_sitter_fysh

// #include "src/parser.c"
// // NOTE: if your language has an external scanner, add it here.
// #include "src/scanner.c"
import "C"

import (
	"unsafe"

	sitter "github.com/smacker/go-tree-sitter"
)

func GetLanguage() *sitter.Language {
	return sitter.NewLanguage(Language())

}

// Get the tree-sitter Language for this grammar.
func Language() unsafe.Pointer {
	return unsafe.Pointer(C.tree_sitter_fysh())
}
