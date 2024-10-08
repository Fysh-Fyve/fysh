package main

import (
	"fmt"
	"io"
	"log"
	"os"
	"os/user"

	"golang.org/x/term"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/evaluator"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/object"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/parser"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/repl"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/scanner"
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
		env := object.NewEnvironment(repl.NewPrinter(os.Stdout))
		filename, r, err := getInput()
		if err != nil {
			log.Fatal(err)
		}
		l, err := scanner.NewFile(filename, r)
		if err != nil {
			log.Fatal(err)
		}
		p := parser.New(l)

		program, err := p.Parse()
		if err != nil {
			log.Fatal(err)
		}

		evaluated := evaluator.Eval(program, env)
		if object.IsError(evaluated) {
			if _, err := io.WriteString(os.Stdout, evaluated.Inspect()); err != nil {
				log.Print(err)
			}
			if _, err := io.WriteString(os.Stdout, "\n"); err != nil {
				log.Print(err)
			}
			os.Exit(1)
		}
	}
}

func getInput() (string, io.ReadCloser, error) {
	var filename string
	var r io.ReadCloser
	var err error
	if len(os.Args) > 1 {
		r, err = os.Open(os.Args[1])
		filename = os.Args[1]
	} else {
		r = os.Stdin
		filename = "stdin"
	}
	return filename, r, err
}
