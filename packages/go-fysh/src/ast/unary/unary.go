package unary

import (
	"strconv"

	"github.com/Fysh-Fyve/fysh/src/fysh"
)

type Op int8

const (
	Invalid Op = iota
	Neg
	BitwiseNot
	LogicalNot
)

var tokens = [...]string{
	Invalid:    "INVALID",
	Neg:        "-",
	BitwiseNot: "~",
	LogicalNot: "!",
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
		str = "unary(" + strconv.Itoa(int(o)) + ")"
	}
	return str
}

func FromFysh(s fysh.Species) Op {
	switch s {
	case fysh.LNot:
		return LogicalNot
	case fysh.BWNot:
		return BitwiseNot
	default:
		return Invalid
	}
}
