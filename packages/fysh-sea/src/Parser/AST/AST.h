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
 * \file AST.h
 */
#ifndef FYSH_AST_H_
#define FYSH_AST_H_

#include "Box.h"
#include "Operators.h"
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

template <class> inline constexpr bool always_false_v = false;

namespace fysh::ast {
// TODO: Maybe make this more sophisticated?
using Error = Box<std::string>;

struct FyshBinaryExpr;
struct FyshUnaryExpr;
struct FyshCallExpr;
struct Aquarium;

// This is intentionally empty
struct GrilledFysh {};

// ><steven>
struct FyshIdentifier {
  std::string_view name;
};

// ><))}>
struct FyshLiteral {
  std::uint64_t num;
};

struct FyshFloatLiteral {
  double num;
};

// every single type of expression
using FyshExpr = std::variant<Error, Box<FyshCallExpr>, Box<FyshBinaryExpr>,
                              Box<FyshUnaryExpr>, FyshIdentifier, FyshLiteral,
                              FyshFloatLiteral, GrilledFysh, Aquarium>;

bool operator==(const FyshExpr &expr, const char *str);
bool operator!=(const FyshExpr &expr, const char *str);

struct Aquarium : public std::vector<FyshExpr> {
  using std::vector<FyshExpr>::vector;
  Aquarium(const std::vector<FyshExpr> &vec) : std::vector<FyshExpr>(vec) {}
};

// !Steven
struct FyshUnaryExpr {
  FyshUnary op;
  FyshExpr expr;
};

// 1 + 2, steven > 1
struct FyshBinaryExpr {
  FyshExpr left;
  FyshExpr right;
  FyshBinary op;
};

struct FyshCallExpr {
  std::string_view callee;
  std::vector<FyshExpr> args;
  bool negate;
};

//  >><steven>
struct FyshIncrementStmt {
  FyshExpr expr;
};

//  <steven><<
struct FyshDecrementStmt {
  FyshExpr expr;
};

// ><steven> = ><)})>
struct FyshAssignmentStmt {
  FyshExpr left;
  FyshExpr right;
};

// ><})}> (+o ><steven>
struct FyshAnchorStmt {
  FyshBinary op;
  FyshExpr right;
};

// <~ return operator
struct Squid {
  FyshExpr expr;
};

// ><\/> or <\/>< (break)
struct BrokenFysh {};

struct FyshBlock;
struct FyshLoopStmt;
struct FyshIfStmt;

using FyshStmt =
    std::variant<Error, FyshExpr, FyshIncrementStmt, FyshDecrementStmt,
                 FyshAssignmentStmt, FyshBlock, FyshLoopStmt, FyshIfStmt,
                 FyshAnchorStmt, Squid, BrokenFysh>;

struct FyshBlock {
  std::vector<FyshStmt> statements;
};

struct FyshLoopStmt {
  FyshExpr condition;
  std::vector<FyshStmt> body;
};

struct FyshIfStmt {
  FyshExpr condition;
  std::vector<FyshStmt> consequence;
  std::optional<std::vector<FyshStmt>> alternative;
};

struct SUBroutine {
  std::string_view name;
  std::vector<std::string_view> parameters;
  std::vector<FyshStmt> body;
};

using FyshSurfaceLevel = std::variant<Error, FyshStmt, SUBroutine>;

struct FyshProgram : std::vector<FyshSurfaceLevel> {
  std::optional<Error> getError() {
    if (this->size() == 1) {
      if (const Error *err = std::get_if<Error>(&(*this)[0])) {
        return *err;
      }
    }
    return {};
  }
};
}; // namespace fysh::ast

namespace std {
string to_string(const fysh::ast::FyshExpr &f);
string to_string(const fysh::ast::FyshStmt &f);
string to_string(const fysh::ast::FyshProgram &f);
string to_string(const vector<fysh::ast::FyshStmt> &f);
} // namespace std

#endif // !FYSH_AST_H_
