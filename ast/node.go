package ast

import (
	"bytes"
	"fmt"

	"github.com/Fysh-Fyve/go-fysh/fysh"
)

type Node interface {
	Literal() string
	String() string
}

type SurfaceLevel interface {
	Node
	top()
}

type Statement interface {
	SurfaceLevel
	statement()
}

type Expression interface {
	Node
	expression()
}

type Program struct{ TopLevels []SurfaceLevel }

func (p *Program) top()            {}
func (p *Program) statement()      {}
func (p *Program) Literal() string { return "" }
func (p *Program) String() string {
	var out bytes.Buffer
	for _, s := range p.TopLevels {
		out.WriteString(s.String())
	}

	return out.String()
}

type Param struct {
	Name string
	Neg  bool
}

type SUBRoutine struct {
	Name       string
	Neg        bool
	Parameters []Param
	Body       *BlockStatement
}

func (s *SUBRoutine) top()            {}
func (s *SUBRoutine) Literal() string { return fysh.Sub.String() }
func (s *SUBRoutine) String() string {
	var out bytes.Buffer
	if s.Neg {
		out.WriteString("-")
	}
	fmt.Fprintf(&out, "sub %s(", s.Name)
	for i, p := range s.Parameters {
		if i != 0 {
			out.WriteString(", ")
		}
		if p.Neg {
			out.WriteString("-")
		}
		out.WriteString(p.Name)
	}
	fmt.Fprintf(&out, ") %s", s.Body)
	return out.String()
}

// Interface Assertions
var _ SurfaceLevel = &SUBRoutine{}
