package server_test

import (
	_ "embed"
	"fmt"
	"testing"

	"github.com/Fysh-Fyve/fysh/pkg/fyshls/server"
	"github.com/stretchr/testify/assert"
)

//go:embed add.fysh
var SOURCE_CODE []byte

func TestHighlight(t *testing.T) {
	assert := assert.New(t)

	n, err := server.GetTree(SOURCE_CODE)
	assert.NoError(err)
	x := server.Encode(SOURCE_CODE, n)
	expected := 25
	if len(x)/5 != expected {
		var lineNum uint32 = 0
		fmt.Println(len(x) / 5)
		for i := 0; i < len(x)/5; i++ {
			lineNum += x[i*5]
			fmt.Println(lineNum, x[i*5:i*5+5])
		}
		assert.Fail("incorrect number of tokens")
	}
}
