package repl

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"log"

	"github.com/Fysh-Fyve/fysh/src/evaluator"
	"github.com/Fysh-Fyve/fysh/src/object"
	"github.com/Fysh-Fyve/fysh/src/parser"
	"github.com/Fysh-Fyve/fysh/src/scanner"
)

const PROMPT = "><> "

func Start(in io.Reader, out io.Writer, prompt bool) {
	s := bufio.NewScanner(in)
	env := object.NewEnvironment()

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
