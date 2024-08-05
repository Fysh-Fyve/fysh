package object

import (
	"bytes"
	"fmt"
	"hash/fnv"
	"strings"
	"unsafe"

	"github.com/Fysh-Fyve/fysh/src/ast"
)

type BuiltinFunction func(args ...Object) Object

type ObjectType string

const (
	NUL = "NULL"
	ERR = "ERROR"

	INT   = "INTEGER"
	STR   = "STRING"
	FLOAT = "FLOAT"

	RET = "RETURN_VALUE"

	FUN = "FUNCTION"
	STD = "BUILTIN"

	ARR = "ARRAY"
	MAP = "HASH"

	BRK = "BREAK"
)

type HashKey struct {
	Type  ObjectType
	Value uint64
}

type Hashable interface {
	HashKey() HashKey
}

type Object interface {
	Type() ObjectType
	Inspect() string
}

type Numeric interface {
	int64 | float64
}

type NumericObj[T Numeric] interface {
	Val() T
}

type Integer struct{ Value int64 }

func (i *Integer) Type() ObjectType { return INT }
func (i *Integer) Inspect() string  { return fmt.Sprintf("%d", i.Value) }
func (i *Integer) HashKey() HashKey {
	return HashKey{Type: i.Type(), Value: uint64(i.Value)}
}
func (i *Integer) Val() int64 { return i.Value }

type Float struct{ Value float64 }

var _ NumericObj[int64] = &Integer{}
var _ NumericObj[float64] = &Float{}

func float64bits(f float64) uint64 { return *(*uint64)(unsafe.Pointer(&f)) }

func (i *Float) Type() ObjectType { return FLOAT }
func (i *Float) Inspect() string  { return fmt.Sprintf("%f", i.Value) }
func (i *Float) HashKey() HashKey {
	return HashKey{Type: i.Type(), Value: float64bits(i.Value)}
}
func (i *Float) Val() float64 { return i.Value }

type Null struct{}

func (n *Null) Type() ObjectType { return NUL }
func (n *Null) Inspect() string  { return "null" }

type Break struct{}

func (b *Break) Type() ObjectType { return BRK }
func (b *Break) Inspect() string  { return "break" }

type ReturnValue struct{ Value Object }

func (rv *ReturnValue) Type() ObjectType { return RET }
func (rv *ReturnValue) Inspect() string  { return rv.Value.Inspect() }

type Error struct{ Message string }

func (e *Error) Type() ObjectType { return ERR }
func (e *Error) Inspect() string  { return "ERROR: " + e.Message }

type Function struct {
	Parameters []ast.Param
	Body       *ast.BlockStatement
	Env        *Environment
}

func (f *Function) Type() ObjectType { return FUN }
func (f *Function) Inspect() string {
	var out bytes.Buffer

	params := [][]byte{}
	for _, p := range f.Parameters {
		params = append(params, p.Name)
	}

	out.WriteString("fn")
	out.WriteString("(")
	out.Write(bytes.Join(params, []byte(", ")))
	out.WriteString(") {\n")
	out.WriteString(f.Body.String())
	out.WriteString("\n}")

	return out.String()
}

type String struct{ Value string }

func (s *String) Type() ObjectType { return STR }
func (s *String) Inspect() string  { return s.Value }
func (s *String) HashKey() HashKey {
	h := fnv.New64a()
	h.Write([]byte(s.Value))

	return HashKey{Type: s.Type(), Value: h.Sum64()}
}

type Builtin struct{ Fn BuiltinFunction }

func (b *Builtin) Type() ObjectType { return STD }
func (b *Builtin) Inspect() string  { return "builtin function" }

type Array struct{ Elements []Object }

func (ao *Array) Type() ObjectType { return ARR }
func (ao *Array) Inspect() string {
	var out bytes.Buffer

	elements := []string{}
	for _, e := range ao.Elements {
		elements = append(elements, e.Inspect())
	}

	out.WriteString("[")
	out.WriteString(strings.Join(elements, ", "))
	out.WriteString("]")

	return out.String()
}

type HashPair struct {
	Key   Object
	Value Object
}

type Hash struct{ Pairs map[HashKey]HashPair }

func (h *Hash) Type() ObjectType { return MAP }
func (h *Hash) Inspect() string {
	var out bytes.Buffer

	pairs := []string{}
	for _, pair := range h.Pairs {
		pairs = append(pairs, fmt.Sprintf("%s: %s",
			pair.Key.Inspect(), pair.Value.Inspect()))
	}

	out.WriteString("{")
	out.WriteString(strings.Join(pairs, ", "))
	out.WriteString("}")

	return out.String()
}

func IsError(obj Object) bool {
	if obj != nil {
		return obj.Type() == ERR
	}
	return false
}
