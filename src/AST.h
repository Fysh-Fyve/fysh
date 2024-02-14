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

#include <memory>
#include <string_view>
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

class FyshExpr {
public:
  virtual ~FyshExpr() = default;
};

class FyshBinaryExpr : public FyshExpr {
public:
  FyshBinaryExpr(std::unique_ptr<FyshExpr> left, FyshBinary op,
                 std::unique_ptr<FyshExpr> right)
      : left(std::move(left)), right(std::move(right)), op(op) {}
  std::unique_ptr<FyshExpr> left;
  std::unique_ptr<FyshExpr> right;
  FyshBinary op;
};

class FyshIdentifier : public FyshExpr {
public:
  FyshIdentifier(std::string_view name) : name(name) {}
  std::string_view name;
};

class FyshLiteral : public FyshExpr {
public:
  FyshLiteral(uint64_t num) : num(num) {}
  uint64_t num;
};

class FyshStmt {
public:
  virtual ~FyshStmt() = default;
};

class FyshExprStmt : public FyshStmt {
public:
  FyshExprStmt(std::unique_ptr<FyshExpr> expr) : expr(std::move(expr)) {}
  std::unique_ptr<FyshExpr> expr;
};
class FyshIncrementStmt : public FyshStmt {
public:
  FyshIncrementStmt(std::unique_ptr<FyshExpr> expr) : expr(std::move(expr)) {}
  std::unique_ptr<FyshExpr> expr;
};
class FyshDecrementStmt : public FyshStmt {
public:
  FyshDecrementStmt(std::unique_ptr<FyshExpr> expr) : expr(std::move(expr)) {}
  std::unique_ptr<FyshExpr> expr;
};

class FyshAssignmentStmt : public FyshStmt {
public:
  FyshAssignmentStmt(std::unique_ptr<FyshExpr> left,
                     std::unique_ptr<FyshExpr> right)
      : left(std::move(left)), right(std::move(right)) {}
  std::unique_ptr<FyshExpr> left;
  std::unique_ptr<FyshExpr> right;
};

class FyshBlock : public FyshStmt {
public:
  FyshBlock(std::vector<FyshStmt> statements)
      : statements(std::move(statements)) {}
  std::vector<FyshStmt> statements;
};

class FyshLoopStmt : public FyshStmt {
public:
  FyshLoopStmt(std::unique_ptr<FyshExpr> condition,
               std::unique_ptr<FyshBlock> body)
      : condition(std::move(condition)), body(std::move(body)) {}
  std::unique_ptr<FyshExpr> condition;
  std::unique_ptr<FyshBlock> body;
};

}; // namespace fysh::ast

#endif // !FYSH_AST_H_
