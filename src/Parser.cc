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

fysh::ast::Error fysh::expectFysh(fysh::Species species) {
  std::stringstream ss;
  ss << "Expected " << species;
  return ss.str();
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
    // TODO: Parse expression, not just a literal.
    if (curFysh != Species::FYSH_LITERAL) {
      return expectFysh(Species::FYSH_LITERAL);
    }
    ast::FyshLiteral value{curFysh.getValue().value()};
    nextFysh();
    return terminateStatement(ast::FyshAssignmentStmt{ident, value});
  }

  return ast::Error{"unimplemented"};
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