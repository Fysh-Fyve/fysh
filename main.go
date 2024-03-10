package main

import (
	"github.com/tliron/glsp"
	protocol "github.com/tliron/glsp/protocol_3_16"
	"github.com/tliron/glsp/server"
)

var version string = "0.0.1"

type FyshLs struct {
	name    string
	version string
	handler protocol.Handler
}

func NewFyshLs() *FyshLs {
	ls := &FyshLs{}

	ls.handler = protocol.Handler{
		Initialize: ls.initialize,
		Shutdown:   ls.shutdown,
	}
	return ls
}

func (ls *FyshLs) initialize(
	context *glsp.Context,
	params *protocol.InitializeParams,
) (any, error) {
	capabilities := ls.handler.CreateServerCapabilities()

	return protocol.InitializeResult{
		Capabilities: capabilities,
		ServerInfo: &protocol.InitializeResultServerInfo{
			Name:    ls.name,
			Version: &ls.version,
		},
	}, nil
}

func (ls *FyshLs) shutdown(context *glsp.Context) error {
	return nil
}

func (ls *FyshLs) RunStdio() {
	server := server.NewServer(&ls.handler, ls.name, true)
	server.RunStdio()
}

func main() {
	fysh := NewFyshLs()
	fysh.RunStdio()
}
