package evaluator_test

import (
	"bytes"
	"math"
	"testing"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/evaluator"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/object"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/parser"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/scanner"
)

const floatTolerance = 1e-5

func TestEvalIntegerExpression(t *testing.T) {
	tests := []struct {
		input    string
		expected int64
	}{
		{"><{({> ~", 5},
		{"><{({(> ~", 10},
		{"<})}>< ~", -5},
		{"<})})>< ~", -10},
		{"><{({> ><{({> ><{({> ><{({> <})})>< ~", 10},
		{"><})> <3 ><})> <3 ><})> <3 ><})> <3 ><})> ~", 32},
		{"<{{(({(>< ><{{(({((> <{{(({(>< ~", 0},
		{"><{({> <3 ><{(> ><{({(> ~", 20},
		{"><{({> ><{(> <3 ><{({(> ~", 25},
		{"><{({((> ><{(> <3 <{({(>< ~", 0},
		{"><{(> <3 (><{({> ><{({(>) ~", 30},
		{"><{{> <3 ><{{> <3 ><{{> ><{({(> ~", 37},
		{"><{{> <3 (><{{> <3 ><{{>) ><{({(> ~", 37},
		{"><{{(({(> </3 ><{(> <3 ><{(> ><{({(> ~", 60},

		{"><foo> = ><{> ~ <foo><< ~ ><foo> ~", 0},
		{"><foo> = ><(> ~ >><foo> ~ ><foo> ~", 1},

		{"(><{({> ><{({(> <3 ><{(> ><{{{{> </3 ><{{>) <3 ><{(> <})})>< ~", 50},
		{"><})> <3 ><})> <3 ><})> <3 ><})> <3 ><})> ~", 32},
		{"<{{(({(>< ><{{(({((> <{{(({(>< ~", 0},
		{"><{({> <3 ><{(> ><{({(> ~", 20},
		{"><{({> ><{(> <3 ><{({(> ~", 25},
		{"><{({((> ><{(> <3 <{({(>< ~", 0},
		{"><{{(({(> </3 ><{(> <3 ><{(> ><{({(> ~", 60},
		{"><{(> <3 (><{({> ><{({(>) ~", 30},
		{"><{{> <3 ><{{> <3 ><{{> ><{({(> ~", 37},
		{"><{{> <3 (><{{> <3 ><{{>) ><{({(> ~", 37},
		{"(><{({> ><{({(> <3 ><{(> ><{{{{> </3 ><{{>) <3 ><{(> <})})>< ~", 50},
		{"><{> >> ><{> ~", 0}, // 1 >> 1 = 0
		{"><{> << ><{> ~", 2}, // 1 << 1 = 2
		{"><{> & ><(> ~", 0},  // 1 & 0 = 0
		{"><{> | ><(> ~", 1},  // 1 | 0 = 1
		{"><{> ^ ><(> ~", 1},  // 1 ^ 0 = 1
		{"><{> ^ ><{> ~", 0},  // 1 ^ 1 = 0
		{"! ><{> ~", -2},      // ~1 = -2
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		testNumericObject(t, evaluated, tt.expected)
	}
}

func TestEvalFloatExpression(t *testing.T) {
	tests := []struct {
		input    string
		expected float64
	}{
		{"><{(-{{> ~", 2.3},
		{"><{({-{({-{({> ~", 5.55},
		{"><{({-{({{({-{({> ~", 5.455},
		{"<})}-})}>< ~", -5.5},
		{"<})})-})})-})})>< ~", -10.1010},
		{"><-{({> ><{({> ><{({> ><{({> <})})-{(>< ~", 5.3},
		// we have a fixed seed for the test environment
		{"><###> </3 ><{({{{{((({{{{(({(> ~", 42069.1263},
		{"><{-> >> ><{> ~", 0.5}, // 1.0 >> 1 = 0.5
		{"><{-> << ><{> ~", 2},   // 1.0 << 1 = 2.0
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		testNumericObject(t, evaluated, tt.expected)
	}
}

func TestEvalBooleanExpression(t *testing.T) {
	tests := []struct {
		input    string
		expected int64
	}{
		{"><{> ~o ><{(> ~", 1},
		{"><{> o~ ><{(> ~", 0},
		{"><{> ~o= ><{> ~", 1},
		{"><{> ~o ><{> ~", 0},
		{"><{> o~ ><{> ~", 0},
		{"><{> o~= ><{> ~", 1},
		{"><{> == ><{> ~", 1},
		{"><{> ~= ><{> ~", 0},
		{"><{> == ><{(> ~", 0},
		{"><{> ~= ><{(> ~", 1},
		{"><{> && ><{> ~", 1},
		{"><{> && ><(> ~", 0},
		{"><{> || ><{> ~", 1},
		{"><{> || ><(> ~", 1},
		{"><(> || ><(> ~", 0},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		testNumericObject(t, evaluated, tt.expected)
	}
}

func TestBangOperator(t *testing.T) {
	tests := []struct {
		input    string
		expected int64
	}{
		{"!!><{> ~", 0},
		{"!!><(> ~", 1},
		{"!!><{({> ~", 0},
		{"!!!!><{> ~", 1},
		{"!!!!><(> ~", 0},
		{"!!!!><{({> ~", 1},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		testNumericObject(t, evaluated, tt.expected)
	}
}

func TestIfElseExpressions(t *testing.T) {
	tests := []struct {
		input    string
		expected interface{}
	}{
		{"><(((^> (><{>) ><> ><{({(> ~ <><", 10},
		{"><(((^> (><(>) ><> ><{({(> ~ <><", nil},
		{"><(((^> (><{> ~o ><{(>) ><> ><{({(> ~ <><", 10},
		{"><(((^> (><{> o~ ><{(>) ><> ><{({(> ~ <><", nil},
		{"><(((^> (><{> o~ ><{(>) ><> ><{({(> ~ <>< ><(((*> ><> ><{({((> ~ <><", 20},
		{"><(((^> (><{> ~o ><{(>) ><> ><{({(> ~ <>< ><(((*> ><> ><{({((> ~ <><", 10},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		integer, ok := tt.expected.(int)
		if ok {
			testNumericObject(t, evaluated, int64(integer))
		} else {
			testNullObject(t, evaluated)
		}
	}
}

func TestReturnStatements(t *testing.T) {
	tests := []struct {
		input    string
		expected int64
	}{
		{"<~ ><{({(> ~", 10},
		{"<~ ><{({(> ~ ><{(({> ~", 10},
		{"<~ ><{(> <3 ><{({> ~ ><{(({> ~", 10},
		{"><{(({> ~ <~ ><{(> <3 ><{({> ~ ><{(({> ~", 10},
		{"><(((^> (><{({(> o~ ><{>) ><> <~  ><{({(> ~ <><", 10},
		{
			`
><(((^> (><{({(> o~ ><{>)
><>
	><(((^> (><{({(> o~ ><{>)
	><>
		<~  ><{({(> ~
	<><

	<~ ><{> ~
<><
`,
			10,
		},
		{
			`
>(f) ><x>
><>
	<~ ><x> ~
	><x> ><{({(> ~
<><

[>(f) ><{({(>] ~
`,
			10,
		},
		{
			`
>(f) ><x>
><>
	><result> = ><x> ><{({(> ~
	<~ ><result> ~
	<~ ><{({(> ~
<><

[>(f) ><{({(>] ~
`,
			20,
		},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		testNumericObject(t, evaluated, tt.expected)
	}
}

func TestErrorHandling(t *testing.T) {
	tests := []struct {
		input           string
		expectedMessage string
	}{
		{
			"><foobar> ~",
			"identifier not found: foobar",
		},
		{
			`><{{{>[><{>] ~`,
			"index operator not supported: INTEGER",
		},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)

		errObj, ok := evaluated.(*object.Error)
		if !ok {
			t.Errorf("no error object returned. got=%T(%+v)",
				evaluated, evaluated)
			continue
		}

		if errObj.Message != tt.expectedMessage {
			t.Errorf("wrong error message. expected=%q, got=%q",
				tt.expectedMessage, errObj.Message)
		}
	}
}

func TestLetStatements(t *testing.T) {
	tests := []struct {
		input    string
		expected int64
	}{
		{"><a> = ><{(}> ~ ><a> ~", 5},
		{"><a> = ><{(}> <3 ><{(}> ~ ><a> ~", 25},
		{"><a> = ><{(}> ~ ><b> = ><a> ~ ><b> ~", 5},
		{"><a> = ><{(}> ~ ><b> = ><a> ~ ><b> <a>< ~", 0},
		{"><a> = ><{(}> ~ ><b> = ><a> ~ ><c> = ><a> ><b> ><{(}> ~ ><c> ~", 15},
	}

	for _, tt := range tests {
		testNumericObject(t, testEval(t, tt.input), tt.expected)
	}
}

func TestFunctionObject(t *testing.T) {
	input := ">(sub) ><x> ><> ><x> ><{(> ~ <><"

	evaluated := testEval(t, input)
	fn, ok := evaluated.(*object.Function)
	if !ok {
		t.Fatalf("object is not Function. got=%T (%+v)", evaluated, evaluated)
	}

	if len(fn.Parameters) != 1 {
		t.Fatalf("function has wrong parameters. Parameters=%+v",
			fn.Parameters)
	}

	if string(fn.Parameters[0].Name) != "x" {
		t.Fatalf("parameter is not 'x'. got=%q", fn.Parameters[0].Name)
	}

	expectedBody := "{\n(x + 2);\n}"

	if fn.Body.String() != expectedBody {
		t.Fatalf("body is not %q. got=%q", expectedBody, fn.Body.String())
	}
}

func TestFunctionApplication(t *testing.T) {
	tests := []struct {
		input    string
		expected int64
	}{
		{">(identity) ><x> ><> ><x> ~ <>< [>(identity) ><{({>] ~", 5},
		{">(identity) ><x> ><> <~ ><x> ~ <>< [>(identity) ><{({>] ~", 5},
		{">(double) ><x> ><> ><x> <3 ><{(> ~ <>< [>(double) ><{({>] ~", 10},
		{">(add) ><x> ><y> ><> ><x> ><y> ~ <>< [>(add) ><{({> - ><{({>] ~", 10},
		{">(add) ><x> ><y> ><> ><x> ><y> ~ <>< [>(add) ><{({> ><{({> - [>(add) ><{({> - ><{({>] ] ~", 20},
	}

	for _, tt := range tests {
		testNumericObject(t, testEval(t, tt.input), tt.expected)
	}
}

func TestEnclosingEnvironments(t *testing.T) {
	input := `
><first> = ><{({(> ~
><second> = ><{({(> ~
><third> = ><{({(> ~

>(ourFunction) ><first>
><>
	><second> = ><{({((> ~
	><first> ><second> ><third> ~
<><

[>(ourFunction) - ><{({((>] ><second> ><third> ~
`

	testNumericObject(t, testEval(t, input), int64(70))
}

func TestStringLiteral(t *testing.T) {
	input := `🫧Hello World!🫧~`

	evaluated := testEval(t, input)
	str, ok := evaluated.(*object.String)
	if !ok {
		t.Fatalf("object is not String. got=%T (%+v)", evaluated, evaluated)
	}

	if str.Value != "Hello World!" {
		t.Errorf("String has wrong value. got=%q", str.Value)
	}
}

func TestStringConcatenation(t *testing.T) {
	input := `🫧Hello🫧 🫧 🫧 🫧World!🫧~`

	evaluated := testEval(t, input)
	str, ok := evaluated.(*object.String)
	if !ok {
		t.Fatalf("object is not String. got=%T (%+v)", evaluated, evaluated)
	}

	if str.Value != "Hello World!" {
		t.Errorf("String has wrong value. got=%q", str.Value)
	}
}

func TestBuiltinFunctions(t *testing.T) {
	t.Skip()
	tests := []struct {
		input    string
		expected interface{}
	}{
		{`len("")`, 0},
		{`len("four")`, 4},
		{`len("hello world")`, 11},
		{`len(1)`, "argument to `len` not supported, got INTEGER"},
		{`len("one", "two")`, "wrong number of arguments. got=2, want=1"},
		{`len([1, 2, 3])`, 3},
		{`len([])`, 0},
		{`puts("hello", "world!")`, nil},
		{`first([1, 2, 3])`, 1},
		{`first([])`, nil},
		{`first(1)`, "argument to `first` must be ARRAY, got INTEGER"},
		{`last([1, 2, 3])`, 3},
		{`last([])`, nil},
		{`last(1)`, "argument to `last` must be ARRAY, got INTEGER"},
		{`rest([1, 2, 3])`, []int{2, 3}},
		{`rest([])`, nil},
		{`push([], 1)`, []int{1}},
		{`push(1, 1)`, "argument to `push` must be ARRAY, got INTEGER"},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)

		switch expected := tt.expected.(type) {
		case int:
			testNumericObject(t, evaluated, int64(expected))
		case nil:
			testNullObject(t, evaluated)
		case string:
			errObj, ok := evaluated.(*object.Error)
			if !ok {
				t.Errorf("object is not Error. got=%T (%+v)",
					evaluated, evaluated)
				continue
			}
			if errObj.Message != expected {
				t.Errorf("wrong error message. expected=%q, got=%q",
					expected, errObj.Message)
			}
		case []int:
			array, ok := evaluated.(*object.Array)
			if !ok {
				t.Errorf("obj not Array. got=%T (%+v)", evaluated, evaluated)
				continue
			}

			if len(array.Elements) != len(expected) {
				t.Errorf("wrong num of elements. want=%d, got=%d",
					len(expected), len(array.Elements))
				continue
			}

			for i, expectedElem := range expected {
				testNumericObject(t, array.Elements[i], int64(expectedElem))
			}
		}
	}
}

func TestArrayLiterals(t *testing.T) {
	input := "[><{> - ><{(> <3 ><{(> - ><{{> ><{{>] ~"

	evaluated := testEval(t, input)
	result, ok := evaluated.(*object.Array)
	if !ok {
		t.Fatalf("object is not Array. got=%T (%+v)", evaluated, evaluated)
	}

	if len(result.Elements) != 3 {
		t.Fatalf("array has wrong num of elements. got=%d",
			len(result.Elements))
	}

	testNumericObject(t, result.Elements[0], int64(1))
	testNumericObject(t, result.Elements[1], int64(4))
	testNumericObject(t, result.Elements[2], int64(6))
}

func TestArrayIndexExpressions(t *testing.T) {
	tests := []struct {
		input    string
		expected interface{}
	}{
		{"[><{> - ><{(> - ><{{>][><(>] ~", 1},
		{"[><{> - ><{(> - ><{{>][><{>] ~", 2},
		{"[><{> - ><{(> - ><{{>][><{(>] ~", 3},
		{"><i> = ><(> ~ [><{>][><i>] ~", 1},
		{"[><{> - ><{(> - ><{{>][><{> ><{>] ~", 3},
		{"><myArray> = [><{> - ><{(> - ><{{>] ~ ><myArray>[><{(>] ~", 3},
		{"><myArray> = [><{> - ><{(> - ><{{>] ~ ><myArray>[><(>] ><myArray>[><{>] ><myArray>[><{(>] ~", 6},
		{"><myArray> = [><{> - ><{(> - ><{{>] ~ ><i> = ><myArray>[><(>] ~ ><myArray>[><i>] ~", 2},
		{"[><{> - ><{(> - ><{{>][><{{>] ~", nil},
		{"[><{> - ><{(> - ><{{>][<}><] ~", nil},
		{"><fysh> = [><{> - ><{(> - ><{{>][<}><] ~ !! ><fysh> ~", 1},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		integer, ok := tt.expected.(int)
		if ok {
			testNumericObject(t, evaluated, int64(integer))
		} else {
			testNullObject(t, evaluated)
		}
	}
}

func TestHashLiterals(t *testing.T) {
	input := `><two> = 🫧two🫧 ~
	[
		🫧one🫧 : ><{({(> <}))}>< -
		><two> : ><{> ><{> -
		🫧thr🫧 🫧ee🫧 : ><{{(> </3 ><{(> -
		><{((> : ><{((> -
		><{> : ><{({> -
		><(> : ><{{(>
	] ~`

	evaluated := testEval(t, input)
	result, ok := evaluated.(*object.Hash)
	if !ok {
		t.Fatalf("Eval didn't return Hash. got=%T (%+v)", evaluated, evaluated)
	}

	expected := map[object.HashKey]int64{
		(&object.String{Value: "one"}).HashKey():   1,
		(&object.String{Value: "two"}).HashKey():   2,
		(&object.String{Value: "three"}).HashKey(): 3,
		(&object.Integer{Value: 4}).HashKey():      4,
		evaluator.TRUE.HashKey():                   5,
		evaluator.FALSE.HashKey():                  6,
	}

	if len(result.Pairs) != len(expected) {
		t.Fatalf("Hash has wrong num of pairs. got=%d", len(result.Pairs))
	}

	for expectedKey, expectedValue := range expected {
		pair, ok := result.Pairs[expectedKey]
		if !ok {
			t.Errorf("no pair for given key in Pairs")
		}

		testNumericObject(t, pair.Value, expectedValue)
	}
}

func TestHashIndexExpressions(t *testing.T) {
	tests := []struct {
		input    string
		expected interface{}
	}{
		{`[🫧foo🫧 : ><{({>][🫧foo🫧] ~`, 5},
		{`[🫧foo🫧 : ><{({>][🫧bar🫧] ~`, nil},
		{`><key> = 🫧foo🫧 ~ [🫧foo🫧 : ><{({>][><key>] ~`, 5},
		{`[:][🫧foo🫧] ~`, nil},
		{`[><{({> : ><{({>][><{({>] ~`, 5},
	}

	for _, tt := range tests {
		evaluated := testEval(t, tt.input)
		integer, ok := tt.expected.(int)
		if ok {
			testNumericObject(t, evaluated, int64(integer))
		} else {
			testNullObject(t, evaluated)
		}
	}
}

func testEval(t testing.TB, input string) object.Object {
	l, err := scanner.NewFile("evaluator-test-input", bytes.NewBuffer([]byte(input)))
	if err != nil {
		t.Fatal(err)
	}
	p := parser.New(l)
	program, err := p.Parse()
	if err != nil {
		t.Fatalf("program failed to parse: %v.\nprogram: %s", err, input)
	}
	env := object.NewEnvironmentWithSeed(0)

	return evaluator.Eval(program, env)
}

func testNumericObject[T object.Numeric](t testing.TB, obj object.Object, expected T) bool {
	t.Helper()
	result, ok := obj.(object.NumericObj[T])
	if !ok {
		t.Errorf("object is not %T. got=%T (%+v)", new(object.NumericObj[T]), obj, obj)
		return false
	}
	if result.Val() != expected {
		if math.Abs(float64(result.Val()-expected)) <= floatTolerance {
			return true
		}
		t.Errorf("object has wrong value. got=%v, want=%v",
			result.Val(), expected)
		return false
	}

	return true
}

func testNullObject(t testing.TB, obj object.Object) bool {
	t.Helper()
	if obj != evaluator.NULL {
		t.Errorf("object is not NULL. got=%T (%+v)", obj, obj)
		return false
	}
	return true
}
