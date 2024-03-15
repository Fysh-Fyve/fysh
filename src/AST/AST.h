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
#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>
#include <variant>
#include <vector>

template <class> inline constexpr bool always_false_v = false;

namespace fysh::ast {
// TODO: Maybe make this more sophisticated?
using Error = Box<std::string>;

// all operators that take two arguments and return one (add, sub, greater than,
// less than, bit shift, etc.)
enum class FyshBinary {
  Add,
  Mul,
  Div,
  Equal,
  NotEqual,
  GT,
  LT,
  GTE,
  LTE,
  BitwiseAnd,
  BitwiseOr,
  BitwiseXor,
  ShiftLeft,
  ShiftRight,
  AnchorIn,
  AnchorOut,
};

// !True
enum class FyshUnary {
  Neg,
};

struct FyshBinaryExpr;
struct FyshUnaryExpr;

// ><steven>
struct FyshIdentifier {
  std::string_view name;
};

// ><))}>
struct FyshLiteral {
  std::uint64_t num;
};

// every single type of expression
using FyshExpr = std::variant<Error, Box<FyshBinaryExpr>, Box<FyshUnaryExpr>,
                              FyshIdentifier, FyshLiteral>;

bool operator==(const FyshExpr &expr, const char *str);
bool operator!=(const FyshExpr &expr, const char *str);

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

//  >><steven>
struct FyshIncrementStmt {
  FyshExpr expr;
};

//  <steven><<
struct FyshDecrementStmt {
  FyshExpr expr;
};

struct FyshAssignmentStmt {
  FyshExpr left;
  FyshExpr right;
};

struct FyshAnchorStmt {
  FyshBinary op;
  FyshExpr right;
};

struct FyshBlock;
struct FyshLoopStmt;
struct FyshIfStmt;

using FyshStmt = std::variant<Error, FyshExpr, FyshIncrementStmt,
                              FyshDecrementStmt, FyshAssignmentStmt, FyshBlock,
                              FyshLoopStmt, FyshIfStmt, FyshAnchorStmt>;

struct FyshBlock : public std::vector<FyshStmt> {
  using std::vector<FyshStmt>::vector;
  FyshBlock(const std::vector<FyshStmt> &vec) : std::vector<FyshStmt>(vec) {}
};

struct FyshLoopStmt {
  FyshExpr condition;
  FyshBlock body;
};

struct FyshIfStmt {
  FyshExpr condition;
  FyshBlock consequence;
  std::optional<FyshBlock> alternative;
};

struct SUBroutine {
  std::string_view name;
  std::vector<std::string_view> parameters;
  FyshBlock body;
};

using FyshSurfaceLevel = std::variant<Error, FyshStmt, SUBroutine>;

using FyshProgram = std::vector<FyshSurfaceLevel>;

constexpr const char *toStr(const FyshBinary &op);
constexpr const char *toStr(const FyshUnary &op);

std::ostream &operator<<(std::ostream &os, const FyshExpr &f);
std::ostream &operator<<(std::ostream &os, const FyshStmt &f);
std::ostream &operator<<(std::ostream &os, const FyshProgram &f);

}; // namespace fysh::ast

#endif // !FYSH_AST_H_
