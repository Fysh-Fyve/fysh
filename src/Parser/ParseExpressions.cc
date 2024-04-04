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
 * \file ParseExpressions.cc
 */
#include "../Lexer/Fysh/Species.h"
#include "AST/AST.h"
#include "Parser.h"

#include <string>
#include <vector>

using FB = fysh::ast::FyshBinary;

fysh::ast::FyshExpr fysh::FyshParser::parsePrimary() {
  switch (curFysh.getSpecies()) {
  case Species::FYSH_LITERAL: {
    ast::FyshLiteral value{curFysh.getValue().value()};
    bool negate{curFysh.negate};
    nextFysh();
    if (negate) {
      return ast::FyshUnaryExpr{ast::FyshUnary::Neg, value};
    }
    return value;
  }

  case Species::FYSH_BONES: {
    ast::FyshFloatLiteral value{curFysh.getFloat().value()};
    bool negate{curFysh.negate};
    nextFysh();
    if (negate) {
      return ast::FyshUnaryExpr{ast::FyshUnary::Neg, value};
    }
    return value;
  }

  case Species::FYSH_IDENTIFIER: {
    ast::FyshIdentifier ident{curFysh.getBody()};
    bool negate{curFysh.negate};
    nextFysh();
    if (negate) {
      return ast::FyshUnaryExpr{ast::FyshUnary::Neg, ident};
    }
    return ident;
  }
  case Species::GRILLED_FYSH: {
    nextFysh();
    return ast::GrilledFysh{};
  }
  case Species::FYSH_BOWL_OPEN: {
    nextFysh();
    ast::FyshExpr expr{parseExpression()};
    if (curFysh != Species::FYSH_BOWL_CLOSE) {
      return expectFysh(Species::FYSH_BOWL_CLOSE);
    }
    nextFysh();
    return expr;
  }
  case Species::FYSH_TANK_OPEN: {
    nextFysh();

    std::optional<std::string_view> callee;
    bool negate;
    std::vector<ast::FyshExpr> args;
    while (curFysh != Species::FYSH_TANK_CLOSE) {
      if (curFysh == Species::SUBMARINE) {
        if (callee.has_value()) {
          return ast::Error{"ambiguous call"};
        }
        callee = curFysh.getBody();
        negate = curFysh.negate;
        nextFysh();
        if (curFysh == Species::FYSH_FOOD) {
          nextFysh();
        }
      } else {
        args.push_back(parseExpression());
        if (curFysh == Species::FYSH_FOOD) {
          nextFysh();
        }
      }
    }
    nextFysh();
    if (!callee.has_value()) {
      return args;
    }
    return ast::FyshCallExpr{callee.value(), args};
  }
  default: {
    return parseError();
  }
  }
}

fysh::ast::FyshExpr fysh::FyshParser::parseMultiplicative() {
  ast::FyshExpr left{parsePrimary()};
  std::optional<FB> op{binaryOp(curFysh)};
  while (op == FB::Mul || op == FB::Div || op == FB::ShiftLeft ||
         op == FB::ShiftRight || op == FB::BitwiseAnd) {
    nextFysh();
    ast::FyshExpr right{parseMultiplicative()};
    left = ast::FyshBinaryExpr{left, right, op.value()};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseAdditive() {
  ast::FyshExpr left{parseMultiplicative()};
  std::optional<FB> op{binaryOp(curFysh)};
  using S = Species;
  while (op == FB::BitwiseOr || op == FB::BitwiseXor ||
         (!op.has_value() &&
          !curFysh.isOneOf(S::FYSH_WATER, S::FYSH_BOWL_CLOSE,
                           S::FYSH_TANK_CLOSE, S::SUBMARINE, S::FYSH_FOOD))) {
    if (op.has_value()) {
      nextFysh();
    }
    ast::FyshExpr right{parseAdditive()};
    left = ast::FyshBinaryExpr{left, right, op.value_or(FB::Add)};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseComparative() {
  ast::FyshExpr left{parseAdditive()};
  std::optional<FB> op{binaryOp(curFysh)};
  while (op == FB::LT || op == FB::GT || op == FB::LTE || op == FB::GTE ||
         op == FB::Equal || op == FB::NotEqual) {
    nextFysh();
    ast::FyshExpr right{parseComparative()};
    left = ast::FyshBinaryExpr{left, right, op.value()};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseAnchor() {
  ast::FyshExpr left{parseComparative()};
  std::optional<FB> op{binaryOp(curFysh)};
  while (op == FB::AnchorIn || op == FB::AnchorOut) {
    nextFysh();
    ast::FyshExpr right{parseAnchor()};
    left = ast::FyshBinaryExpr{left, right, op.value()};
    op = binaryOp(curFysh);
  }
  return left;
}

fysh::ast::FyshExpr fysh::FyshParser::parseExpression() {
  return parseAnchor();
}
