#include "../src/Lexer/Lexer.h"
#include "../src/Parser/Parser.h"

#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING

#include "doctest.h"
#include <variant>

using namespace fysh::ast;

template <typename T> static void check_program(T program, std::size_t size) {
  if (program.size() == 1) {
    if (std::holds_alternative<Error>(program[0])) {
      FAIL(std::get<Error>(program[0]).getraw());
    }
  }
  REQUIRE(program.size() == size);
}

template <typename T> T get_stmt(FyshSurfaceLevel decl) {
  FyshStmt stmt{std::get<FyshStmt>(decl)};
  REQUIRE(std::holds_alternative<T>(stmt));
  return std::get<T>(stmt);
}

template <typename T> T unwrap(FyshSurfaceLevel decl) {
  FyshStmt stmt{std::get<FyshStmt>(decl)};
  while (std::holds_alternative<FyshBlock>(stmt)) {
    stmt = std::get<FyshBlock>(stmt)[0];
  }
  return get_stmt<T>(stmt);
}

inline std::vector<FyshStmt> unwrap_block(FyshStmt stmt) {
  FyshBlock block{std::get<FyshBlock>(stmt)};
  FyshStmt s{stmt};
  while (std::holds_alternative<FyshBlock>(s) &&
         std::holds_alternative<FyshBlock>(std::get<FyshBlock>(s)[0])) {
    s = std::get<FyshBlock>(s)[0];
  }
  return std::get<FyshBlock>(s);
}

template <typename T> T get_expr(FyshSurfaceLevel decl) {
  FyshStmt stmt{std::get<FyshStmt>(decl)};
  FyshExpr expr{get_stmt<FyshExpr>(stmt)};
  REQUIRE(std::holds_alternative<T>(expr));
  return std::get<T>(expr);
}

template <typename T> T get_expr(FyshExpr expr) {
  REQUIRE(std::holds_alternative<T>(expr));
  return std::get<T>(expr);
}

template <typename T> void check_ident(T expr, const char *name) {
  CHECK(get_expr<FyshIdentifier>(expr).name == name);
}

// #define EXPR_WACK

#ifdef EXPR_WACK
#include <iostream>
#endif

inline FyshExpr expr(const char *input) {
  fysh::FyshParser p{fysh::FyshLexer{input}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
#ifdef EXPR_WACK
  std::cout << std::to_string(unwrap<FyshExpr>(program[0]));
#undef EXPR_WACK
#endif
  return unwrap<FyshExpr>(program[0]);
}

TEST_CASE("Loop Statement") {
  fysh::FyshParser p{fysh::FyshLexer{R"(
><(((@> [ ><fysh> ]
><>
    ><((({o> ~
<><
  )"}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
  FyshLoopStmt stmt{unwrap<FyshLoopStmt>(program[0])};
  check_ident(stmt.condition, "fysh");
  check_program(stmt.body, 1);
  CHECK(get_expr<FyshLiteral>(unwrap<FyshExpr>(stmt.body[0])).num == 1);
}

TEST_CASE("Assignment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"><fysh> = ><(({o> ~"}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
  FyshAssignmentStmt stmt{unwrap<FyshAssignmentStmt>(program[0])};
  check_ident(stmt.left, "fysh");
  CHECK(get_expr<FyshLiteral>(stmt.right).num == 1);
}

TEST_CASE("Expression Statements") {
  struct TestCase {
    const char *input;
    const char *expected;
  };
  static const TestCase cases[] = {
      {"><(({o> ~", "1"},
      {"><fysh> ~", "fysh"},
      {"><fysh> <3 ><{({o> ~", "(fysh * 5)"},
      {"><fysh> ><{({o> <3 ><(({o> ~", "(fysh + (5 * 1))"},
      {"><fyshy> | ><{({o> ^ ><(({o> ~", "(fyshy | (5 ^ 1))"},
      {"><fysh1> ><fysh2> ><fysh3> ~", "(fysh1 + (fysh2 + fysh3))"},
      {"><{{> <3 ><{(({({> <3 ><{({{{{({{> ~", "(3 * (37 * 379))"},
      {"( ><{{> <3 ><{(({({> ) <3 ><{({{{{({{> ~", "((3 * 37) * 379)"},
      {"><fysh> o~ ><{({{{{({{> ~", "(fysh > 379)"},
      {"[>(sub) ><{({{{{({{>] ~", "sub(379)"},
      {"[><{({{{{({{>] ~", "[379]"},
      {"[><{({{{{({{> - ><{({{{{({{>] ~", "[379, 379]"},
      {"<{{{>< ~", "(-7)"},
      {"!!><}> ~", "(!1)"},
      {"!><}> ~", "(~1)"},
      {"!!!><}> ~", "(!(~1))"},
      {"!(!!><}>) ~", "(~(!1))"},

  };
  for (const auto &[input, expected] : cases) {
    CHECK_EQ(expr(input), expected);
  }
}

TEST_CASE("Increment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{">><fysh> ~"}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
  FyshIncrementStmt stmt{unwrap<FyshIncrementStmt>(program[0])};
  check_ident(stmt.expr, "fysh");
}

TEST_CASE("Decrement Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"<fysh><< ~"}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
  FyshDecrementStmt stmt{unwrap<FyshDecrementStmt>(program[0])};
  check_ident(stmt.expr, "fysh");
}

TEST_CASE("Break") {
  fysh::FyshParser p{fysh::FyshLexer{R"(><\/> ~)"}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
  BrokenFysh stmt{unwrap<BrokenFysh>(program[0])};
}

TEST_CASE("Subroutines") {
  fysh::FyshParser p{fysh::FyshLexer{R"(
>(foo) ><arg1>
><>
    o+) ><local> ~
    (+o ><local> ><arg1> ~
<><
  )"}};
  fysh::ast::FyshProgram program{p.parseProgram()};
  check_program(program, 1);
  REQUIRE(std::holds_alternative<SUBroutine>(program[0]));
  SUBroutine func{std::get<SUBroutine>(program[0])};
  CHECK(func.name == "foo");
  REQUIRE(func.parameters.size() == 1);
  CHECK(func.parameters[0] == "arg1");
  std::vector<FyshStmt> block = unwrap_block(func.body);
  check_program(block, 2);

  FyshAnchorStmt stmt{unwrap<FyshAnchorStmt>(block[0])};
  CHECK(stmt.op == FyshBinary::AnchorIn);
  check_ident(stmt.right, "local");

  stmt = unwrap<FyshAnchorStmt>(block[1]);
  CHECK(stmt.op == FyshBinary::AnchorOut);
  CHECK(stmt.right == "(local + arg1)");
}
