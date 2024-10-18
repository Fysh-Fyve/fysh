package repl

import (
	"bufio"
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"log"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/evaluator"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/object"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/parser"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/scanner"
)

const PROMPT = "><> "

type DefaultPrinter struct {
	w io.Writer
}

func NewPrinter(w io.Writer) *DefaultPrinter {
	return &DefaultPrinter{w}
}

func (d *DefaultPrinter) Print(s string) {
	fmt.Fprintln(d.w, s)
}

func Start(in io.Reader, out io.Writer, prompt bool) {
	s := bufio.NewScanner(in)
	env := object.NewEnvironment(NewPrinter(out))

	for {
		if prompt {
			fmt.Fprint(out, PROMPT)
		}
		scanned := s.Scan()
		if !scanned {
			return
		}

		line := s.Bytes()
		l, err := scanner.NewFile("stdin", bytes.NewBuffer(line))
		if err != nil {
			log.Println(err)
			continue
		}
		p := parser.New(l)

		program, err := p.Parse()
		if err != nil {
			log.Println(err)
			continue
		}

		evaluated := evaluator.Eval(program, env)
		if evaluated != nil {
			_, err := io.WriteString(out, evaluated.Inspect())
			if err != nil {
				log.Println(err)
			}
			_, err = io.WriteString(out, "\n")
			if err != nil {
				log.Println(err)
			}
		}
	}
}

func StartParse(in io.Reader, out io.Writer, prompt bool) {
	s := bufio.NewScanner(in)
	for {
		if prompt {
			fmt.Fprint(out, PROMPT)
		}
		scanned := s.Scan()
		if !scanned {
			return
		}

		line := s.Bytes()
		l, err := scanner.NewFile("stdin", bytes.NewBuffer(line))
		if err != nil {
			log.Println(err)
			continue
		}
		p := parser.New(l)

		program, err := p.Parse()
		if err != nil {
			log.Println(err)
			continue
		}

		b, err := json.Marshal(program)
		if err != nil {
			log.Println(err)
			continue
		}

		fmt.Println(string(b))
	}
}
