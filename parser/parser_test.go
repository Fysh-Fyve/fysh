package parser_test

import (
	"testing"

	"github.com/cbebe/go-fysh/parser"
	"github.com/cbebe/go-fysh/scanner"
)

type Test struct {
	statement string
}

func testProgram(t testing.TB, input string, tests []Test) {
	t.Helper()
	s := scanner.New(input)
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

func TestIncrement(t *testing.T) {
	input := `>><fysh> ~`
	tests := []Test{
		{"fysh++;"},
	}
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

func TestBlink(t *testing.T) {
	input := `
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
	tests := []Test{
		{"(24 (+o 1);"},
		{"o+) steven;"},
		{"if ((steven > 3)) {\nreturn steven;\n}"},
		{"while (1) {\n(24 (+o 1);\n(24 (+o 0);\n}"},
	}
	testProgram(t, input, tests)
}

// TODO: Pass original test cases

// TEST_CASE("Loop Statement") {
//   fysh::FyshParser p{fysh::FyshLexer{R"(
// ><(((@> [ ><fysh> ]
// ><>
//     ><((({o> ~
// <><
//   )"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   FyshLoopStmt stmt{unwrap<FyshLoopStmt>(program[0])};
//   check_ident(stmt.condition, "fysh");
//   check_program(stmt.body, 1);
//   CHECK(get_expr<FyshLiteral>(unwrap<FyshExpr>(stmt.body[0])).num == 1);
// }
//
// TEST_CASE("Loop Statement (with Fysh Bowl)") {
//   fysh::FyshParser p{fysh::FyshLexer{R"(
// ><(((@> ( ><fysh> )
// ><>
//     ><((({o> ~
// <><
//   )"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   FyshLoopStmt stmt{unwrap<FyshLoopStmt>(program[0])};
//   check_ident(stmt.condition, "fysh");
//   check_program(stmt.body, 1);
//   CHECK(get_expr<FyshLiteral>(unwrap<FyshExpr>(stmt.body[0])).num == 1);
// }
//
// TEST_CASE("Assignment Statement") {
//   fysh::FyshParser p{fysh::FyshLexer{"><fysh> = ><(({o> ~"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   FyshAssignmentStmt stmt{unwrap<FyshAssignmentStmt>(program[0])};
//   check_ident(stmt.left, "fysh");
//   CHECK(get_expr<FyshLiteral>(stmt.right).num == 1);
// }
//
// TEST_CASE("Expression Statements") {
//   struct TestCase {
//     const char *input;
//     const char *expected;
//   };
//   static const TestCase cases[] = {
//       {"><(({o> ~", "1"},
//       {"><fysh> ~", "fysh"},
//       {"><fysh> <3 ><{({o> ~", "(fysh * 5)"},
//       {"><fysh> ><{({o> <3 ><(({o> ~", "(fysh + (5 * 1))"},
//       {"><fyshy> | ><{({o> ^ ><(({o> ~", "(fyshy | (5 ^ 1))"},
//       {"><fysh1> ><fysh2> ><fysh3> ~", "(fysh1 + (fysh2 + fysh3))"},
//       {"><{{> <3 ><{(({({> <3 ><{({{{{({{> ~", "(3 * (37 * 379))"},
//       {"( ><{{> <3 ><{(({({> ) <3 ><{({{{{({{> ~", "((3 * 37) * 379)"},
//       {"><fysh> o~ ><{({{{{({{> ~", "(fysh > 379)"},
//       {"[>(sub) ><{({{{{({{>] ~", "sub(379)"},
//       {"[><{({{{{({{>] ~", "[379]"},
//       {"[><{({{{{({{> - ><{({{{{({{>] ~", "[379, 379]"},
//       {"<{{{>< ~", "(-7)"},
//       {"!!><}> ~", "(!1)"},
//       {"!><}> ~", "(~1)"},
//       {"!!!><}> ~", "(!(~1))"},
//       {"!(!!><}>) ~", "(~(!1))"},
//
//   };
//   for (const auto &[input, expected] : cases) {
//     CHECK_EQ(expr(input), expected);
//   }
// }
//
// TEST_CASE("Increment Statement") {
//   fysh::FyshParser p{fysh::FyshLexer{">><fysh> ~"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   FyshIncrementStmt stmt{unwrap<FyshIncrementStmt>(program[0])};
//   check_ident(stmt.expr, "fysh");
// }
//
// TEST_CASE("Decrement Statement") {
//   fysh::FyshParser p{fysh::FyshLexer{"<fysh><< ~"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   FyshDecrementStmt stmt{unwrap<FyshDecrementStmt>(program[0])};
//   check_ident(stmt.expr, "fysh");
// }
//
// TEST_CASE("Break") {
//   fysh::FyshParser p{fysh::FyshLexer{R"(><\/> ~)"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   BrokenFysh stmt{unwrap<BrokenFysh>(program[0])};
// }
//
// TEST_CASE("Subroutines") {
//   fysh::FyshParser p{fysh::FyshLexer{R"(
// >(foo) ><arg1>
// ><>
//     o+) ><local> ~
//     (+o ><local> ><arg1> ~
// <><
//   )"}};
//   fysh::ast::FyshProgram program{p.parseProgram()};
//   check_program(program, 1);
//   REQUIRE(std::holds_alternative<SUBroutine>(program[0]));
//   SUBroutine func{std::get<SUBroutine>(program[0])};
//   CHECK(func.name == "foo");
//   REQUIRE(func.parameters.size() == 1);
//   CHECK(func.parameters[0] == "arg1");
//   std::vector<FyshStmt> block = func.body;
//   check_program(block, 2);
//
//   FyshAnchorStmt stmt{unwrap<FyshAnchorStmt>(block[0])};
//   CHECK(stmt.op == FyshBinary::AnchorIn);
//   check_ident(stmt.right, "local");
//
//   stmt = unwrap<FyshAnchorStmt>(block[1]);
//   CHECK(stmt.op == FyshBinary::AnchorOut);
//   CHECK(stmt.right == "(local + arg1)");
// }
