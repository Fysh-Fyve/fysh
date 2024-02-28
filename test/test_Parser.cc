#include "../src/Lexer.h"
#include "../src/Parser.h"
#include <iostream>

#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING

#include "doctest.h"
#include <variant>

using namespace fysh::ast;

void check_program(std::vector<FyshStmt> program, std::size_t size) {
  if (program.size() == 1) {
    if (std::holds_alternative<Error>(program[0])) {
      FAIL(std::get<Error>(program[0]).getraw());
    }
  }
  REQUIRE(program.size() == size);
}

template <typename T> T get_stmt(FyshStmt stmt) {
  REQUIRE(std::holds_alternative<T>(stmt));
  return std::get<T>(stmt);
}

template <typename T> T unwrap(FyshStmt stmt) {
  while (std::holds_alternative<FyshBlock>(stmt)) {
    stmt = std::get<FyshBlock>(stmt)[0];
  }
  return get_stmt<T>(stmt);
}

template <typename T> T get_expr(FyshStmt stmt) {
  auto expr{get_stmt<FyshExpr>(stmt)};
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

FyshExpr expr(const char *input) {
  fysh::FyshParser p{fysh::FyshLexer{input}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  return unwrap<FyshExpr>(program[0]);
}

TEST_CASE("Loop Statement") {
  fysh::FyshParser p{fysh::FyshLexer{R"(
><(((@> [ ><fysh> ]
><>
    ><((({o> ~
<><
  )"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{unwrap<FyshLoopStmt>(program[0])};
  check_ident(stmt.condition, "fysh");
  check_program(stmt.body, 1);
  CHECK(get_expr<FyshLiteral>(unwrap<FyshExpr>(stmt.body[0])).num == 1);
}

TEST_CASE("Assignment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"><fysh> = ><(({o> ~"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{unwrap<FyshAssignmentStmt>(program[0])};
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
  };
  for (const auto &[input, expected] : cases) {
    CHECK_EQ(expr(input), expected);
  }
}

TEST_CASE("Increment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{">><fysh> ~"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{unwrap<FyshIncrementStmt>(program[0])};
  check_ident(stmt.expr, "fysh");
}

TEST_CASE("Decrement Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"<fysh><< ~"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{unwrap<FyshDecrementStmt>(program[0])};
  check_ident(stmt.expr, "fysh");
}
