package scanner_test

import (
	"strings"
	"testing"

	"github.com/Fysh-Fyve/fysh/src/fysh"
	"github.com/Fysh-Fyve/fysh/src/scanner"
)

type tt struct {
	expectedType  fysh.Species
	expectedValue string
}

func lit(f fysh.Species) tt { return tt{f, f.String()} }

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
		lit(fysh.LFysh),
		lit(fysh.If),
		lit(fysh.LTank),
		{fysh.Ident, "><num>"},
		lit(fysh.GT),
		{fysh.Scales, "><)))>"},
		lit(fysh.RTank),
		lit(fysh.LFysh),
		lit(fysh.Squid),
		{fysh.Ident, "><num>"},
		lit(fysh.Water),
		lit(fysh.RFysh),
		lit(fysh.Else),
		lit(fysh.LFysh),
		lit(fysh.Squid),
		{fysh.Ident, "<num><"},
		lit(fysh.Water),
		lit(fysh.RFysh),
		lit(fysh.RFysh),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
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
		lit(fysh.LFysh),
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
		lit(fysh.RFysh),
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
	input := "🫧This is a String🫧 ~"
	tests := []tt{
		{fysh.String, "This is a String"},
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
		lit(fysh.LFysh),
		lit(fysh.Squid),
		{fysh.Ident, "><steven>"},
		lit(fysh.Water),
		lit(fysh.RFysh),
		lit(fysh.Loop),
		lit(fysh.LTank),
		{fysh.Scales, "><{>"},
		lit(fysh.RTank),
		lit(fysh.LFysh),
		{fysh.Scales, "><{{(((o>"},
		lit(fysh.LAnchor),
		{fysh.Scales, "><{>"},
		lit(fysh.Water),
		{fysh.Scales, "><{{(((o>"},
		lit(fysh.LAnchor),
		{fysh.Scales, "><(>"},
		lit(fysh.Water),
		lit(fysh.RFysh),
		{fysh.End, ""},
	}

	testScanner(t, input, tests)
}

func TestTouching(t *testing.T) {
	input := `
><>♡(><fysh>♡<{{{(())}}}><<{{{(())}}}><><)))>♡><)))><FYSH><><)))>♡)<><
`
	tests := []tt{
		lit(fysh.LFysh),
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
		lit(fysh.RFysh),
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
//
// TEST_CASE("Arrays") {
//   FyshLexer lexer{"><fysh> = [ ><{}o> - ><{}o> ] ~"};
//
//   IDENT("fysh");
//   T(S::ASSIGN);
//   T(S::FYSH_TANK_OPEN);
//   T(3);
//   T(S::FYSH_FOOD);
//   T(3);
//   T(S::FYSH_TANK_CLOSE);
//   T(S::FYSH_WATER);
//   T(S::END);
// }
//
// TEST_CASE("Submarines (SUBroutines)") {
//   FyshLexer lexer{">(submarine) (submarine)<"};
//   SUB_DIR("submarine", false);
//   SUB_DIR("submarine", true);
// }
//
// TEST_CASE("BABY SQUID (Return)") {
//   FyshLexer lexer{R"(
//   >(submarine) ><fysh>
//   ><>
//     >><fysh> ~
//     <~ <fysh>< ~
//     🦑🦑
//     ~<~<fysh><~
//   <><
//   )"};
//   // clang-format off
//   SUB_DIR("submarine", false); IDENT_DIR("fysh", false);
//   T(S::FYSH_OPEN);
//   Fysh fysh{lexer.nextFysh()};
//   CHECK(fysh == "fysh"); CHECK(fysh == S::INCREMENT); T(S::FYSH_WATER);
//   T(S::SQUID); IDENT_DIR("fysh", true); T(S::FYSH_WATER);
//   T(S::SQUID); T(S::SQUID);
//   T(S::FYSH_WATER); T(S::SQUID); IDENT_DIR("fysh", true); T(S::FYSH_WATER);
//   T(S::FYSH_CLOSE);
//   T(S::END);
//   // clang-format on
// }
//
// TEST_CASE("Contributors") {
//   FyshLexer lexer{"><Contributors> ≈ [ ><Kyle Prince> - ><Charles Ancheta> - "
//                   "><Yahya Al-Shamali>] ~"};
//   IDENT("Contributors");
//   T(S::ASSIGN);
//   T(S::FYSH_TANK_OPEN);
//   IDENT("Kyle Prince");
//   T(S::FYSH_FOOD);
//   IDENT("Charles Ancheta");
//   T(S::FYSH_FOOD);
//   IDENT("Yahya Al-Shamali");
//   T(S::FYSH_TANK_CLOSE);
//   T(S::FYSH_WATER);
//   T(S::END);
// }
//
// TEST_CASE("Floats") {
//   FyshLexer lexer{
//       "><}-}-}> <}-}-}>< ><}}-})-})}o> ><}--}> <}--}>< "
//       "><}--------------------------------> <o->< <->< ><-o> ><-> ><---------> "
//       " ><---------o>  <o--------->< <--------->< ><-{> <-{>< ><-{oo> <oo-{><"};
//   F(1.11);
//   F(-1.11);
//   F(3.25);
//   F(1.01);
//   F(-1.01);
//   F(1);
//   F(0);
//   F(0);
//   F(0);
//   F(0);
//   F(0);
//   F(0);
//   F(0);
//   F(0);
//   F(0.1);
//   F(-0.1);
//   F(0.1);
//   F(-0.1);
//   T(S::END);
// }

func testScanner(t testing.TB, input string, tests []tt) {
	t.Helper()
	s := scanner.New(input)

	for i, tt := range tests {
		tok := s.NextFysh()

		if tok.Type != tt.expectedType {
			t.Fatalf("tests[%d] - tokentype wrong. expected=%q, got=%q",
				i, tt.expectedType, tok.Type)
		}

		if tok.Value != tt.expectedValue {
			t.Fatalf("tests[%d] - literal wrong. expected=%q, got=%q",
				i, tt.expectedValue, tok)
		}
	}
}
