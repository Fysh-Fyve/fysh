package ast

import (
	"bytes"
	"fmt"

	"github.com/Fysh-Fyve/fysh/src/ast/binary"
	"github.com/Fysh-Fyve/fysh/src/ast/unary"
	"github.com/Fysh-Fyve/fysh/src/fysh"
)

type Identifier struct{ Name []byte }

func (i *Identifier) top()            {}
func (i *Identifier) expression()     {}
func (i *Identifier) Literal() string { return fysh.Ident.String() }
func (i *Identifier) String() string  { return string(i.Name) }

type Grilled struct {
}

func (s *Grilled) top()            {}
func (s *Grilled) expression()     {}
func (s *Grilled) Literal() string { return fysh.Grilled.String() }
func (s *Grilled) String() string  { return fysh.Grilled.String() }

type Scales struct{ Value int64 }

func (s *Scales) top()            {}
func (s *Scales) expression()     {}
func (s *Scales) Literal() string { return fysh.Scales.String() }
func (s *Scales) String() string  { return fmt.Sprintf("%d", s.Value) }

type Bones struct{ Value float64 }

func (s *Bones) top()            {}
func (s *Bones) expression()     {}
func (s *Bones) Literal() string { return fysh.Bones.String() }
func (s *Bones) String() string  { return fmt.Sprintf("%f", s.Value) }

type String struct{ Value string }

func (s *String) expression()     {}
func (s *String) Literal() string { return s.Value }
func (s *String) String() string  { return fmt.Sprintf("\"%s\"", s.Value) }

type Unary struct {
	Op    unary.Op
	Right Expression
}

func (u *Unary) top()            {}
func (u *Unary) expression()     {}
func (u *Unary) Literal() string { return u.Op.String() }
func (u *Unary) String() string {
	return fmt.Sprintf("(%s%s)", u.Op, u.Right)
}

type Call struct {
	Callee []byte
	Args   []Expression
}

func (c *Call) top()            {}
func (c *Call) expression()     {}
func (c *Call) Literal() string { return string(c.Callee) }
func (c *Call) String() string {
	var out bytes.Buffer
	fmt.Fprintf(&out, "%s%s", c.Callee, fysh.LBowl)
	for i, p := range c.Args {
		if i != 0 {
			out.WriteString(", ")
		}
		out.WriteString(p.String())
	}
	out.WriteString(fysh.RBowl.String())
	return out.String()
}

type Binary struct {
	Left  Expression
	Op    binary.Op
	Right Expression
}

func (b *Binary) top()            {}
func (b *Binary) expression()     {}
func (b *Binary) Literal() string { return b.Op.String() }
func (b *Binary) String() string {
	return fmt.Sprintf("(%s %s %s)", b.Left, b.Op, b.Right)
}

type Index struct {
	Left  Expression
	Index Expression
}

func (b *Index) top()            {}
func (b *Index) expression()     {}
func (b *Index) Literal() string { return b.Left.Literal() }
func (b *Index) String() string {
	return fmt.Sprintf("%s[%s]", b.Left, b.Index)
}

type Aquarium struct{ Elems []Expression }

func (c *Aquarium) top()            {}
func (c *Aquarium) expression()     {}
func (c *Aquarium) Literal() string { return fysh.LTank.String() }
func (c *Aquarium) String() string {
	var out bytes.Buffer
	out.WriteString(fysh.LTank.String())
	for i, p := range c.Elems {
		if i != 0 {
			out.WriteString(", ")
		}
		out.WriteString(p.String())
	}
	out.WriteString(fysh.RTank.String())
	return out.String()
}

var _ Expression = &Identifier{}
var _ Expression = &Scales{}
var _ Expression = &Bones{}
var _ Expression = &Binary{}
var _ Expression = &Unary{}
var _ Expression = &Call{}
var _ Expression = &Aquarium{}
var _ Expression = &Index{}
var _ Expression = &String{}
