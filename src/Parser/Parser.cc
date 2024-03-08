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
#include "../AST/AST.h"
#include "../Fysh/Species.h"

#include <iostream>
#include <sstream>
#include <variant>
#include <vector>

fysh::FyshParser::FyshParser(fysh::FyshLexer lexer) : lexer(lexer) {
  nextFysh(); // curFysh
  nextFysh(); // peekFysh
}

void fysh::FyshParser::nextFysh() {
  curFysh = peekFysh;
  do {
    peekFysh = lexer.nextFysh();

    if ((peekFysh == Species::COMMENT ||
         peekFysh == Species::MULTILINE_COMMENT) &&
        peekFysh.getBody() == "fysh bad") {
      // >:(
      int *p{nullptr};
      std::cout << *p;
    }

    // Skip all comment tokens for now
    // maybe we'll do something with them eventually?
  } while (peekFysh == Species::COMMENT ||
           peekFysh == Species::MULTILINE_COMMENT);
}

fysh::ast::Error fysh::FyshParser::expectFysh(fysh::Species species) {
  std::stringstream ss;
  ss << "Expected " << species << " at line " << lexer.fyshingLine();
  return ss.str();
}

fysh::ast::FyshExpr fysh::FyshParser::parsePrimary() {
  if (curFysh == Species::FYSH_LITERAL) {
    ast::FyshLiteral value{curFysh.getValue().value()};
    bool negate{curFysh.negate};
    nextFysh();
    if (negate) {
      return ast::FyshUnaryExpr{ast::FyshUnary::Neg, value};
    }
    return value;
  } else if (curFysh == Species::FYSH_IDENTIFIER) {
    ast::FyshIdentifier ident{curFysh.getBody()};
    bool negate{curFysh.negate};
    nextFysh();
    if (negate) {
      return ast::FyshUnaryExpr{ast::FyshUnary::Neg, ident};
    }
    return ident;
  } else if (curFysh == Species::FYSH_BOWL_OPEN) {
    nextFysh();
    ast::FyshExpr expr{parseExpression()};
    if (curFysh != Species::FYSH_BOWL_CLOSE) {
      return expectFysh(Species::FYSH_BOWL_CLOSE);
    }
    nextFysh();
    return expr;
  }
  std::stringstream ss;
  ss << "Parser error at line " << lexer.fyshingLine();
  return ast::Error{ss.str()};
}

static std::optional<fysh::ast::FyshBinary> binaryOp(fysh::Fysh fysh) {
  using fysh::Species;
  using fysh::ast::FyshBinary;
  switch (fysh.getSpecies()) {
    // clang-format off
  case Species::HEART_MULTIPLY: return FyshBinary::Mul;
  case Species::HEART_DIVIDE:   return FyshBinary::Div;
  case Species::TADPOLE_LT:     return FyshBinary::LT;
  case Species::TADPOLE_GT:     return FyshBinary::GT;
  case Species::TADPOLE_LTE:    return FyshBinary::LTE;
  case Species::TADPOLE_GTE:    return FyshBinary::GTE;
  case Species::EQUAL:          return FyshBinary::Equal;
  case Species::NOT_EQUAL:      return FyshBinary::NotEqual;
  case Species::BITWISE_AND:    return FyshBinary::BitwiseAnd;
  case Species::BITWISE_OR:     return FyshBinary::BitwiseOr;
  case Species::CARET:          return FyshBinary::BitwiseXor;
  case Species::SHIFT_LEFT:     return FyshBinary::ShiftLeft;
  case Species::SHIFT_RIGHT:    return FyshBinary::ShiftRight;
    // clang-format on
  default:
    return {};
  }
}

fysh::ast::FyshExpr fysh::FyshParser::parseMultiplicative() {
  ast::FyshExpr left{parsePrimary()};
  std::optional<ast::FyshBinary> op{binaryOp(curFysh)};
  while (op == ast::FyshBinary::Mul || op == ast::FyshBinary::Div ||
         op == ast::FyshBinary::ShiftLeft ||
         op == ast::FyshBinary::ShiftRight ||
         op == ast::FyshBinary::BitwiseAnd) {
    nextFysh();
    ast::FyshExpr right{parseMultiplicative()};
    left = ast::FyshBinaryExpr{left, right, op.value()};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseAdditive() {
  ast::FyshExpr left{parseMultiplicative()};
  std::optional<ast::FyshBinary> op{binaryOp(curFysh)};
  while (
      op == ast::FyshBinary::BitwiseOr || op == ast::FyshBinary::BitwiseXor ||
      // TODO: This might break when it comes to parsing unaries, not sure yet
      (!op.has_value() && curFysh != Species::FYSH_WATER &&
       curFysh != Species::FYSH_BOWL_CLOSE &&
       curFysh != Species::FYSH_TANK_CLOSE)) {
    if (op.has_value()) {
      nextFysh();
    }
    ast::FyshExpr right{parseAdditive()};
    left = ast::FyshBinaryExpr{left, right, op.value_or(ast::FyshBinary::Add)};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseComparative() {
  ast::FyshExpr left{parseAdditive()};
  std::optional<ast::FyshBinary> op{binaryOp(curFysh)};
  while (op == ast::FyshBinary::LT || op == ast::FyshBinary::GT ||
         op == ast::FyshBinary::LTE || op == ast::FyshBinary::GTE) {
    nextFysh();
    ast::FyshExpr right{parseComparative()};
    left = ast::FyshBinaryExpr{left, right, op.value()};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseExpression() {
  return parseComparative();
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
    ast::FyshExpr expr{parseExpression()};
    if (std::holds_alternative<ast::Error>(expr)) {
      return std::get<ast::Error>(expr);
    }
    return terminateStatement(ast::FyshAssignmentStmt{ident, expr});
  } else if (curFysh == Species::FYSH_LOOP) {
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
    ast::FyshBlock block{parseBlock()};
    if (block.size() == 1 && std::holds_alternative<ast::Error>(block[0])) {
      return block[0];
    }
    if (curFysh != Species::FYSH_CLOSE) {
      return expectFysh(Species::FYSH_CLOSE);
    }
    nextFysh();
    return ast::FyshLoopStmt{condition, block};
  } else {
    return terminateStatement(parseExpression());
  }
}

std::vector<fysh::ast::FyshStmt> fysh::FyshParser::parseProgram() {
  return parseBlock();
}

std::vector<fysh::ast::FyshStmt> fysh::FyshParser::parseBlock() {
  std::vector<fysh::ast::FyshStmt> program;

  while ((curFysh != Species::END) && (curFysh != Species::FYSH_CLOSE)) {
    fysh::ast::FyshStmt stmt{parseStatement()};
    if (std::holds_alternative<ast::Error>(stmt)) {
      return {stmt};
    }
    program.push_back(stmt);
  }

  return program;
}