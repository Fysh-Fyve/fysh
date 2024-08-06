package ast

import (
	"bytes"
	"fmt"

	"github.com/Fysh-Fyve/fysh/src/ast/binary"
	"github.com/Fysh-Fyve/fysh/src/fysh"
)

type ExpressionStatement struct{ Expr Expression }

func (e *ExpressionStatement) top()            {}
func (e *ExpressionStatement) statement()      {}
func (e *ExpressionStatement) Literal() string { return e.Expr.String() }
func (e *ExpressionStatement) String() string {
	return fmt.Sprintf("%s%s", e.Expr, fysh.Water)
}

type IncrementStatement struct{ Expr Expression }

func (i *IncrementStatement) top()            {}
func (i *IncrementStatement) statement()      {}
func (i *IncrementStatement) Literal() string { return fysh.Inc.String() }
func (i *IncrementStatement) String() string {
	return fmt.Sprintf("%s%s%s", i.Expr, fysh.Inc, fysh.Water)
}

type DecrementStatement struct{ Expr Expression }

func (d *DecrementStatement) top()            {}
func (d *DecrementStatement) statement()      {}
func (d *DecrementStatement) Literal() string { return fysh.Dec.String() }
func (d *DecrementStatement) String() string {
	return fmt.Sprintf("%s%s%s", d.Expr, fysh.Dec, fysh.Water)
}

type AssignmentStatement struct {
	Left  Expression
	Right Expression
}

func (a *AssignmentStatement) top()            {}
func (a *AssignmentStatement) statement()      {}
func (a *AssignmentStatement) Literal() string { return fysh.OpenFysh.String() }
func (a *AssignmentStatement) String() string {
	return fmt.Sprintf("%s %s %s%s", a.Left, fysh.Assign, a.Right, fysh.Water)
}

type BlockStatement struct{ Statements []Statement }

func (b *BlockStatement) top()            {}
func (b *BlockStatement) statement()      {}
func (b *BlockStatement) Literal() string { return fysh.OpenFysh.String() }
func (b *BlockStatement) String() string {
	var out bytes.Buffer
	out.WriteString(fysh.OpenFysh.String())
	for i, s := range b.Statements {
		if i == 0 {
			out.WriteString("\n")
		}
		out.WriteString(s.String())
		out.WriteString("\n")
	}
	out.WriteString(fysh.CloseFysh.String())
	return out.String()
}

type ReturnStatement struct{ Expr Expression }

func (r *ReturnStatement) top()            {}
func (r *ReturnStatement) statement()      {}
func (r *ReturnStatement) Literal() string { return fysh.Squid.String() }
func (r *ReturnStatement) String() string {
	return fmt.Sprintf("%s %s%s", fysh.Squid, r.Expr, fysh.Water)
}

type BreakStatement struct{}

func (r *BreakStatement) top()            {}
func (r *BreakStatement) statement()      {}
func (r *BreakStatement) Literal() string { return fysh.BreakFysh.String() }
func (r *BreakStatement) String() string {
	return fmt.Sprintf("%s%s", fysh.BreakFysh, fysh.Water)
}

type IfStatement struct {
	Cond Expression
	Then *BlockStatement
	Else *BlockStatement
}

func (b *IfStatement) top()            {}
func (b *IfStatement) statement()      {}
func (b *IfStatement) Literal() string { return fysh.If.String() }
func (b *IfStatement) String() string {
	var out bytes.Buffer
	fmt.Fprintf(&out, "%s %s%s%s ", fysh.If, fysh.LBowl, b.Cond, fysh.RBowl)
	out.WriteString(b.Then.String())
	if b.Else != nil {
		fmt.Fprintf(&out, " %s %s", fysh.Else, b.Else)
	}
	return out.String()
}

type LoopStatement struct {
	Cond Expression
	Body *BlockStatement
}

func (l *LoopStatement) top()            {}
func (l *LoopStatement) statement()      {}
func (l *LoopStatement) Literal() string { return fysh.Loop.String() }
func (l *LoopStatement) String() string {
	var out bytes.Buffer
	fmt.Fprintf(&out, "%s %s%s%s ", fysh.Loop, fysh.LBowl, l.Cond, fysh.RBowl)
	out.WriteString(l.Body.String())
	return out.String()
}

type AnchorStatement struct {
	Op    binary.Op
	Right Expression
}

func (a *AnchorStatement) top()            {}
func (a *AnchorStatement) statement()      {}
func (a *AnchorStatement) Literal() string { return a.Op.String() }
func (a *AnchorStatement) String() string {
	return fmt.Sprintf("%s %s%s", a.Op, a.Right, fysh.Water)
}

var _ Statement = &BlockStatement{}
var _ Statement = &ReturnStatement{}
var _ Statement = &IfStatement{}
var _ Statement = &LoopStatement{}
var _ Statement = &AssignmentStatement{}
var _ Statement = &IncrementStatement{}
var _ Statement = &DecrementStatement{}
var _ Statement = &ExpressionStatement{}
var _ Statement = &AnchorStatement{}
