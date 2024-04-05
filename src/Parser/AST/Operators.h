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
 * \file Operators.h
 */
#ifndef FYSH_AST_OPERATORS_H_
#define FYSH_AST_OPERATORS_H_
#include <cassert>
#include <string>

namespace fysh::ast {
/**
 * all operators that take two arguments and return one (add, sub, greater than,
 * less than, bit shift, etc.)
 */
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
  LogicalAnd,
  LogicalOr,
  ShiftLeft,
  ShiftRight,
  AnchorIn,
  AnchorOut,
};

enum class FyshUnary {
  /*! \!True */
  Neg,
  BitwiseNot,
  LogicalNot,
};

constexpr const char *str(const FyshBinary op) {
  using FB = FyshBinary;
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
  case FB::LogicalAnd: return "&&";
  case FB::LogicalOr:  return "||";
  case FB::ShiftLeft:  return "<<";
  case FB::ShiftRight: return ">>";
  case FB::AnchorIn:   return "o+)";
  case FB::AnchorOut:  return "(+o";
    // clang-format on
  };
  assert(false);
  // should never be here
  return nullptr;
}

constexpr const char *str(const FyshUnary op) {
  switch (op) {
    //clang-format off
  case FyshUnary::Neg:
    return "-";
  case FyshUnary::BitwiseNot:
    return "~";
  case FyshUnary::LogicalNot:
    return "!";
    // clang-format on
  }

  assert(false);
  // should never be here
  return nullptr;
}
} // namespace fysh::ast

namespace std {
inline string to_string(const fysh::ast::FyshUnary &f) {
  return string(str(f));
}
inline string to_string(const fysh::ast::FyshBinary &f) {
  return string(str(f));
}
} // namespace std

#endif // !FYSH_AST_OPERATORS_H_
