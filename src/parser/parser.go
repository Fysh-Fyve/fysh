package parser

import (
	"bytes"
	"fmt"
	"strconv"
	"strings"

	"github.com/Fysh-Fyve/fysh/src/ast"
	"github.com/Fysh-Fyve/fysh/src/ast/binary"
	"github.com/Fysh-Fyve/fysh/src/ast/unary"
	"github.com/Fysh-Fyve/fysh/src/fysh"
	"github.com/Fysh-Fyve/fysh/src/scanner"
)

type ParserErrors []error

func (p ParserErrors) Error() string {
	var out bytes.Buffer
	for _, e := range p {
		out.WriteString(e.Error() + "\n")
	}
	return out.String()
}

func (p *Parser) bonesToFloat (s string, neg bool) ast.Expression {
	// split bones to get the binary values e.g. "101-110" -> ["101", "110"]
	arr := strings.Split(s, "-")

	strnums := ""

	// build the float string (e.g. ["101", "110", "101"] -> 5.65)
	for i, v := range arr {
		if v == "" {
			arr[i] = "0"
		}
		
		nums, err := strconv.ParseInt(arr[i], 2, 64)
		if err != nil {
			p.errors = append(p.errors, err)
			return nil
		}

		strnums += strconv.FormatInt(nums, 10)

		if i == 0 {
			strnums += "."
		}
	}

	result, err := strconv.ParseFloat(strnums, 64)
	if err != nil {
		p.errors = append(p.errors, err)
		return nil
	}

	if neg {
		result = -result
	}
	
	p.next()
	return &ast.Bones{Value: result}
}

type Parser struct {
	scanner *scanner.Scanner
	errors  ParserErrors
	cur     fysh.Fysh
	peek    fysh.Fysh
}

func New(s *scanner.Scanner) *Parser {
	p := &Parser{scanner: s}
	p.next()
	p.next()
	return p
}

func isComment(s fysh.Species) bool {
	return s == fysh.Comment || s == fysh.BlockC
}

func (p *Parser) next() {
	p.cur = p.peek
	for ok := true; ok; ok = isComment(p.peek.Type) {
		p.peek = p.scanner.NextFysh()
	}
}

func (p *Parser) expectFysh(f fysh.Species, ignore ...bool) bool {
	if p.cur.Type != f {
		if len(ignore) == 0 {
			err := fmt.Errorf("expected fysh %s, got %s", f, p.cur.Type)
			p.errors = append(p.errors, err)
		}
		return false
	}
	p.next()
	return true
}

func (p *Parser) list() ast.Expression {
	p.next()
	exprs := []ast.Expression{}
	sub, neg := "", false
	for !p.cur.Type.IsOneOf(fysh.RTank, fysh.End, fysh.Invalid) {
		if p.expectFysh(fysh.Food, true) {
		}
		if p.cur.Type == fysh.Sub {
			if sub != "" {
				p.errors = append(p.errors, fmt.Errorf("conflicting calls: %s", sub))
				return nil
			}
			sub, neg = p.cur.Unfysh()
			p.next()
		} else {
			e := p.expression()
			if e == nil {
				return nil
			}
			exprs = append(exprs, e)
		}
	}
	if !p.expectFysh(fysh.RTank) {
		return nil
	}
	if sub != "" {
		var c ast.Expression = &ast.Call{
			Callee: sub,
			Args:   exprs,
		}
		if neg {
			c = &ast.Unary{Op: unary.Neg, Right: c}
		}
		return c
	} else {
		return &ast.Aquarium{Elems: exprs}
	}
}

func (p *Parser) primary() ast.Expression {
	switch p.cur.Type {
	case fysh.Grilled:
		p.next()
		return &ast.Grilled{}
	case fysh.Scales:
		bin, neg := p.cur.Unfysh()
		if i, err := strconv.ParseInt(bin, 2, 64); err != nil {
			p.errors = append(p.errors, err)
			return nil
		} else {
			p.next()
			if neg {
				i = -i
			}
			return &ast.Scales{Value: i}
		}
	case fysh.Bones:
		bin, neg := p.cur.Unfysh()
		return p.bonesToFloat(bin, neg)

	case fysh.Ident:
		name, neg := p.cur.Unfysh()
		var ident ast.Expression = &ast.Identifier{Name: name}
		p.next()
		if neg {
			ident = &ast.Unary{Op: unary.Neg, Right: ident}
		}
		return ident
	case fysh.LTank:
		return p.list()
	case fysh.LBowl:
		p.next()
		expr := p.expression()
		if expr == nil {
			return nil
		}
		if p.expectFysh(fysh.RBowl) {
			return expr
		}
	default:
		p.expectFysh(fysh.Scales)
	}
	return nil
}

func (p *Parser) index() ast.Expression {
	left := p.primary()
	if p.cur.Type == fysh.LTank {
		p.next()
		idx := p.expression()
		if idx == nil {
			return nil
		}
		left = &ast.Index{Left: left, Index: idx}
		if !p.expectFysh(fysh.RTank) {
			return nil
		}
	}
	return left
}
func (p *Parser) unary() ast.Expression {
	ops := []unary.Op{}

	op := unary.FromFysh(p.cur.Type)
	for op.IsOneOf(unary.BitwiseNot, unary.LogicalNot) {
		ops = append(ops, op)
		p.next()
		op = unary.FromFysh(p.cur.Type)
	}

	right := p.index()
	if right == nil {
		return nil
	}

	for len(ops) > 0 {
		op := ops[len(ops)-1]
		right = &ast.Unary{Op: op, Right: right}
		ops = ops[:len(ops)-1]
	}

	return right
}

func (p *Parser) binOp(pLeft, pRight func() ast.Expression,
	cond func(binary.Op) bool) ast.Expression {
	left := pLeft()
	if left == nil {
		return nil
	}
	op := binary.FromFysh(p.cur.Type)
	for cond(op) {
		p.next()
		right := pRight()
		if right == nil {
			return nil
		}
		left = &ast.Binary{Left: left, Op: op, Right: right}
		op = binary.FromFysh(p.cur.Type)
	}

	return left
}

func (p *Parser) multiplicative() ast.Expression {
	return p.binOp(p.unary, p.unary, func(o binary.Op) bool {
		return o.IsOneOf(binary.Mul, binary.Div, binary.ShiftLeft,
			binary.ShiftRight, binary.BitwiseAnd)
	})
}

func (p *Parser) additive() ast.Expression {
	left := p.multiplicative()
	if left == nil {
		return nil
	}
	op := binary.FromFysh(p.cur.Type)
	for op.IsOneOf(binary.BitwiseOr, binary.BitwiseXor) ||
		(op == binary.Invalid && !p.cur.Type.IsOneOf(
			fysh.Water, fysh.RBowl, fysh.RTank, fysh.Sub, fysh.Food,
		)) {
		if op != binary.Invalid {
			p.next()
		} else {
			op = binary.Add
		}
		right := p.additive()
		if right == nil {
			return nil
		}
		left = &ast.Binary{Left: left, Op: op, Right: right}
		op = binary.FromFysh(p.cur.Type)
	}

	return left
}

func (p *Parser) comparative() ast.Expression {
	return p.binOp(p.additive, p.comparative, func(o binary.Op) bool {
		return o.IsOneOf(binary.Equal, binary.NotEqual, binary.LTE, binary.GTE,
			binary.GT, binary.LT)
	})
}

func (p *Parser) and() ast.Expression {
	return p.binOp(p.comparative, p.and, func(o binary.Op) bool {
		return o == binary.LogicalAnd
	})
}

func (p *Parser) or() ast.Expression {
	return p.binOp(p.and, p.or, func(o binary.Op) bool {
		return o == binary.LogicalOr
	})
}

func (p *Parser) anchor() ast.Expression {
	return p.binOp(p.or, p.anchor, func(o binary.Op) bool {
		return o.IsOneOf(binary.AnchorIn, binary.AnchorOut)
	})
}

func (p *Parser) expression() ast.Expression {
	return p.anchor()
}

func (p *Parser) assignment() ast.Statement {
	name, negate := p.cur.Unfysh()
	left := &ast.Identifier{Name: name}
	p.next()
	p.next()

	expr := p.expression()
	if expr == nil {
		return nil
	}
	if negate {
		expr = &ast.Unary{Op: unary.Neg, Right: expr}
	}
	return p.water(&ast.AssignmentStatement{Left: left, Right: expr})
}

func (p *Parser) water(s ast.Statement) ast.Statement {
	if p.expectFysh(fysh.Water) {
		return s
	} else {
		return nil
	}
}

func (p *Parser) squid() ast.Statement {
	p.next()
	ret := &ast.ReturnStatement{}
	ret.Expr = p.expression()
	if ret.Expr == nil {
		return nil
	}
	return p.water(ret)
}

func (p *Parser) breakStmt() ast.Statement {
	p.next()
	return p.water(&ast.BreakStatement{})
}

func (p *Parser) anchorStmt() ast.Statement {
	op := binary.FromFysh(p.cur.Type)
	p.next()
	anc := &ast.AnchorStatement{Op: op}
	anc.Right = p.expression()
	if anc.Right == nil {
		return nil
	}
	return p.water(anc)
}

func (p *Parser) loop() ast.Statement {
	p.next()
	l := &ast.LoopStatement{}
	var closing fysh.Species
	if p.expectFysh(fysh.LTank, true) {
		closing = fysh.RTank
	} else if p.expectFysh(fysh.LBowl) {
		closing = fysh.RBowl
	} else {
		return nil
	}
	l.Cond = p.expression()
	if l.Cond == nil {
		return nil
	}

	if !p.expectFysh(closing) {
		return nil
	}

	l.Body = p.block()
	if l.Body == nil {
		return nil
	}

	return l
}

func (p *Parser) ifStmt() ast.Statement {
	p.next()
	i := &ast.IfStatement{}
	var closing fysh.Species
	if p.expectFysh(fysh.LTank, true) {
		closing = fysh.RTank
	} else if p.expectFysh(fysh.LBowl) {
		closing = fysh.RBowl
	} else {
		return nil
	}
	i.Cond = p.expression()
	if i.Cond == nil {
		return nil
	}

	if !p.expectFysh(closing) {
		return nil
	}

	i.Then = p.block()
	if i.Then == nil {
		return nil
	}

	if p.cur.Type == fysh.Else {
		p.next()
		if p.cur.Type == fysh.If {
			alt := p.ifStmt()
			if alt == nil {
				return nil
			}
			i.Else = &ast.BlockStatement{Statements: []ast.Statement{alt}}
		} else {
			i.Else = p.block()
			if i.Else == nil {
				return nil
			}
		}
	}

	return i
}

func (p *Parser) statement() ast.Statement {
	switch p.cur.Type {
	case fysh.BreakFysh:
		return p.breakStmt()
	case fysh.LFysh:
		return p.block()
	case fysh.Loop:
		return p.loop()
	case fysh.Squid:
		return p.squid()
	case fysh.LAnchor:
		fallthrough
	case fysh.RAnchor:
		return p.anchorStmt()
	case fysh.If:
		return p.ifStmt()
	case fysh.Inc:
		name, _ := p.cur.Unfysh()
		ident := &ast.Identifier{Name: name}
		p.next()
		return p.water(&ast.IncrementStatement{Expr: ident})
	case fysh.Dec:
		name, _ := p.cur.Unfysh()
		ident := &ast.Identifier{Name: name}
		p.next()
		return p.water(&ast.DecrementStatement{Expr: ident})
	default:
		if p.cur.Type == fysh.Ident && p.peek.Type == fysh.Assign {
			return p.assignment()
		} else {
			expr := p.expression()
			if expr == nil {
				return nil
			}
			return p.water(&ast.ExpressionStatement{Expr: expr})
		}
	}
}

func (p *Parser) block() *ast.BlockStatement {
	if !p.expectFysh(fysh.LFysh) {
		return nil
	}
	b := &ast.BlockStatement{Statements: []ast.Statement{}}

	for !p.cur.Type.IsOneOf(fysh.RFysh, fysh.End, fysh.Invalid) {
		s := p.statement()
		if s == nil {
			return nil
		}
		b.Statements = append(b.Statements, s)
	}

	if !p.expectFysh(fysh.RFysh) {
		return nil
	}

	return b
}

func (p *Parser) submarine() *ast.SUBRoutine {
	sub := &ast.SUBRoutine{}
	sub.Name, sub.Neg = p.cur.Unfysh()
	sub.Parameters = []ast.Param{}
	p.next()
	for p.cur.Type.IsOneOf(fysh.Ident) {
		var par ast.Param
		par.Name, par.Neg = p.cur.Unfysh()
		sub.Parameters = append(sub.Parameters, par)
		p.next()
	}
	sub.Body = p.block()
	if sub.Body == nil {
		return nil
	}
	return sub
}

func (p *Parser) Parse() (*ast.Program, error) {
	p.errors = make([]error, 0)
	prog := &ast.Program{
		TopLevels: make([]ast.SurfaceLevel, 0),
	}

	for !p.cur.Type.IsOneOf(fysh.End, fysh.Invalid) {
		var s ast.SurfaceLevel
		if p.cur.Type == fysh.Sub {
			s = p.submarine()
		} else {
			s = p.statement()
		}

		if s == nil {
			return nil, p.errors
		}

		prog.TopLevels = append(prog.TopLevels, s)
	}

	if len(p.errors) > 0 {
		return nil, p.errors
	} else {
		return prog, nil
	}
}
