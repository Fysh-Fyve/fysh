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
 * \file AST.cc
 */
#include "AST.h"
#include <string>
#include <variant>

using namespace fysh::ast;

// #region TO_STRING[[[
template <typename T> static inline std::string ss(const T &arg) {
  return std::to_string(arg);
}

static inline std::string error(const Error &arg) {
  return "ERROR(\"" + ss(*arg.t) + "\")";
}

static inline std::string binary(const Box<FyshBinaryExpr> &arg) {
  return "(" + ss(arg.t->left) + " " + str(arg.t->op) + " " + ss(arg.t->right) +
         ")";
}

static inline std::string call(const Box<FyshCallExpr> &arg) {
  bool first{true};
  std::string s;
  for (auto const &param : arg.t->args) {
    s += (first ? first = false, "" : ", ") + ss(param);
  }
  s += ")";
  return (arg.t->negate ? "-" : "") + std::string(arg.t->callee) + "(" + s;
}

static inline std::string unary(const Box<FyshUnaryExpr> &arg) {
  return "(" + ss(arg.t->op) + " " + ss(arg.t->expr) + ")";
}

static inline std::string block(const FyshBlock &arg) {
  std::string s = "{\n";
  for (const FyshStmt &a : arg) {
    s += ss(a);
  }
  return s + "}\n";
}

static inline std::string ifStmt(const FyshIfStmt &arg) {
  return "if (" + ss(arg.condition) + ")\n" + ss(arg.consequence) +
         (arg.alternative.has_value() ? ("else\n" + ss(arg.alternative.value()))
                                      : "");
}

static inline std::string loop(const FyshLoopStmt &arg) {
  return "while (" + ss(arg.condition) + ")\n" + ss(arg.body);
}

static inline std::string anchor(const FyshAnchorStmt &arg) {
  return ss(arg.op) + " " + ss(arg.right) + ";\n";
}
// #endregion ]]]TO_STRING

bool fysh::ast::operator==(const FyshExpr &expr, const char *str) {
  return ss(expr) == str;
}

bool fysh::ast::operator!=(const FyshExpr &expr, const char *str) {
  return !(expr == str);
}

std::string std::to_string(const FyshProgram &f) {
  std::string s;
  for (const auto &stmt : f) {
    std::visit(
        [&s](auto &&arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, Error>) {
            s += error(*arg.t);
          } else if constexpr (std::is_same_v<T, FyshStmt>) {
            s += ss(arg);
          } else if constexpr (std::is_same_v<T, SUBroutine>) {
            s += "sub " + std::string(arg.name) + "(";
            bool first{true};
            for (auto const &param : arg.parameters) {
              s += (first ? first = false, "" : ", ") + std::string(param);
            }
            s += ")\n" + ss(arg.body);
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        stmt);
  }
  return s;
}

std::string std::to_string(const FyshExpr &f) {
  return std::visit(
      [](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
#define MATCH(TYPE, RESULT)                                                    \
  if constexpr (std::is_same_v<T, TYPE>)                                       \
    return RESULT;                                                             \
  else
        MATCH(Error, error(arg))
        MATCH(Box<FyshBinaryExpr>, binary(arg))
        MATCH(Box<FyshCallExpr>, call(arg))
        MATCH(Box<FyshUnaryExpr>, unary(arg))
        MATCH(FyshIdentifier, std::string(arg.name))
        MATCH(FyshLiteral, ss(arg.num))
        MATCH(FyshFloatLiteral, ss(arg.num))
        MATCH(GrilledFysh, "><###>")
        static_assert(always_false_v<T>, "non-exhaustive visitor!");
#undef MATCH
      },
      f);
}

std::string std::to_string(const FyshStmt &f) {
  return std::visit(
      [](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
#define MATCH(TYPE, RESULT)                                                    \
  if constexpr (std::is_same_v<T, TYPE>)                                       \
    return RESULT;                                                             \
  else
        MATCH(Error, error(*arg.t))
        MATCH(FyshExpr, ss(arg) + ";\n")
        MATCH(FyshAssignmentStmt, ss(arg.left) + " = " + ss(arg.right) + ";\n")
        MATCH(FyshBlock, block(arg))
        MATCH(FyshIncrementStmt, ss(arg.expr) + "++;\n")
        MATCH(FyshDecrementStmt, ss(arg.expr) + "--;\n")
        MATCH(FyshLoopStmt, loop(arg))
        MATCH(FyshIfStmt, ifStmt(arg))
        MATCH(FyshAnchorStmt, anchor(arg))
        MATCH(Squid, "return " + ss(arg.expr) + ";\n")
        MATCH(BrokenFysh, "break;\n")
        static_assert(always_false_v<T>, "non-exhaustive visitor!");
#undef MATCH
      },
      f);
}

// vim:foldmethod=marker foldmarker=[[[,]]]
