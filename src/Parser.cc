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

fysh::ast::FyshStmt fysh::FyshParser::parseStatement() {
  if (curFysh == Species::INCREMENT) {
    if (peekFysh != Species::TERMINATE) {
      return ast::FyshStmt{ast::Error{"Expected terminator"}};
    } else {
      ast::FyshIdentifier ident{curFysh.getBody()};
      nextFysh();
      nextFysh();
      return ast::FyshStmt{ast::FyshIncrementStmt{ident}};
    }
  } else if (curFysh == Species::DECREMENT) {
    if (peekFysh != Species::TERMINATE) {
      return ast::FyshStmt{ast::Error{"Expected terminator"}};
    } else {
      ast::FyshIdentifier ident{curFysh.getBody()};
      nextFysh();
      nextFysh();
      return ast::FyshStmt{ast::FyshDecrementStmt{ident}};
    }
  } else if (curFysh == Species::FYSH_IDENTIFIER &&
             peekFysh == Species::ASSIGN) {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    nextFysh();
    // TODO: Parse expression, not just a literal.
    if (curFysh != Species::FYSH_LITERAL) {
      return ast::FyshStmt{ast::Error{"Expected literal"}};
    }
    ast::FyshLiteral value{curFysh.getValue().value()};
    nextFysh();
    if (curFysh != Species::TERMINATE) {
      return ast::FyshStmt{ast::Error{"Expected terminator"}};
    } else {
      nextFysh();
      return ast::FyshStmt{ast::FyshAssignmentStmt{ident, value}};
    }
  }

  return ast::FyshStmt{ast::Error{"unimplemented"}};
}

std::vector<fysh::ast::FyshStmt> fysh::FyshParser::parseProgram() {
  std::vector<fysh::ast::FyshStmt> program{};

  while (curFysh != Species::END) {
    auto stmt{parseStatement()};
    if (!std::holds_alternative<ast::Error>(stmt)) {
      program.push_back(stmt);
    } else {
      return std::vector<fysh::ast::FyshStmt>{stmt};
    }
  }

  return program;
}
