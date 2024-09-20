package tree_sitter_fysh_test

import (
	"testing"

	tree_sitter "github.com/smacker/go-tree-sitter"
	"github.com/tree-sitter/tree-sitter-fysh"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_fysh.Language())
	if language == nil {
		t.Errorf("Error loading Fysh grammar")
	}
}
