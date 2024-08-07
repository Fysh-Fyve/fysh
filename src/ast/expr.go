package ast

import (
	"bytes"
	"fmt"
	"slices"
	"strings"

	"github.com/Fysh-Fyve/fysh/src/ast/binary"
	"github.com/Fysh-Fyve/fysh/src/ast/unary"
	"github.com/Fysh-Fyve/fysh/src/fysh"
)

type Identifier struct{ Name []byte }

func (i *Identifier) expression()     {}
func (i *Identifier) Literal() string { return fysh.Ident.String() }
func (i *Identifier) String() string  { return string(i.Name) }

type Grilled struct {
}

func (s *Grilled) expression()     {}
func (s *Grilled) Literal() string { return fysh.Grilled.String() }
func (s *Grilled) String() string  { return fysh.Grilled.String() }

type Scales struct{ Value int64 }

func (s *Scales) expression()     {}
func (s *Scales) Literal() string { return fysh.Scales.String() }
func (s *Scales) String() string  { return fmt.Sprintf("%d", s.Value) }

type Bones struct{ Value float64 }

func (s *Bones) expression()     {}
func (s *Bones) Literal() string { return fysh.Bones.String() }
func (s *Bones) String() string  { return fmt.Sprintf("%f", s.Value) }

type String struct{ Value []byte }

func (s *String) expression()     {}
func (s *String) Literal() string { return string(s.Value) }
func (s *String) String() string  { return fmt.Sprintf("\"%s\"", s.Value) }

type Unary struct {
	Op    unary.Op
	Right Expression
}

func (u *Unary) expression()     {}
func (u *Unary) Literal() string { return u.Op.String() }
func (u *Unary) String() string {
	return fmt.Sprintf("(%s%s)", u.Op, u.Right)
}

type Call struct {
	Callee []byte
	Args   []Expression
}

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

func (b *Binary) expression()     {}
func (b *Binary) Literal() string { return b.Op.String() }
func (b *Binary) String() string {
	return fmt.Sprintf("(%s %s %s)", b.Left, b.Op, b.Right)
}

type Index struct {
	Left  Expression
	Index Expression
}

func (b *Index) expression()     {}
func (b *Index) Literal() string { return b.Left.Literal() }
func (b *Index) String() string {
	return fmt.Sprintf("%s[%s]", b.Left, b.Index)
}

type Aquarium struct{ Elems []Expression }

func (c *Aquarium) expression()     {}
func (c *Aquarium) Literal() string { return fysh.LTank.String() }
func (c *Aquarium) String() string {
	var out bytes.Buffer
	out.WriteString(fysh.LTank.String())
	elems := make([]string, 0, len(c.Elems))
	for _, p := range c.Elems {
		elems = append(elems, p.String())
	}
	out.WriteString(strings.Join(elems, ", "))
	out.WriteString(fysh.RTank.String())
	return out.String()
}

type SeaHash struct{ Pairs map[Expression]Expression }

func (c *SeaHash) expression()     {}
func (c *SeaHash) Literal() string { return fysh.LTank.String() }
func (c *SeaHash) String() string {
	var out bytes.Buffer
	out.WriteString("{")
	pairs := make([]string, 0, len(c.Pairs))
	for key, value := range c.Pairs {
		pairs = append(pairs, key.String()+": "+value.String())
	}
	slices.Sort(pairs)
	out.WriteString(strings.Join(pairs, ", "))
	out.WriteString("}")
	return out.String()
}

var _ Expression = &Identifier{}
var _ Expression = &Scales{}
var _ Expression = &Bones{}
var _ Expression = &Binary{}
var _ Expression = &Unary{}
var _ Expression = &Call{}
var _ Expression = &Aquarium{}
var _ Expression = &SeaHash{}
var _ Expression = &Index{}
var _ Expression = &String{}
