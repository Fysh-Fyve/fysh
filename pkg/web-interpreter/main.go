package main

import (
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/evaluator"
)

var buf [4096]byte

//go:export getBuffer
func getBuffer() *byte {
	return &buf[0]
}

type JSPrinter struct{}

func (JSPrinter) Print(s string) {
	printOut(s)
}

//go:export printError
func printError(s string) // {}

//go:export printOut
func printOut(s string) // {}

//go:export goFysh
func goFysh(s string) {
	if err := evaluator.GoFysh(s, JSPrinter{}); err != nil {
		println("error: ", err.Error())
	}
}

func main() {}
