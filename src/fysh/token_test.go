package fysh_test

import (
	"testing"

	"github.com/Fysh-Fyve/fysh/src/fysh"
)

type nameCase struct {
	fysh   fysh.Fysh
	name   string
	negate bool
}

func TestUnfysh(t *testing.T) {
	tests := []nameCase{
		{fysh.Fysh{Type: fysh.Inc, Value: ">><increment>"}, "increment", false},
		{fysh.Fysh{Type: fysh.Dec, Value: "<decrement><<"}, "decrement", false},
		{fysh.Fysh{Type: fysh.Sub, Value: ">(submarine)"}, "submarine", false},
		{fysh.Fysh{Type: fysh.Sub, Value: "(submarine)<"}, "submarine", true},
		{fysh.Fysh{Type: fysh.Ident, Value: "><positive>"}, "positive", false},
		{fysh.Fysh{Type: fysh.Ident, Value: "<negative><"}, "negative", true},
		{fysh.Fysh{Type: fysh.Scales, Value: "><{{{>"}, "111", false},
		{fysh.Fysh{Type: fysh.Scales, Value: "<{{{><"}, "111", true},
	}

	for i, tt := range tests {
		name, neg := tt.fysh.Unfysh()
		if name != tt.name {
			t.Fatalf("tests[%d] (%s) - name wrong. expected=%q, got=%q",
				i, tt.fysh.Value, tt.name, name)
		}
		if neg != tt.negate {
			t.Fatalf("tests[%d] (%s) - neg wrong. expected=%v, got=%v",
				i, tt.fysh.Value, tt.negate, neg)
		}
	}
}
