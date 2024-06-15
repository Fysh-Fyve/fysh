package binary

import (
	"strconv"

	"github.com/Fysh-Fyve/fysh/fysh"
)

type Op int8

const (
	Invalid Op = iota
	Add
	Mul
	Div
	Equal
	NotEqual
	GT
	LT
	GTE
	LTE
	BitwiseAnd
	BitwiseOr
	BitwiseXor
	LogicalAnd
	LogicalOr
	ShiftLeft
	ShiftRight
	AnchorIn
	AnchorOut
)

var tokens = [...]string{
	Invalid:    "INVALID",
	Add:        "+",
	Mul:        "*",
	Div:        "/",
	Equal:      "==",
	NotEqual:   "!=",
	GT:         ">",
	LT:         "<",
	GTE:        ">=",
	LTE:        "<=",
	BitwiseAnd: "&",
	BitwiseOr:  "|",
	BitwiseXor: "^",
	LogicalAnd: "&&",
	LogicalOr:  "||",
	ShiftLeft:  "<<",
	ShiftRight: ">>",
	AnchorIn:   "o+)",
	AnchorOut:  "(+o",
}

func (s Op) IsOneOf(other ...Op) bool {
	for _, o := range other {
		if s == o {
			return true
		}
	}
	return false
}

func (o Op) String() string {
	str := ""
	if 0 <= o && o < Op(len(tokens)) {
		str = tokens[o]
	}
	if str == "" {
		str = "binary(" + strconv.Itoa(int(o)) + ")"
	}
	return str
}

func FromFysh(s fysh.Species) Op {
	switch s {
	case fysh.Mul:
		return Mul
	case fysh.Div:
		return Div
	case fysh.LT:
		return LT
	case fysh.GT:
		return GT
	case fysh.LTE:
		return LTE
	case fysh.GTE:
		return GTE
	case fysh.Eq:
		return Equal
	case fysh.NEq:
		return NotEqual
	case fysh.BWAnd:
		return BitwiseAnd
	case fysh.BWOr:
		return BitwiseOr
	case fysh.Caret:
		return BitwiseXor
	case fysh.LAnd:
		return LogicalAnd
	case fysh.LOr:
		return LogicalOr
	case fysh.LShift:
		return ShiftLeft
	case fysh.RShift:
		return ShiftRight
	case fysh.LAnchor:
		return AnchorOut
	case fysh.RAnchor:
		return AnchorIn
	default:
		return Invalid
	}
}
