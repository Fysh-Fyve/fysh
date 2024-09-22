package object

import (
	"math/rand"
)

func NewEnclosedEnvironment(outer *Environment) *Environment {
	env := NewEnvironment(outer.printer)
	env.outer = outer
	env.rng = outer.rng
	return env
}

type globalRng struct{}

func (g globalRng) Num() uint32 {
	return rand.Uint32()
}

type localRng struct{ r *rand.Rand }

func (l *localRng) Num() uint32 {
	return l.r.Uint32()
}

func NewEnvironmentWithSeed(seed int64) *Environment {
	e := NewEnvironment(nil)
	e.rng = &localRng{r: rand.New(rand.NewSource(seed))}
	return e
}

func NewEnvironment(p Printer) *Environment {
	s := make(map[string]Object)
	return &Environment{store: s, outer: nil, rng: globalRng{}}
}

type rng interface {
	Num() uint32
}

type Environment struct {
	store   map[string]Object
	outer   *Environment
	rng     rng
	printer Printer
}

type Printer interface {
	Print(s string)
}

func (e *Environment) RandomNum() uint32 {
	return e.rng.Num()
}

func (e *Environment) Print(s string) {
	if e.printer != nil {
		e.printer.Print(s)
	}
}

func (e *Environment) Get(name string) (Object, bool) {
	obj, ok := e.store[name]
	if !ok && e.outer != nil {
		obj, ok = e.outer.Get(name)
	}
	return obj, ok
}

func (e *Environment) Set(name string, val Object) Object {
	e.store[name] = val
	return val
}
