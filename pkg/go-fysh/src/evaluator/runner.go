package evaluator

import (
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/object"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/parser"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/scanner"
)

type EvalError struct {
	obj object.Object
}

func (e *EvalError) Error() string {
	return e.obj.Inspect()
}

func GoFysh(input string, printer object.Printer) error {
	env := object.NewEnvironment(printer)
	l := scanner.NewFileFromString(input)
	p := parser.New(l)

	program, err := p.Parse()
	if err != nil {
		return err
	}

	evaluated := Eval(program, env)
	if object.IsError(evaluated) {
		return &EvalError{evaluated}
	}

	return nil
}
