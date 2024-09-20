package scanner_test

import (
	"bytes"
	"strings"
	"testing"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/fysh"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/scanner"
)

type tt struct {
	expectedType  fysh.Species
	expectedValue string
}

func lit(f fysh.Species) tt { return tt{f, f.String()} }

func TestUnclosedIdents(t *testing.T) {
	inputs := []string{
		">(abs ",
		"(abs ",
		"><fysh ",
		">><fysh ",
		"<fysh",
		"🫧Unclosed",
	}
	for _, tc := range inputs {
		tests := []tt{
			{fysh.Invalid, tc},
			{fysh.End, ""},
		}

		testScanner(t, tc, tests)
	}
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

	tests := []tt{
		{fysh.Sub, ">(abs)"},
		{fysh.Ident, "><num>"},
		lit(fysh.OpenFysh),
		lit(fysh.If),
		lit(fysh.LTank),
		{fysh.Ident, "><num>"},
		lit(fysh.GT),
		{fysh.Scales, "><)))>"},
		lit(fysh.RTank),
		lit(fysh.OpenFysh),
		lit(fysh.Squid),
		{fysh.Ident, "><num>"},
		lit(fysh.Water),
		lit(fysh.CloseFysh),
		lit(fysh.Else),
		lit(fysh.OpenFysh),
		lit(fysh.Squid),
		{fysh.Ident, "<num><"},
		lit(fysh.Water),
		lit(fysh.CloseFysh),
		lit(fysh.CloseFysh),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestFancyTails(t *testing.T) {
	l := [...]string{"><>", "⟩<>", "⟫<>", "〉<>", "⦄<>", "⦆<>", "⦈<>", "⦊<>", "⦌<>", "⦎<>", "⦐<>", "⦒<>", "⦔<>", "⦖<>", "〉<>", "❭<>", "❯<>", "❱<>", "❳<>", "❵<>"}
	r := [...]string{"<><", "<>⟨", "<>⟪", "<>〈", "<>⦃"}

	tests := make([]tt, 0, len(l)+len(r)+1)
	input := strings.Builder{}
	appendToTest := func(s []string, t tt) {
		for _, str := range s {
			tests = append(tests, t)
			input.WriteString(str)
			input.WriteRune(' ')
		}
	}
	appendToTest(l[:], lit(fysh.OpenFysh))
	appendToTest(r[:], lit(fysh.CloseFysh))
	tests = append(tests, tt{fysh.End, ""})
	testScanner(t, input.String(), tests)
}

func TestFactorial(t *testing.T) {
	input := `
><//> Comment

><number>    = ><{({o> ~  ><//> b101 = 5
><factorial> = ><(((o> ~  ><//> b000 = 0
>><factorial> ~ ><//> set to 1

><//> while number > 1
><(((@> [><number> o~ ><(({o>]
><>
	><//> factorial = factorial * number
	><factorial> = (><factorial> <3 ><number>) ~

	><//> number -= 1
	<number><< ~
<><

><factorial> ~
`

	tests := []tt{
		{fysh.Comment, "><//> Comment\n"},
		{fysh.Ident, "><number>"},
		lit(fysh.Assign),
		{fysh.Scales, "><{({o>"},
		lit(fysh.Water),
		{fysh.Comment, "><//> b101 = 5\n"},
		{fysh.Ident, "><factorial>"},
		lit(fysh.Assign),
		{fysh.Scales, "><(((o>"},
		lit(fysh.Water),
		{fysh.Comment, "><//> b000 = 0\n"},
		{fysh.Inc, ">><factorial>"},
		lit(fysh.Water),
		{fysh.Comment, "><//> set to 1\n"},
		{fysh.Comment, "><//> while number > 1\n"},
		lit(fysh.Loop),
		lit(fysh.LTank),
		{fysh.Ident, "><number>"},
		lit(fysh.GT),
		{fysh.Scales, "><(({o>"},
		lit(fysh.RTank),
		lit(fysh.OpenFysh),
		{fysh.Comment, "><//> factorial = factorial * number\n"},
		{fysh.Ident, "><factorial>"},
		lit(fysh.Assign),
		lit(fysh.LBowl),
		{fysh.Ident, "><factorial>"},
		lit(fysh.Mul),
		{fysh.Ident, "><number>"},
		lit(fysh.RBowl),
		lit(fysh.Water),
		{fysh.Comment, "><//> number -= 1\n"},
		{fysh.Dec, "<number><<"},
		lit(fysh.Water),
		lit(fysh.CloseFysh),
		{fysh.Ident, "><factorial>"},
		lit(fysh.Water),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}
func TestShortLoop(t *testing.T) {
	input := "><((@> @ 🌀 ><((@>><{({o> @><{({o> 🌀><{({o>"
	tests := []tt{
		lit(fysh.Loop),
		lit(fysh.Loop),
		lit(fysh.Loop),
		lit(fysh.Loop),
		{fysh.Scales, "><{({o>"},
		lit(fysh.Loop),
		{fysh.Scales, "><{({o>"},
		lit(fysh.Loop),
		{fysh.Scales, "><{({o>"},
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestStrings(t *testing.T) {
	input := "🫧This is a String🫧 ~ *This is a String* ~ *bubbles 🫧🫧 in string* ~ 🫧stars ** in string🫧~"
	tests := []tt{
		{fysh.Bubbles, "🫧This is a String🫧"},
		lit(fysh.Water),
		{fysh.Bubbles, "*This is a String*"},
		lit(fysh.Water),
		{fysh.Bubbles, "*bubbles 🫧🫧 in string*"},
		lit(fysh.Water),
		{fysh.Bubbles, "🫧stars ** in string🫧"},
		lit(fysh.Water),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestBiblicallyAccurateFysh(t *testing.T) {
	input := `
><{{{oo> ~
><{{{°o°> ~
><{{oooo> <ooooooooo}}>< ><oolong> <oomph>< ><(°o°> ~
`
	tests := []tt{
		{fysh.Scales, "><{{{oo>"},
		lit(fysh.Water),
		{fysh.Scales, "><{{{°o°>"},
		lit(fysh.Water),
		{fysh.Scales, "><{{oooo>"},
		{fysh.Scales, "<ooooooooo}}><"},
		{fysh.Ident, "><oolong>"},
		{fysh.Ident, "<oomph><"},
		{fysh.Scales, "><(°o°>"},
		lit(fysh.Water),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestOperators(t *testing.T) {
	operators := [...]struct {
		op      string
		species fysh.Species
	}{
		{"💔", fysh.Div},
		{"</3", fysh.Div},
		{"&", fysh.BWAnd},
		{"|", fysh.BWOr},
		{"⸾", fysh.BWOr},
		{"!", fysh.BWNot},
		{"^", fysh.Caret},
		{"~=", fysh.NEq},
		{"~≈", fysh.NEq},
		{"==", fysh.Eq},
		{"≈≈", fysh.Eq},
		{"=", fysh.Assign},
		{"≈", fysh.Assign},
		{"o~", fysh.GT},
		{"~o", fysh.LT},
		{"o~=", fysh.GTE},
		{"o~≈", fysh.GTE},
		{"~o=", fysh.LTE},
		{"~o≈", fysh.LTE},
		{"o=", fysh.GTE},
		{"o≈", fysh.GTE},
		{"=o", fysh.LTE},
		{"≈o", fysh.LTE},
		{">>", fysh.RShift},
		{"&&", fysh.LAnd},
		{"<<", fysh.LShift},
		{"||", fysh.LOr},
		{"⸾⸾", fysh.LOr},
		{"!!", fysh.LNot},
	}
	tests := make([]tt, len(operators))
	input := ""
	for i, v := range operators {
		tests[i] = lit(v.species)
		input += v.op + " "
	}
	tests = append(tests, tt{fysh.End, ""})
	testScanner(t, input, tests)
}

func TestHearts(t *testing.T) {
	hearts := [...]string{
		"💝", "☙", "♡", "♥", "❥", "❦", "❧", "🎔", "🖤", "💙",
		"💚", "💛", "💜", "🧡", "🤍", "🤎", "🩶", "🩷", "🩵", "💓", "💕",
		"💖", "💗", "💘", "🫀", "💌", "💞", "💟", "<3",

		// variation selector
		"❣", "❣️ ",
		"❤", "❤️ ",

		// ZWJ (zero width joiner)
		"❤️‍🔥 ",
		"❤️‍🩹 ",

		"🫶",
		// skin tone modifier
		"🫶🏻", "🫶🏼", "🫶🏽", "🫶🏾", "🫶🏿",
	}
	tests := make([]tt, 0, len(hearts))
	for i := 0; i < len(hearts); i++ {
		tests = append(tests, lit(fysh.Mul))
	}
	tests = append(tests, tt{fysh.End, ""})
	input := strings.Join(hearts[:], " ")
	testScanner(t, input, tests)
}

func TestBlink(t *testing.T) {
	input := `
></*>
Blink Example
<*/>
<*/><
><{{(((> (+o ><{> ~

o+) ><steven> ~

><(((^> [><steven> o~ ><}}>]
><>
        <~ ><steven> ~
<><

><(((@> [><{>]
><>
        ><{{(((o> (+o ><{> ~
        ><{{(((o> ⚓ ><(> ~
<><
`
	tests := []tt{
		{fysh.BlockC, "></*>\nBlink Example\n<*/>\n<*/><"},
		{fysh.Scales, "><{{(((>"},
		lit(fysh.LAnchor),
		{fysh.Scales, "><{>"},
		lit(fysh.Water),
		lit(fysh.RAnchor),
		{fysh.Ident, "><steven>"},
		lit(fysh.Water),
		lit(fysh.If),
		lit(fysh.LTank),
		{fysh.Ident, "><steven>"},
		lit(fysh.GT),
		{fysh.Scales, "><}}>"},
		lit(fysh.RTank),
		lit(fysh.OpenFysh),
		lit(fysh.Squid),
		{fysh.Ident, "><steven>"},
		lit(fysh.Water),
		lit(fysh.CloseFysh),
		lit(fysh.Loop),
		lit(fysh.LTank),
		{fysh.Scales, "><{>"},
		lit(fysh.RTank),
		lit(fysh.OpenFysh),
		{fysh.Scales, "><{{(((o>"},
		lit(fysh.LAnchor),
		{fysh.Scales, "><{>"},
		lit(fysh.Water),
		{fysh.Scales, "><{{(((o>"},
		lit(fysh.LAnchor),
		{fysh.Scales, "><(>"},
		lit(fysh.Water),
		lit(fysh.CloseFysh),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestTouching(t *testing.T) {
	input := `
><>♡(><fysh>♡<{{{(())}}}><<{{{(())}}}><><)))>♡><)))><FYSH><><)))>♡)<><
`
	tests := []tt{
		lit(fysh.OpenFysh),
		lit(fysh.Mul),
		lit(fysh.LBowl),
		{fysh.Ident, "><fysh>"},
		lit(fysh.Mul),
		{fysh.Scales, "<{{{(())}}}><"},
		{fysh.Scales, "<{{{(())}}}><"},
		{fysh.Scales, "><)))>"},
		lit(fysh.Mul),
		{fysh.Scales, "><)))>"},
		{fysh.Ident, "<FYSH><"},
		{fysh.Scales, "><)))>"},
		lit(fysh.Mul),
		lit(fysh.RBowl),
		lit(fysh.CloseFysh),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestRandomFysh(t *testing.T) {
	input := "><###>"
	tests := []tt{
		lit(fysh.Grilled),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestIdentifiers(t *testing.T) {
	idents := []string{
		"><pos>", "<neg><", "><ostart>", "<ostart><", "><鱼>", "><とと>", "<魚><",
		"<سمكة><", "><ᜁᜐ᜔ᜇ>", "><ᠨᡳᠮᠠᡥᠠ>", "><𒐫>",
		"><🐠🐟🐡🦈🐬🐳🐋🦐🦑🦞🦀🐙>",
		"><𒈙>",
		"><𓀐𓂸>",
		"><under_scored>",
		"><_under_scored>",
		"><^-^>",
		"<°isthisallowed><", "><whataboutthis°>",
	}
	tests := make([]tt, 0, len(idents))
	for _, name := range idents {
		tests = append(tests, tt{fysh.Ident, name})
	}
	tests = append(tests, tt{fysh.End, ""})
	input := strings.Join(idents[:], " ")
	testScanner(t, input, tests)
}

func TestWeirdFysh(t *testing.T) {
	scales := []string{"><{{({(>", "><{)()}{)()}>", "<o{}{()}><", "<{}{()}><",
		"><{}o>"}
	tests := make([]tt, 0, len(scales))
	for _, name := range scales {
		tests = append(tests, tt{fysh.Scales, name})
	}
	tests = append(tests, tt{fysh.End, ""})
	input := strings.Join(scales[:], " ")
	testScanner(t, input, tests)
}

func TestSeaHash(t *testing.T) {
	input := "[ ><foo> : ><{> - ><bar> : ><{(> - ><baz> : ><{{> ] ~"
	tests := []tt{
		lit(fysh.LTank),
		{fysh.Ident, "><foo>"},
		lit(fysh.Colon),
		{fysh.Scales, "><{>"},
		lit(fysh.Food),
		{fysh.Ident, "><bar>"},
		lit(fysh.Colon),
		{fysh.Scales, "><{(>"},
		lit(fysh.Food),
		{fysh.Ident, "><baz>"},
		lit(fysh.Colon),
		{fysh.Scales, "><{{>"},
		lit(fysh.RTank),
		lit(fysh.Water),
		{fysh.End, ""},
	}
	testScanner(t, input, tests)
}

func TestBrokenFysh(t *testing.T) {
	input := "><\\/> <\\/><"
	tests := []tt{lit(fysh.BreakFysh), lit(fysh.BreakFysh), {fysh.End, ""}}
	testScanner(t, input, tests)
}

func TestFyshBones(t *testing.T) {
	input := "><-{({-{-{> <-{({-{-{>< <o-{({-{-{>< <o{({-{-{>< ><{({-{-{->"
	tests := []tt{
		{fysh.Bones, "><-{({-{-{>"},
		{fysh.Bones, "<-{({-{-{><"},
		{fysh.Bones, "<o-{({-{-{><"},
		{fysh.Bones, "<o{({-{-{><"},
		{fysh.Bones, "><{({-{-{->"},
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

// TODO: Pass original test cases
//
// TEST_CASE("fysh open & wtf open") {
//   FyshLexer lexer{"><> <3 ><{{({(o> ><!@#$> ><> ><!@#$>"};
//
//   T(S::FYSH_OPEN);
//   T(S::HEART_MULTIPLY);
//   T(0b011010);
//   T(S::WTF_OPEN);
//   T(S::FYSH_OPEN);
//   T(S::WTF_OPEN);
//   T(S::END);
// }
//
// TEST_CASE("Bad fysh") {
//   FyshLexer lexer{"><{{({(o>><{{({(o>< ><{{((>< ><{{{< ><o{{}}>< "
//                   "><{{({(o <o{{}}o ><>"};
//   T(0b11010);
//   T(0b11010);
//   INVALID("<");
//   T(0b1100);
//   INVALID("<");
//   INVALID("><{{{<");
//   INVALID("><o{{}}><");
//   INVALID("><{{({(o");
//   INVALID("<o{{}}o");
//   T(S::FYSH_OPEN);
//   T(S::END);
// }
//
// TEST_CASE("Swim Left") {
//   FyshLexer lexer{"<!@#$>< <>< <!@%$>< <!@#$> <><"};
//
//   T(S::WTF_CLOSE);
//   T(S::FYSH_CLOSE);
//   INVALID("<!@%$><");
//   INVALID("<!@#$>");
//   T(S::FYSH_CLOSE);
//   T(S::END);
// }

func TestArrays(t *testing.T) {
	input := `><fysh> = [ ><{}o> - ><{}o> ] ~`
	tests := []tt{
		{fysh.Ident, "><fysh>"},
		lit(fysh.Assign),
		lit(fysh.LTank),
		{fysh.Scales, "><{}o>"},
		lit(fysh.Food),
		{fysh.Scales, "><{}o>"},
		lit(fysh.RTank),
		lit(fysh.Water),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestSubmarines(t *testing.T) {
	input := `>(submarine) (submarine)<`
	tests := []tt{
		{fysh.Sub, ">(submarine)"},
		{fysh.Sub, "(submarine)<"},
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestBabySquid(t *testing.T) {
	input := `
>(submarine) ><fysh>
><>
  >><fysh> ~
  <~ <fysh>< ~
  🦑🦑
  ~<~<fysh><~
<><
`
	tests := []tt{
		{fysh.Sub, ">(submarine)"},
		{fysh.Ident, "><fysh>"},
		lit(fysh.OpenFysh),
		{fysh.Inc, ">><fysh>"},
		lit(fysh.Water),
		lit(fysh.Squid),
		{fysh.Ident, "<fysh><"},
		lit(fysh.Water),
		lit(fysh.Squid),
		lit(fysh.Squid),
		lit(fysh.Water),
		lit(fysh.Squid),
		{fysh.Ident, "<fysh><"},
		lit(fysh.Water),
		lit(fysh.CloseFysh),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestContributors(t *testing.T) {
	input := `
><Contributors> ≈ [ ><Kyle Prince> - ><Charles Ancheta> - ><Yahya Al-Shamali>] ~
`
	tests := []tt{
		{fysh.Ident, "><Contributors>"},
		lit(fysh.Assign),
		lit(fysh.LTank),
		{fysh.Ident, "><Kyle Prince>"},
		lit(fysh.Food),
		{fysh.Ident, "><Charles Ancheta>"},
		lit(fysh.Food),
		{fysh.Ident, "><Yahya Al-Shamali>"},
		lit(fysh.RTank),
		lit(fysh.Water),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func testScanner(t testing.TB, input string, tests []tt) {
	t.Helper()
	s, err := scanner.NewFile("scanner-test-input", bytes.NewBuffer([]byte(input)))
	if err != nil {
		t.Fatal(err)
	}

	for i, tt := range tests {
		tok := s.NextFysh()

		if tok.Type != tt.expectedType {
			t.Fatalf("tests[%d] - tokentype wrong. expected=%q, got=%q",
				i, tt.expectedType, tok.Type)
		}

		if string(tok.Value) != tt.expectedValue {
			t.Fatalf("tests[%d] - literal wrong. expected=%q, got=%q",
				i, tt.expectedValue, tok)
		}
	}
}
