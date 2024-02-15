#include "../src/Lexer.h"
#include "../src/Parser.h"

#include "doctest.h"
#include <variant>

using namespace fysh::ast;

template <typename T> T get_stmt(FyshStmt stmt) {
  REQUIRE(std::holds_alternative<T>(stmt));
  return std::get<T>(stmt);
}

template <typename T> T get_expr(FyshExpr expr) {
  REQUIRE(std::holds_alternative<T>(expr));
  return std::get<T>(expr);
}

TEST_CASE("Assignment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"><fysh> = ><(({o> ~"}};
  std::vector<FyshStmt> program{p.parseProgram()};
  REQUIRE(program.size() == 1);
  auto stmt{get_stmt<FyshAssignmentStmt>(program[0])};
  auto left{get_expr<FyshIdentifier>(stmt.left)};
  auto right{get_expr<FyshLiteral>(stmt.right)};
  CHECK(left.name == "fysh");
  CHECK(right.num == 1);
}

TEST_CASE("Expression Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"><(({o> ~"}};
  std::vector<FyshStmt> program{p.parseProgram()};
  REQUIRE(program.size() == 1);
  auto stmt{get_stmt<FyshExpr>(program[0])};
  auto expr{get_expr<FyshLiteral>(stmt)};
  CHECK(expr.num == 1);
}

TEST_CASE("Increment Statement") {
  fysh::FyshParser p{fysh::FyshLexer{">><fysh> ~"}};
  std::vector<FyshStmt> program{p.parseProgram()};
  REQUIRE(program.size() == 1);
  auto stmt{get_stmt<FyshIncrementStmt>(program[0])};
  auto expr{get_expr<FyshIdentifier>(stmt.expr)};
  CHECK(expr.name == "fysh");
}

TEST_CASE("Decrement Statement") {
  fysh::FyshParser p{fysh::FyshLexer{"<fysh><< ~"}};
  std::vector<FyshStmt> program{p.parseProgram()};
  REQUIRE(program.size() == 1);
  auto stmt{get_stmt<FyshDecrementStmt>(program[0])};
  auto expr{get_expr<FyshIdentifier>(stmt.expr)};
  CHECK(expr.name == "fysh");
}
