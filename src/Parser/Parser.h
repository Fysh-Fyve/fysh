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
 * \file Parser.h
 */
#ifndef FYSH_PARSER_H_
#define FYSH_PARSER_H_

#include "../Lexer/Lexer.h"
#include "AST/AST.h"

namespace fysh {
class FyshParser {

public:
  FyshParser(FyshLexer lexer);
  ast::FyshProgram parseProgram();

private:
  void nextFysh();

  // We're doing recursive descent, where the operator precedence is determined
  // by how deep it is in the call stack. Called earlier == Lower precedence.
  // Order of operations (same line means equal precedence):
  // - L_OR
  // - L_AND
  // - EQ, NEQ, LT, GT
  // - ADD, B_OR, XOR
  // - MUL, DIV, B_AND, SHIFTS
  // - UNARY (remember that this is applied in reverse)
  // - INDEX
  // - LITERAL, GROUP
  ast::FyshExpr parsePrimary();
  ast::FyshExpr parseIndex();
  ast::FyshExpr parseUnary();
  ast::FyshExpr parseMultiplicative();
  ast::FyshExpr parseAdditive();
  ast::FyshExpr parseComparative();
  ast::FyshExpr parseAnd();
  ast::FyshExpr parseOr();
  ast::FyshExpr parseAnchor();

  ast::FyshExpr parseExpression();
  ast::FyshStmt parseStatement();
  ast::FyshStmt parseLoop();
  ast::FyshStmt parseAssignment();
  ast::FyshStmt parseIfElse();
  std::vector<ast::FyshStmt> parseBlock();
  ast::FyshSurfaceLevel parseSUBroutine();

  ast::Error expectFysh(Species species);
  ast::Error parseError();

  template <typename T> ast::FyshStmt terminateStatement(T node) {
    if (curFysh != Species::FYSH_WATER) {
      return expectFysh(Species::FYSH_WATER);
    }
    nextFysh();
    return node;
  }

  FyshLexer lexer;
  Fysh curFysh;
  Fysh peekFysh;
};
}; // namespace fysh

#endif // !FYSH_PARSER_H_
