package queries

import (
	_ "embed"
)

//go:embed highlights.scm
var Highlights []byte

//go:embed injections.scm
var Injections []byte
