package fysh_test

import (
	"testing"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/fysh"
)

type nameCase struct {
	fysh   fysh.Fysh
	name   string
	negate bool
}

func TestUnfysh(t *testing.T) {
	tests := []nameCase{
		{fysh.New(fysh.Inc, ">><increment>"), "increment", false},
		{fysh.New(fysh.Dec, "<decrement><<"), "decrement", false},
		{fysh.New(fysh.Sub, ">(submarine)"), "submarine", false},
		{fysh.New(fysh.Sub, "(submarine)<"), "submarine", true},
		{fysh.New(fysh.Ident, "><positive>"), "positive", false},
		{fysh.New(fysh.Ident, "<negative><"), "negative", true},
		{fysh.New(fysh.Scales, "><{{{>"), "111", false},
		{fysh.New(fysh.Scales, "<{{{><"), "111", true},
		{fysh.New(fysh.Scales, "<°{{{><"), "111", true},
		{fysh.New(fysh.Bubbles, "🫧bubbles🫧"), "bubbles", false},
	}

	for i, tt := range tests {
		name, neg := tt.fysh.Unfysh()
		if string(name) != tt.name {
			t.Fatalf("tests[%d] (%s) - name wrong. expected=%q, got=%q",
				i, tt.fysh.Value, tt.name, name)
		}
		if neg != tt.negate {
			t.Fatalf("tests[%d] (%s) - neg wrong. expected=%v, got=%v",
				i, tt.fysh.Value, tt.negate, neg)
		}
	}
}
