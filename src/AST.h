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
#include <string_view>
#include <variant>
#include <vector>

namespace fysh::ast {
// TODO: Fill these up with more operations
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
};

// TODO: Fill these up with more operations
enum class FyshUnary {
  Neg,
};

struct FyshBinaryExpr;
struct FyshUnaryExpr;

struct FyshIdentifier {
  std::string_view name;
};

struct FyshLiteral {
  std::uint64_t num;
};

using FyshExpr = std::variant<Box<FyshBinaryExpr>, FyshIdentifier, FyshLiteral>;

struct FyshUnaryExpr {
  FyshUnary op;
  FyshExpr expr;
};

struct FyshBinaryExpr {
  FyshExpr left;
  FyshExpr right;
  FyshBinary op;
};

struct FyshIncrementStmt {
  FyshExpr expr;
};

struct FyshDecrementStmt {
  FyshExpr expr;
};

struct FyshAssignmentStmt {
  FyshExpr left;
  FyshExpr right;
};

struct FyshBlock;
struct FyshLoopStmt;

using FyshStmt = std::variant<FyshExpr, FyshIncrementStmt, FyshDecrementStmt,
                              FyshAssignmentStmt, FyshBlock, FyshLoopStmt>;

struct FyshBlock : public std::vector<FyshStmt> {
  using std::vector<FyshStmt>::vector;
};

struct FyshLoopStmt {
  FyshExpr condition;
  FyshBlock body;
};

}; // namespace fysh::ast

#endif // !FYSH_AST_H_
