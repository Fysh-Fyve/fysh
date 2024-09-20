package parser_test

import (
	"bytes"
	"testing"

	"github.com/Fysh-Fyve/fysh/src/parser"
	"github.com/Fysh-Fyve/fysh/src/scanner"
)

type Test struct{ statement string }

func testProgram(t testing.TB, input string, tests []Test) {
	t.Helper()
	s, err := scanner.NewFile("parser-test-input", bytes.NewBuffer([]byte(input)))
	if err != nil {
		t.Fatal(err)
	}
	p := parser.New(s)
	prog, err := p.Parse()
	if err != nil {
		t.Fatalf("parse error: %s", err)
	}
	if len(prog.TopLevels) != len(tests) {
		t.Fatalf("number of declarations wrong. expected=%d, got=%d",
			len(tests), len(prog.TopLevels))
	}
	for i, tt := range tests {
		if s := prog.TopLevels[i]; tt.statement != s.String() {
			t.Fatalf("tests[%d] - statement wrong. expected=%q, got=%q",
				i, tt.statement, s)
		}
	}
}

func TestExpressions(t *testing.T) {
	tc := []struct {
		stmt   string
		parsed string
	}{
		{"><(({o> ~", "1;"},
		{"><{{-{{> ~", "3.300000;"},
		{"><-{{-{{> ~", "0.330000;"},
		{"<{{-{{>< ~", "-3.300000;"},
		{"<-{{-{{>< ~", "-0.330000;"},
		{"><fysh> ~", "fysh;"},
		{"><fysh> <3 ><{({o> ~", "(fysh * 5);"},
		{"><fysh> ><{({o> <3 ><(({o> ~", "(fysh + (5 * 1));"},
		{"><fyshy> | ><{({o> ^ ><(({o> ~", "(fyshy | (5 ^ 1));"},
		{"><fysh1> ><fysh2> ><fysh3> ~", "(fysh1 + (fysh2 + fysh3));"},
		{"><{{> <3 ><{(({({> <3 ><{({{{{({{> ~", "((3 * 37) * 379);"},
		{"><{{> <3 (><{(({({> <3 ><{({{{{({{>) ~", "(3 * (37 * 379));"},
		{"><fysh> o~ ><{({{{{({{> ~", "(fysh > 379);"},
		{"[>(sub) ><{({{{{({{>] ~", "sub(379);"},
		{"[><{({{{{({{>] ~", "[379];"},
		{"[><{({{{{({{> - ><{({{{{({{>] ~", "[379, 379];"},
		{"<{{{>< ~", "-7;"},
		{"!!><}> ~", "(!1);"},
		{"!><}> ~", "(~1);"},
		{"!!!><}> ~", "(!(~1));"},
		{"!(!!><}>) ~", "(~(!1));"},
		{"><{{(({(> </3 ><{(> <3 ><{(> ><{({(> ~", "(((50 / 2) * 2) + 10);"},
		{"><num>[><{({(>]~", "num[10];"},
		{"[ ><bar> : ><{> - ><baz> : ><{(> - ><qux> : ><{{> ] ~", "{bar: 1, baz: 2, qux: 3};"},
		{"[:] ~", "{};"},
	}

	tests := make([]Test, len(tc))
	input := ""
	for i, d := range tc {
		input += d.stmt
		tests[i] = Test{d.parsed}
	}
	testProgram(t, input, tests)
}

func TestSub(t *testing.T) {
	input := `
>(abs) ><num>
><>
	><(((^> [><num> o~ ><)))>]
	><>
		<~ ><num> ~
	<><
	><(((*>
	><>
		<~ <num>< ~
	<><
<><
`
	tests := []Test{
		{`sub abs(num) {
if ((num > 0)) {
return num;
} else {
return (-num);
}
}`},
	}
	testProgram(t, input, tests)
}

func TestAssignment(t *testing.T) {
	input := `
><fysh> = ><(({o> ~
<fysh>< = ><(({o> ~
`
	tests := []Test{
		{"fysh = 1;"},
		{"fysh = (-1);"},
	}
	testProgram(t, input, tests)
}

func TestIncrementDecrement(t *testing.T) {
	input := `>><fysh> ~ <fysh><< ~`
	tests := []Test{{"fysh++;"}, {"fysh--;"}}
	testProgram(t, input, tests)
}

func TestTanks(t *testing.T) {
	input := `
><numbers> = [><})}> - ><}})> - ><}}}> - <({><] ~
><avg> = [>(average) ><numbers>] ~
><avg> = [(average)< ><numbers>] ~
`
	tests := []Test{
		{"numbers = [5, 6, 7, -1];"},
		{"avg = average(numbers);"},
		{"avg = (-average(numbers));"},
	}
	testProgram(t, input, tests)
}

func TestStrings(t *testing.T) {
	input := `
><numbers> = 🫧Test String🫧 ~
`
	tests := []Test{
		{"numbers = \"Test String\";"},
	}
	testProgram(t, input, tests)
}

func TestBlink(t *testing.T) {
	input := `
><{{(((> (+o ><{> ~

><>
	o+) ><steven> ~
	(+o ><###> ~
<><

><(((^> (><steven> o~ ><}}>)
><>
        <~ ><steven> ~
<><
><(((*> ><(((^> (><steven> o~ ><}))>)
><>
        <~ ><steven> ><{> ~
<><

><(((@> [><{>]
><>
        ><{{(((o> (+o ><{> ~
        ><{{(((o> (+o ><(> ~
<><

><//> With Fysh Bowl
><(((@> (><{>)
><>
	><\/> ~
	<\/>< ~
<><
`
	tests := []Test{
		{"(24 (+o 1);"},
		{"{\no+) steven;\n(+o ><###>;\n}"},
		{"if ((steven > 3)) {\nreturn steven;\n} else {\nif ((steven > 4)) {\nreturn (steven + 1);\n}\n}"},
		{"while (1) {\n(24 (+o 1);\n(24 (+o 0);\n}"},
		{"while (1) {\nbreak;\nbreak;\n}"},
	}
	testProgram(t, input, tests)
}
