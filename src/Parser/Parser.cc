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
#include "../Lexer/Fysh/Species.h"
#include "AST/AST.h"

#include <string>
#include <variant>
#include <vector>

using FB = fysh::ast::FyshBinary;

fysh::FyshParser::FyshParser(FyshLexer lexer) : lexer(lexer) {
  nextFysh(); // curFysh
  nextFysh(); // peekFysh
}

void fysh::FyshParser::nextFysh() {
  curFysh = peekFysh;
  do {
    peekFysh = lexer.nextFysh();

    if ((peekFysh.isOneOf(Species::COMMENT, Species::MULTI_COMMENT)) &&
        peekFysh.getBody() == "fysh bad") {
      // >:(
      volatile int *p{nullptr};
      *p += 1;
    }

    // Skip all comment tokens for now
    // maybe we'll do something with them eventually?
  } while (peekFysh.isOneOf(Species::COMMENT, Species::MULTI_COMMENT));
}

fysh::ast::FyshSurfaceLevel fysh::FyshParser::parseSUBroutine() {
  std::string_view name{curFysh.getBody()}; // Name of the subroutine
  std::vector<std::string_view> parameters;
  nextFysh();
  // Parse parameters
  while (curFysh != Species::FYSH_OPEN) {
    if (curFysh != Species::FYSH_IDENTIFIER) {
      return expectFysh(Species::FYSH_IDENTIFIER);
    }
    parameters.push_back(curFysh.getBody());
    nextFysh();
  }
  // Parse body
  nextFysh();
  ast::FyshBlock body{parseBlock()};
  if (body.size() == 1 && std::holds_alternative<ast::Error>(body[0])) {
    return body[0];
  }

  // Return the subroutine
  if (curFysh != Species::FYSH_CLOSE) {
    return expectFysh(Species::FYSH_CLOSE);
  } else {
    nextFysh();
    return ast::SUBroutine{name, parameters, body};
  }
}

// Parse entire program
fysh::ast::FyshProgram fysh::FyshParser::parseProgram() {
  fysh::ast::FyshProgram program;

  while ((curFysh != Species::END)) {
    if (curFysh == Species::SUBMARINE) {
      fysh::ast::FyshSurfaceLevel sub{parseSUBroutine()};
      if (std::holds_alternative<ast::Error>(sub)) {
        return {{sub}};
      }
      program.push_back(sub);
    } else {
      fysh::ast::FyshStmt stmt{parseStatement()};
      if (std::holds_alternative<ast::Error>(stmt)) {
        return {{stmt}};
      }
      program.push_back(stmt);
    }
  }
  return program;
}

fysh::ast::Error fysh::FyshParser::expectFysh(fysh::Species species) {
  return {"Expected " + std::to_string(species) + " at line " +
          std::to_string(lexer.fyshingLine())};
}

fysh::ast::Error fysh::FyshParser::parseError() {
  return {"Parser error at line " + std::to_string(lexer.fyshingLine())};
}

std::optional<fysh::ast::FyshBinary> fysh::binaryOp(const fysh::Fysh &fysh) {
  using S = fysh::Species;
  using FB = ast::FyshBinary;
  switch (fysh.getSpecies()) {
    // clang-format off
  case S::HEART_MULTIPLY: return FB::Mul;
  case S::HEART_DIVIDE:   return FB::Div;
  case S::TADPOLE_LT:     return FB::LT;
  case S::TADPOLE_GT:     return FB::GT;
  case S::TADPOLE_LTE:    return FB::LTE;
  case S::TADPOLE_GTE:    return FB::GTE;
  case S::EQUAL:          return FB::Equal;
  case S::NOT_EQUAL:      return FB::NotEqual;
  case S::BITWISE_AND:    return FB::BitwiseAnd;
  case S::BITWISE_OR:     return FB::BitwiseOr;
  case S::CARET:          return FB::BitwiseXor;
  case S::LOGICAL_AND:    return FB::LogicalAnd;
  case S::LOGICAL_OR:     return FB::LogicalOr;
  case S::SHIFT_LEFT:     return FB::ShiftLeft;
  case S::SHIFT_RIGHT:    return FB::ShiftRight;
  case S::ANCHOR_LEFT:    return FB::AnchorOut;
  case S::ANCHOR_RIGHT:   return FB::AnchorIn;
    // clang-format on
  default:
    return {};
  }
}

std::optional<fysh::ast::FyshUnary> fysh::unaryOp(const fysh::Fysh &fysh) {
  using S = fysh::Species;
  using FU = ast::FyshUnary;
  switch (fysh.getSpecies()) {
  // clang-format off
    case S::BITWISE_NOT: return FU::BitwiseNot;
    case S::LOGICAL_NOT: return FU::LogicalNot;
    // clang-format on
  }
}
