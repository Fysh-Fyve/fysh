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

bool fysh::ast::operator!=(const FyshExpr &expr, const char *str) {
  return !(expr == str);
}

std::string std::to_string(const fysh::ast::FyshProgram &f) {
  using namespace fysh::ast;
  std::string s;
  for (const auto &stmt : f) {
    std::visit(
        [&s](auto &&arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, Error>) {
            s += "ERROR(\"" + std::to_string(*arg.t) + "\")";
          } else if constexpr (std::is_same_v<T, FyshStmt>) {
            s += std::to_string(arg);
          } else if constexpr (std::is_same_v<T, SUBroutine>) {
            s += "sub " + std::string(arg.name) + "(";
            bool first{true};
            for (auto const &param : arg.parameters) {
              s += (first ? first = false, "" : ", ") + std::string(param);
            }
            s += ")\n" + std::to_string(arg.body);
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        stmt);
  }
  return s;
}

std::string std::to_string(const fysh::ast::FyshExpr &f) {
  using namespace fysh::ast;
  return std::visit(
      [](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Error>) {
          return "ERROR(\"" + std::to_string(*arg.t) + "\")";
        } else if constexpr (std::is_same_v<T, Box<FyshBinaryExpr>>) {
          return "(" + std::to_string(arg.t->left) + " " + str(arg.t->op) +
                 " " + std::to_string(arg.t->right) + ")";
        } else if constexpr (std::is_same_v<T, Box<FyshCallExpr>>) {
          bool first{true};
          std::string s;
          for (auto const &param : arg.t->args) {
            s += (first ? first = false, "" : ", ") + std::to_string(param);
          }
          s += ")";
          return (arg.t->negate ? "-" : "") + std::string(arg.t->callee) + "(" +
                 s;
        } else if constexpr (std::is_same_v<T, Aquarium>) {
          bool first{true};
          std::string s = "[";
          for (auto const &f : arg) {
            s += (first ? first = false, "" : ", ") + std::to_string(f);
          }
          s += "]";
          return s;
        } else if constexpr (std::is_same_v<T, Box<FyshUnaryExpr>>) {
          return "(" + std::to_string(arg.t->op) + "" +
                 std::to_string(arg.t->expr) + ")";
        } else if constexpr (std::is_same_v<T, FyshIdentifier>) {
          return std::string(arg.name);
        } else if constexpr (std::is_same_v<T, FyshLiteral>) {
          return std::to_string(arg.num);
        } else if constexpr (std::is_same_v<T, FyshFloatLiteral>) {
          return std::to_string(arg.num);
        } else if constexpr (std::is_same_v<T, GrilledFysh>) {
          return "><###>";
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      f);
}

std::string std::to_string(const fysh::ast::FyshStmt &f) {
  using namespace fysh::ast;
  return std::visit(
      [](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Error>)
          return "ERROR(\"" + std::to_string(*arg.t) + "\");";
        else if constexpr (std::is_same_v<T, FyshExpr>)
          return std::to_string(arg) + ";\n";
        else if constexpr (std::is_same_v<T, FyshAssignmentStmt>)
          return std::to_string(arg.left) + " = " + std::to_string(arg.right) +
                 ";\n";
        else if constexpr (std::is_same_v<T, FyshBlock>) {
          std::string s = "{\n";
          for (const FyshStmt &a : arg) {
            s += std::to_string(a);
          }
          return s + "}\n";
        } else if constexpr (std::is_same_v<T, FyshIncrementStmt>)
          return std::to_string(arg.expr) + "++;\n";
        else if constexpr (std::is_same_v<T, FyshDecrementStmt>)
          return std::to_string(arg.expr) + "--;\n";
        else if constexpr (std::is_same_v<T, FyshLoopStmt>)
          return "while (" + std::to_string(arg.condition) + ")\n" +
                 std::to_string(arg.body);
        else if constexpr (std::is_same_v<T, FyshIfStmt>) {
          return "if (" + std::to_string(arg.condition) + ")\n" +
                 std::to_string(arg.consequence) +
                 (arg.alternative.has_value()
                      ? ("else\n" + std::to_string(arg.alternative.value()))
                      : "");
        } else if constexpr (std::is_same_v<T, FyshAnchorStmt>) {
          return std::to_string(arg.op) + " " + std::to_string(arg.right) +
                 ";\n";
        } else if constexpr (std::is_same_v<T, Squid>) {
          return "return " + std::to_string(arg.expr) + ";\n";
        } else if constexpr (std::is_same_v<T, BrokenFysh>) {
          return "break;\n";
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
      },
      f);
}

bool fysh::ast::operator==(const fysh::ast::FyshExpr &expr, const char *str) {
  return std::to_string(expr) == str;
}
