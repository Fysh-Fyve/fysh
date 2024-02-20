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
#include <string_view>
#include <variant>
#include <vector>

namespace fysh::ast {
// TODO: Maybe make this more sophisticated?
using Error = Box<std::string>;

// all operators that take two arguments and return one (add, sub, greater than,
// less than, bit shift, etc.)
enum class FyshBinary {
  Add,
  Sub,
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

struct FyshBlock;
struct FyshLoopStmt;
struct FyshIfStmt;

using FyshStmt =
    std::variant<Error, FyshExpr, FyshIncrementStmt, FyshDecrementStmt,
                 FyshAssignmentStmt, FyshBlock, FyshLoopStmt, FyshIfStmt>;

struct FyshBlock : public std::vector<FyshStmt> {
  using std::vector<FyshStmt>::vector;
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

}; // namespace fysh::ast

#endif // !FYSH_AST_H_
