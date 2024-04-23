package object

import "math/rand"

func NewEnclosedEnvironment(outer *Environment) *Environment {
	env := NewEnvironment()
	env.outer = outer
	env.RNG = outer.RNG
	return env
}

type globalRng struct{}

func (g globalRng) Num() uint32 {
	return rand.Uint32()
}

type localRng struct {
	r *rand.Rand
}

func (l *localRng) Num() uint32 {
	return l.r.Uint32()
}

func NewEnvironmentWithSeed(seed int64) *Environment {
	e := NewEnvironment()
	e.RNG = &localRng{r: rand.New(rand.NewSource(seed))}
	return e
}

func NewEnvironment() *Environment {
	s := make(map[string]Object)
	return &Environment{store: s, outer: nil, RNG: globalRng{}}
}

type rng interface {
	Num() uint32
}

type Environment struct {
	store map[string]Object
	outer *Environment
	RNG   rng
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
