package scanner_test

import (
	"strings"
	"testing"

	"github.com/cbebe/go-fysh/fysh"
	"github.com/cbebe/go-fysh/scanner"
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
><factorial> = ><(({o> ~  ><//> b001 = 1

><//> while number > 1
><(((@> [><number> o~ ><(({o>]
><>
	><//> factorial = factorial * number
	><factorial> = ><factorial> <3 ><number> ~

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
		{fysh.Scales, "><(({o>"},
		lit(fysh.Water),
		{fysh.Comment, "><//> b001 = 1\n"},
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
		{fysh.Ident, "><factorial>"},
		lit(fysh.Mul),
		{fysh.Ident, "><number>"},
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

func TestBiblicallyAccurateFysh(t *testing.T) {
	input := `
><{{{oo> ~
><{{{°o°> ~
`
	tests := []tt{
		{fysh.Scales, "><{{{oo>"},
		lit(fysh.Water),
		{fysh.Scales, "><{{{°o°>"},
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
	testScanner(t, input, tests)
}

func TestHearts(t *testing.T) {
	hearts := [...]string{
		"💝", "☙", "♡", "♥", "❣", "❤", "❥", "❦", "❧", "🎔", "🖤", "💙",
		"💚", "💛", "💜", "🧡", "🤍", "🤎", "🩶", "🩷", "🩵", "💓", "💕",
		"💖", "💗", "💘", "🫀", "💌", "💞", "💟", "🫶", "<3",
	}
	tests := make([]tt, 0, len(hearts))
	for i := 0; i < len(hearts); i++ {
		tests = append(tests, lit(fysh.Mul))
	}
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
        ><{{(((o> (+o ><(> ~
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

// TODO: Pass original test cases

// TEST_CASE("biblically accurate fysh") {
//   FyshLexer lexer{"><{{oooo> <ooooooooo}}>< ><oolong> <oomph>< ><(°o°>"};
//
//   T(0b011);
//   T(-0b011);
//   IDENT_DIR("oolong", false);
//   IDENT_DIR("oomph", true);
//   T(0);
//
//   T(S::END);
// }
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
// TEST_CASE("random fysh") {
//   FyshLexer lexer{"><##> ><###> ><####> <###><"};
//
//   INVALID("><##>");
//   T(S::GRILLED_FYSH);
//   INVALID("><####>");
//   INVALID("<###><");
//   T(S::END);
// }
//
// TEST_CASE("fysh eye") {
//   FyshLexer lexer{"><{{({(°> <3 <°})}>< <°})}><"};
//
//   T(0b011010);
//   T(S::HEART_MULTIPLY);
//   T(-0b0101);
//   T(-0b0101);
//   T(S::END);
// }
//
// TEST_CASE("negative fysh") {
//   FyshLexer lexer{"><{{({(o> <3 <o})}>< <o})}><"};
//
//   T(0b011010);
//   T(S::HEART_MULTIPLY);
//   T(-0b0101);
//   T(-0b0101);
//   T(S::END);
// }
//
// TEST_CASE("weird fysh") {
//   FyshLexer lexer{"><{{({(> ><{)()}{)()}> <o{}{()}>< <{}{()}>< ><{}o>"};
//
//   T(0b011010);
//   T(0b01000110001);
//   T(-0b0111001);
//   T(-0b0111001);
//   T(0b011);
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
// TEST_CASE("identifiers") {
//   FyshLexer lexer{
//       "><pos> <neg>< ><ostart> <ostart>< ><鱼> ><とと> <魚>< "
//       "<سمكة>< ><ᜁᜐ᜔ᜇ> ><ᠨᡳᠮᠠᡥᠠ> ><𒐫> "
//       "><🐠🐟🐡🦈🐬🐳🐋🦐🦑🦞🦀🐙> "
//       "><𒈙>"
//       "><𓀐𓂸>"
//       "><under_scored>"
//       "><_under_scored>"
//       "><^-^>"
//       // "<°isthisallowed>< ><whataboutthis°>"
//   };
//
//   IDENT_DIR("pos", false);
//   IDENT_DIR("neg", true);
//   IDENT_DIR("ostart", false);
//   IDENT_DIR("ostart", true);
//   IDENT_DIR("鱼", false);
//   IDENT_DIR("とと", false);
//   IDENT_DIR("魚", true);
//   IDENT_DIR("سمكة", true);
//   IDENT_DIR("ᜁᜐ᜔ᜇ", false);
//   IDENT_DIR("ᠨᡳᠮᠠᡥᠠ", false);
//   IDENT_DIR("𒐫", false);
//   IDENT_DIR("🐠🐟🐡🦈🐬🐳🐋🦐🦑🦞🦀🐙", false);
//   IDENT_DIR("𒈙", false);
//   IDENT_DIR("𓀐𓂸", false);
//   IDENT_DIR("under_scored", false);
//   IDENT_DIR("_under_scored", false);
//   IDENT_DIR("^-^", false);
//
//   // Comment out until we decide what to do with it
//   // IDENT_DIR("°isthisallowed", true);
//   // IDENT_DIR("whataboutthis°", false);
//
//   T(S::END);
// }
//
// TEST_CASE("increment & decrement") {
//   FyshLexer lexer{">><inc> <dec><<"};
//
//   Fysh fysh{lexer.nextFysh()};
//   CHECK(fysh == "inc");
//   CHECK(fysh == S::INCREMENT);
//
//   fysh = lexer.nextFysh();
//   CHECK(fysh == "dec");
//   CHECK(fysh == S::DECREMENT);
//
//   T(S::END);
// }
//
// TEST_CASE("Terminate") {
//   FyshLexer lexer{"~ ~~"};
//
//   T(S::FYSH_WATER);
//   T(S::FYSH_WATER);
//   T(S::FYSH_WATER);
//   T(S::END);
// }
//
// TEST_CASE("Fysh Tank") {
//   FyshLexer lexer{"[]"};
//
//   T(S::FYSH_TANK_OPEN);
//   T(S::FYSH_TANK_CLOSE);
//   T(S::END);
// }
//
// TEST_CASE("Fysh If Else") {
//   FyshLexer lexer{R"(
// ><(((^> [ ><fysh> ] ><> <><
// ><(((*> ><(((^> [ ><result> ] ><> <><
// ><(((*> ><> <><
// )"};
//
//   T(S::IF);
//   T(S::FYSH_TANK_OPEN);
//   IDENT("fysh");
//   T(S::FYSH_TANK_CLOSE);
//   T(S::FYSH_OPEN);
//   T(S::FYSH_CLOSE);
//
//   T(S::ELSE);
//   T(S::IF);
//   T(S::FYSH_TANK_OPEN);
//   IDENT("result");
//   T(S::FYSH_TANK_CLOSE);
//   T(S::FYSH_OPEN);
//   T(S::FYSH_CLOSE);
//
//   T(S::ELSE);
//   T(S::FYSH_OPEN);
//   T(S::FYSH_CLOSE);
//
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
// TEST_CASE("Anchors") {
//   FyshLexer lexer{R"(
//   (+o ><fysh> ~
//   o+) ><fysh> ~
//   ><{{> (+o ><fysh> ~
//   ><{{> o+) ><fysh> ~
//   )"};
//
//   // clang-format off
//   T(S::ANCHOR_LEFT); IDENT("fysh"); T(S::FYSH_WATER);
//
//   T(S::ANCHOR_RIGHT); IDENT("fysh"); T(S::FYSH_WATER);
//
//   T(3); T(S::ANCHOR_LEFT); IDENT("fysh"); T(S::FYSH_WATER);
//
//   T(3); T(S::ANCHOR_RIGHT); IDENT("fysh"); T(S::FYSH_WATER);
//   // clang-format on
//
//   T(S::END);
// }
//
// TEST_CASE("Fysh Factorial") {
//   FyshLexer lexer{R"(
// ><fysh>   = ><{({o> ~
// ><result> = ><(({o> ~
//
// ><(((@> ><@> [ ><fysh> o~ ><(({o> ]
// ><>
// 	><result> = ><result> ♡ ><fysh> ~
// 	<fysh><< ~
// <><
// )"};
//
//   // clang-format off
//   IDENT("fysh"); T(S::ASSIGN); T(5); T(S::FYSH_WATER);
//
//   IDENT("result"); T(S::ASSIGN); T(1); T(S::FYSH_WATER);
//
//   T(S::FYSH_LOOP);
//   T(S::FYSH_LOOP);
//
//   T(S::FYSH_TANK_OPEN);
//     IDENT("fysh"); T(S::TADPOLE_GT); T(1);
//   T(S::FYSH_TANK_CLOSE);
//
//   T(S::FYSH_OPEN);
//
//     IDENT("result"); T(S::ASSIGN);
//       IDENT("result"); T(S::HEART_MULTIPLY); IDENT("fysh"); T(S::FYSH_WATER);
//
//     Fysh fysh{lexer.nextFysh()};
//     CHECK(fysh == "fysh");
//     CHECK(fysh == S::DECREMENT);
//     T(S::FYSH_WATER);
//
//   T(S::FYSH_CLOSE);
//
//   T(S::END);
//   // clang-format on
// }
//
// TEST_CASE("Comments") {
//   FyshLexer lexer{R"(
// ><//> This is a comment
// ></*>
// This is also a comment
// <*/><
// )"};
//
//   Fysh fysh{lexer.nextFysh()};
//   CHECK(fysh == "This is a comment");
//   CHECK(fysh == S::COMMENT);
//
//   fysh = lexer.nextFysh();
//   CHECK(fysh.getBody() == "This is also a comment");
//   CHECK(fysh == S::MULTI_COMMENT);
//
//   T(Species::END);
// }
//
// TEST_CASE("Fysh Bowl") {
//   FyshLexer lexer{"><> ♡ ( ><fysh> ♡ <{{{(())}}}>< ♡ ><fysh> ) <><"};
//
//   T(S::FYSH_OPEN);
//   T(S::HEART_MULTIPLY);
//   T(S::FYSH_BOWL_OPEN);
//   IDENT("fysh");
//   T(S::HEART_MULTIPLY);
//   T(-0b1110000111);
//   T(S::HEART_MULTIPLY);
//   IDENT("fysh");
//   T(S::FYSH_BOWL_CLOSE);
//   T(S::FYSH_CLOSE);
//   T(S::END);
// }
//
// TEST_CASE("TOUCHING") {
//   FyshLexer lexer{
//       "><>♡(><fysh>♡<{{{(())}}}><<{{{(())}}}><><)))>♡><)))><FYSH><><)))>♡)<><"};
//   // ><> ♡ ( ><fysh> ♡ <{{{(())}}}>< <{{{(())}}}>< ><)))> ♡ ><)))> <FYSH><
//   // ><)))> ♡ ) <><
//   T(S::FYSH_OPEN);
//   T(S::HEART_MULTIPLY);
//   T(S::FYSH_BOWL_OPEN);
//   IDENT_DIR("fysh", false);
//   T(S::HEART_MULTIPLY);
//   T(-0b1110000111);
//   T(-0b1110000111);
//   T(0b000);
//   T(S::HEART_MULTIPLY);
//   T(0b000);
//   IDENT_DIR("FYSH", true);
//   T(0b000);
//   T(S::HEART_MULTIPLY);
//   T(S::FYSH_BOWL_CLOSE);
//   T(S::FYSH_CLOSE);
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
// TEST_CASE("Broken Fysh") {
//   FyshLexer lexer{R"(><\/> <\/><)"};
//
//   T(S::BROKEN_FYSH);
//   T(S::BROKEN_FYSH);
//   T(S::END);
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

// // TODO: Do the other characters
// TEST_CASE("Zero Width Joiner") {
//   FyshLexer lexer{
//       "❤️ "
//       "❤️‍🔥 "
//       "❤️‍🩹 "
//       // "💝 "
//       // "❣️ "
//       // "🫶🏻 "
//       // "🫶🏽 "
//       // "🫶🏾 "
//       // "🫶🏿 "
//   };
//
//   T(S::HEART_MULTIPLY);
//   T(S::HEART_MULTIPLY);
//   T(S::HEART_MULTIPLY);
//   // T(S::HEART_MULTIPLY);
//   // T(S::HEART_MULTIPLY);
//
//   T(S::END);
// }
