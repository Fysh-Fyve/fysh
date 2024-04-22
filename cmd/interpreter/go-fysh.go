package main

import (
	"fmt"
	"io"
	"log"
	"os"

	"github.com/cbebe/go-fysh/parser"
	"github.com/cbebe/go-fysh/scanner"
)

func main() {
	stdin, err := io.ReadAll(os.Stdin)
	if err != nil {
		log.Fatal(err)
	}
	s := scanner.New(string(stdin))
	p := parser.New(s)
	prog, err := p.Parse()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Print(prog.TopLevels)
}
