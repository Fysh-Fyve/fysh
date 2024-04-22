package main

import (
	"fmt"
	"io"
	"log"
	"os"
	"os/user"

	"golang.org/x/term"

	"github.com/cbebe/go-fysh/evaluator"
	"github.com/cbebe/go-fysh/object"
	"github.com/cbebe/go-fysh/parser"
	"github.com/cbebe/go-fysh/repl"
	"github.com/cbebe/go-fysh/scanner"
)

func main() {
	atty := term.IsTerminal(int(os.Stdin.Fd()))
	if atty && len(os.Args) <= 1 {
		user, err := user.Current()
		if err != nil {
			panic(err)
		}
		fmt.Printf("Hello %s! This is the Fysh programming language!\n",
			user.Username)
		fmt.Printf("Feel free to type in commands.\n")
		repl.Start(os.Stdin, os.Stdout, atty)
	} else {
		env := object.NewEnvironment()
		l := scanner.New(string(getInput()))
		p := parser.New(l)

		program, err := p.Parse()
		if err != nil {
			log.Fatal(err)
		}

		evaluated := evaluator.Eval(program, env)
		if object.IsError(evaluated) {
			io.WriteString(os.Stdout, evaluated.Inspect())
			io.WriteString(os.Stdout, "\n")
			os.Exit(1)
		}
	}
}

func getInput() []byte {
	var b []byte
	var err error
	if len(os.Args) > 1 {
		b, err = os.ReadFile(os.Args[1])
	} else {
		b, err = io.ReadAll(os.Stdin)
	}
	if err != nil {
		panic(err)
	}

	return b
}
