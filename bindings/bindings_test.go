package bindings_test

import (
	"context"
	_ "embed"
	"testing"

	fysh "github.com/Fysh-Fyve/fyshls/bindings"
	sitter "github.com/smacker/go-tree-sitter"
	"github.com/stretchr/testify/assert"
)

//go:embed add.fysh
var addFysh []byte

func TestGrammar(t *testing.T) {
	assert := assert.New(t)

	n, err := sitter.ParseCtx(context.Background(), addFysh, fysh.GetLanguage())
	assert.NoError(err)
	assert.Equal(
		"(source_file "+
			"(multiline_comment) "+
			"(assignment_statement "+
			"left: (positive_ident) "+
			"right: (positive_literal (scales (one) (one)))) "+
			"(expression_statement "+
			"(binary_expression "+
			"(addition left: (binary_expression "+
			"(addition left: (binary_expression "+
			"(addition left: (binary_expression "+
			"(addition left: (binary_expression "+
			"(addition left: (positive_literal (scales (one) (one) (one))) "+
			"right: (positive_literal (scales (one) (one))))) "+
			"right: (positive_literal (scales (one) (one) (one))))) "+
			"right: (negative_literal (scales (one) (zero))))) "+
			"(comment) "+
			"right: (binary_expression "+
			"left: (positive_literal (scales (one) (one))) "+
			"right: (positive_literal (scales (one) (one)))))) "+
			"right: (positive_ident)))) "+
			"(comment))",
		n.String(),
	)
}
