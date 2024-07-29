package repl

import (
	"bufio"
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
			fmt.Fprintf(out, PROMPT)
		}
		scanned := s.Scan()
		if !scanned {
			return
		}

		line := s.Text()
		l := scanner.New(line)
		p := parser.New(l)

		program, err := p.Parse()
		if err != nil {
			log.Println(err)
			continue
		}

		evaluated := evaluator.Eval(program, env)
		if evaluated != nil {
			io.WriteString(out, evaluated.Inspect())
			io.WriteString(out, "\n")
		}
	}
}
