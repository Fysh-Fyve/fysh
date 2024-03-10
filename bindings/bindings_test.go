package bindings_test

import (
	"context"
	"testing"

	fysh "github.com/Fysh-Fyve/fyshls/bindings"
	sitter "github.com/smacker/go-tree-sitter"
	"github.com/stretchr/testify/assert"
)

func TestGrammar(t *testing.T) {
	assert := assert.New(t)

	n, err := sitter.ParseCtx(context.Background(), []byte("><fysh> = ><{{> ~"), fysh.GetLanguage())
	assert.NoError(err)
	assert.Equal(
		"(source_file "+
			"(assignment_statement "+
			"left: (positive_ident (name)) "+
			"right: (positive_literal (scales (one) (one)))))",
		n.String(),
	)
}
