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
#include <cassert>
#include <llvm/Support/raw_ostream.h>

constexpr const char *str(const fysh::ast::FyshBinary &op) {
  using FB = fysh::ast::FyshBinary;
  switch (op) {
    // clang-format off
  case FB::Add:        return "+";
  case FB::Mul:        return "*";
  case FB::Div:        return "/";
  case FB::Equal:      return "==";
  case FB::NotEqual:   return "!=";
  case FB::GT:         return ">";
  case FB::LT:         return "<";
  case FB::GTE:        return ">=";
  case FB::LTE:        return "<=";
  case FB::BitwiseAnd: return "&";
  case FB::BitwiseOr:  return "|";
  case FB::BitwiseXor: return "^";
  case FB::ShiftLeft:  return "<<";
  case FB::ShiftRight: return ">>";
  case FB::AnchorIn:   return "o+)";
  case FB::AnchorOut:  return "(+o";
    // clang-format on
  }

  assert(false);
}

constexpr const char *fysh::ast::toStr(const fysh::ast::FyshBinary &op) {
  return str(op);
}

constexpr const char *str(const fysh::ast::FyshUnary &op) {
  using fysh::ast::FyshUnary;
  switch (op) {
  case FyshUnary::Neg:
    return "-";
  }

  assert(false);
}

constexpr const char *fysh::ast::toStr(const fysh::ast::FyshUnary &op) {
  return str(op);
}

llvm::raw_ostream &fysh::ast::operator<<(llvm::raw_ostream &os,
                                         const fysh::ast::FyshExpr &f) {
  return std::visit(
      [&os](auto &&arg) -> llvm::raw_ostream & {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Error>) {
          os << "ERROR(\"" << *arg.t << "\")";
        } else if constexpr (std::is_same_v<T, Box<FyshBinaryExpr>>) {
          os << "(" << arg.t->left << " " << str(arg.t->op) << " "
             << arg.t->right << ")";
        } else if constexpr (std::is_same_v<T, Box<FyshUnaryExpr>>) {
          os << "(" << str(arg.t->op) << " " << arg.t->expr << ")";

        } else if constexpr (std::is_same_v<T, FyshIdentifier>) {
          os << arg.name;

        } else if constexpr (std::is_same_v<T, FyshLiteral>) {
          os << arg.num;

        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
        return os;
      },
      f);
}

llvm::raw_ostream &fysh::ast::operator<<(llvm::raw_ostream &os,
                                         const fysh::ast::FyshStmt &f) {
  return std::visit(
      [&os](auto &&arg) -> llvm::raw_ostream & {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Error>)
          os << "ERROR(\"" << *arg.t << "\");";
        else if constexpr (std::is_same_v<T, FyshExpr>)
          os << arg << ";\n";
        else if constexpr (std::is_same_v<T, FyshAssignmentStmt>)
          os << arg.left << " = " << arg.right << ";\n";
        else if constexpr (std::is_same_v<T, FyshBlock>) {
          os << "{\n";
          for (const ast::FyshStmt &a : arg) {
            os << a;
          }
          os << "}\n";
        } else if constexpr (std::is_same_v<T, FyshIncrementStmt>)
          os << arg.expr << "++;\n";
        else if constexpr (std::is_same_v<T, FyshDecrementStmt>)
          os << arg.expr << "--;\n";
        else if constexpr (std::is_same_v<T, FyshLoopStmt>)
          os << "while (" << arg.condition << ")\n" << arg.body;
        else if constexpr (std::is_same_v<T, FyshIfStmt>) {
          os << "if (" << arg.condition << ")\n" << arg.consequence;
          if (arg.alternative.has_value()) {
            os << "else\n" << arg.alternative.value();
          }
        } else if constexpr (std::is_same_v<T, FyshAnchorStmt>) {
          os << str(arg.op) << " " << arg.right << ";\n";
        } else if constexpr (std::is_same_v<T, Squid>) {
          os << "return " << arg.expr << ";\n";
        } else {
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
        return os;
      },
      f);
}

bool fysh::ast::operator==(const fysh::ast::FyshExpr &expr, const char *str) {
  std::string exprString;
  llvm::raw_string_ostream ss{exprString};
  ss << expr;
  return ss.str() == str;
}

bool fysh::ast::operator!=(const fysh::ast::FyshExpr &expr, const char *str) {
  return !(expr == str);
}

llvm::raw_ostream &fysh::ast::operator<<(llvm::raw_ostream &os,
                                         const fysh::ast::FyshProgram &f) {
  for (const auto &stmt : f) {
    std::visit(
        [&os](auto &&arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, Error>) {
            os << "ERROR(\"" << *arg.t << "\")";
          } else if constexpr (std::is_same_v<T, FyshStmt>) {
            os << arg;
          } else if constexpr (std::is_same_v<T, SUBroutine>) {
            os << "sub " << arg.name << "(";
            for (const auto &param : arg.parameters) {
              os << param << ", ";
            }
            os << ")\n" << arg.body;
          } else {
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
          }
        },
        stmt);
  }
  return os;
}
