package tree_sitter_fysh

import (
	_ "embed"
)

//go:embed queries/highlights.scm
var Highlights []byte

//go:embed queries/injections.scm
var Injections []byte
