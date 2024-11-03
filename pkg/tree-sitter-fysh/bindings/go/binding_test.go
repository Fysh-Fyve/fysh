package tree_sitter_fysh_test

import (
	"testing"

	tree_sitter_fysh "github.com/Fysh-Fyve/fysh/pkg/tree-sitter-fysh/bindings/go"
	tree_sitter "github.com/tree-sitter/go-tree-sitter"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_fysh.Language())
	if language == nil {
		t.Errorf("Error loading Fysh grammar")
	}
}
