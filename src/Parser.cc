/**
 * Copyright (C) 2024 Yahya Al-Shamali, Kyle Prince, Charles Ancheta
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file Parser.cc
 */

#include "Parser.h"
#include "AST.h"

#include <sstream>
#include <variant>
#include <vector>

fysh::FyshParser::FyshParser(fysh::FyshLexer lexer) : lexer(lexer) {
  nextFysh(); // curFysh
  nextFysh(); // peekFysh
}

void fysh::FyshParser::nextFysh() {
  curFysh = peekFysh;
  peekFysh = lexer.nextFysh();
}

fysh::ast::Error fysh::FyshParser::expectFysh(fysh::Species species) {
  std::stringstream ss;
  ss << "Expected " << species << " at line " << lexer.fyshingLine();
  return ss.str();
}

fysh::ast::FyshExpr fysh::FyshParser::parseExpression() {
  // TODO: This is wrong, doesn't take into account any statements with more
  // than one expression involved
  if (curFysh == Species::FYSH_LITERAL) {
    ast::FyshLiteral value{curFysh.getValue().value()};
    nextFysh();
    return value;
  } else if (curFysh == Species::FYSH_IDENTIFIER) {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    return ident;
  }
  return ast::Error{"unimplemented"};
}

fysh::ast::FyshStmt fysh::FyshParser::parseStatement() {
  if (curFysh == Species::INCREMENT) {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    return terminateStatement(ast::FyshIncrementStmt{ident});
  } else if (curFysh == Species::DECREMENT) {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    return terminateStatement(ast::FyshDecrementStmt{ident});
  } else if (curFysh == Species::FYSH_IDENTIFIER &&
             peekFysh == Species::ASSIGN) {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    nextFysh();
    auto expr{parseExpression()};
    if (std::holds_alternative<ast::Error>(expr)) {
      return std::get<ast::Error>(expr);
    }
    return terminateStatement(ast::FyshAssignmentStmt{ident, expr});
  } else {
    return terminateStatement(parseExpression());
  }
}

std::vector<fysh::ast::FyshStmt> fysh::FyshParser::parseProgram() {
  std::vector<fysh::ast::FyshStmt> program;

  while (curFysh != Species::END) {
    auto stmt{parseStatement()};
    if (std::holds_alternative<ast::Error>(stmt)) {
      return {stmt};
    }
    program.push_back(stmt);
  }

  return program;
}
