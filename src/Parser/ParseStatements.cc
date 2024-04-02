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
 * \file ParseStatements.cc
 */
#include "../Lexer/Fysh/Species.h"
#include "AST/AST.h"
#include "Parser.h"

#include <variant>
#include <vector>

fysh::ast::FyshStmt fysh::FyshParser::parseLoop() {
  nextFysh();
  if (curFysh != Species::FYSH_TANK_OPEN) {
    return expectFysh(Species::FYSH_TANK_OPEN);
  }
  nextFysh();
  ast::FyshExpr condition{parseExpression()};
  if (curFysh != Species::FYSH_TANK_CLOSE) {
    return expectFysh(Species::FYSH_TANK_CLOSE);
  }
  nextFysh();
  if (curFysh != Species::FYSH_OPEN) {
    return expectFysh(Species::FYSH_OPEN);
  }
  nextFysh();
  std::vector<ast::FyshStmt> block{parseBlock()};
  if (block.size() == 1 && std::holds_alternative<ast::Error>(block[0])) {
    return block[0];
  }
  if (curFysh != Species::FYSH_CLOSE) {
    return expectFysh(Species::FYSH_CLOSE);
  }
  nextFysh();
  return ast::FyshLoopStmt{condition, block};
}

fysh::ast::FyshStmt fysh::FyshParser::parseStatement() {
  switch (curFysh.getSpecies()) {
  case Species::INCREMENT: {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    return terminateStatement(ast::FyshIncrementStmt{ident});
  }
  case Species::DECREMENT: {
    ast::FyshIdentifier ident{curFysh.getBody()};
    nextFysh();
    return terminateStatement(ast::FyshDecrementStmt{ident});
  }
  case Species::BROKEN_FYSH:
    nextFysh();
    return terminateStatement(ast::BrokenFysh{}); // Break statement

  case Species::FYSH_LOOP:
    return parseLoop();
  case Species::IF:
    return parseIfElse();
  case Species::ANCHOR_LEFT:
  case Species::ANCHOR_RIGHT: {
    // We know it's one of these two
    ast::FyshBinary op{binaryOp(curFysh).value()};
    nextFysh();
    return terminateStatement(ast::FyshAnchorStmt{op, parseExpression()});
  }
  case Species::SQUID: {
    nextFysh();
    return terminateStatement(ast::Squid{parseExpression()});
  }
  default: {
    if (curFysh == Species::FYSH_IDENTIFIER && peekFysh == Species::ASSIGN) {
      return parseAssignment();
    } else {
      return terminateStatement(parseExpression());
    }
  }
  }
}

std::vector<fysh::ast::FyshStmt> fysh::FyshParser::parseBlock() {
  std::vector<ast::FyshStmt> program;

  while ((curFysh != Species::END) && (curFysh != Species::FYSH_CLOSE)) {
    fysh::ast::FyshStmt stmt{parseStatement()};
    if (std::holds_alternative<ast::Error>(stmt)) {
      return {stmt};
    }
    program.push_back(stmt);
  }

  return program;
}

fysh::ast::FyshStmt fysh::FyshParser::parseIfElse() {
  nextFysh();
  if (curFysh != Species::FYSH_TANK_OPEN) {
    return expectFysh(Species::FYSH_TANK_OPEN);
  }
  nextFysh();
  ast::FyshExpr condition{parseExpression()};
  if (curFysh != Species::FYSH_TANK_CLOSE) {
    return expectFysh(Species::FYSH_TANK_CLOSE);
  }
  nextFysh();
  if (curFysh != Species::FYSH_OPEN) {
    return expectFysh(Species::FYSH_OPEN);
  }
  nextFysh();
  std::vector<ast::FyshStmt> consequence{parseBlock()};
  if (consequence.size() == 1 &&
      std::holds_alternative<ast::Error>(consequence[0])) {
    return consequence[0];
  }
  if (curFysh != Species::FYSH_CLOSE) {
    return expectFysh(Species::FYSH_CLOSE);
  }
  nextFysh();
  // No else statement
  if (curFysh != Species::ELSE) {
    return ast::FyshIfStmt{condition, consequence};
  }
  nextFysh();
  // Else if
  if (curFysh == Species::IF) {
    return ast::FyshIfStmt{condition, consequence,
                           ast::FyshBlock{parseIfElse()}};
  }
  // Else
  if (curFysh != Species::FYSH_OPEN) {
    return expectFysh(Species::FYSH_OPEN);
  }
  nextFysh();
  std::vector<ast::FyshStmt> alternative{parseBlock()};
  if (alternative.size() == 1 &&
      std::holds_alternative<ast::Error>(alternative[0])) {
    return alternative[0];
  }
  if (curFysh != Species::FYSH_CLOSE) {
    return expectFysh(Species::FYSH_CLOSE);
  }
  nextFysh();
  return ast::FyshIfStmt{condition, consequence, alternative};
}

fysh::ast::FyshStmt fysh::FyshParser::parseAssignment() {
  ast::FyshIdentifier ident{curFysh.getBody()};
  nextFysh();
  nextFysh();
  ast::FyshExpr expr{parseExpression()};
  if (std::holds_alternative<ast::Error>(expr)) {
    return std::get<ast::Error>(expr);
  }
  return terminateStatement(ast::FyshAssignmentStmt{ident, expr});
}
