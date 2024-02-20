#include "../src/Lexer.h"
#include "../src/Parser.h"

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
  return get_stmt<FyshExpr>(program[0]);
}

TEST_CASE("Assignment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"><fysh> = ><(({o> ~"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{get_stmt<FyshAssignmentStmt>(program[0])};
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
  };
  for (const auto &[input, expected] : cases) {
    CHECK_EQ(expr(input), expected);
  }
}

TEST_CASE("Increment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{">><fysh> ~"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{get_stmt<FyshIncrementStmt>(program[0])};
  check_ident(stmt.expr, "fysh");
}

TEST_CASE("Decrement Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"<fysh><< ~"}};
  auto program{p.parseProgram()};
  check_program(program, 1);
  auto stmt{get_stmt<FyshDecrementStmt>(program[0])};
  check_ident(stmt.expr, "fysh");
}
