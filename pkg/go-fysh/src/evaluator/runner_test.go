package evaluator_test

import (
	"testing"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/evaluator"
)

type PrinterSpy struct {
	output string
}

func (p *PrinterSpy) Print(s string) {
	p.output = s
}

func TestGoFysh(t *testing.T) {
	p := &PrinterSpy{}
	err := evaluator.GoFysh("(+o ><{> ~", p)
	if err != nil {
		t.Fatal(err)
	}
	if p.output != "1" {
		t.Fatalf("unexpected output. got: %s, want: %s", p.output, "1")
	}
}
