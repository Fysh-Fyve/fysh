#include "AST.h"
#include <cassert>
#include <ostream>

constexpr const char *str(const fysh::ast::FyshBinary &op) {
  using fysh::ast::FyshBinary;
  switch (op) {
    // clang-format off
  case FyshBinary::Add:        return "+";
  case FyshBinary::Sub:        return "-";
  case FyshBinary::Mul:        return "*";
  case FyshBinary::Div:        return "/";
  case FyshBinary::Equal:      return "==";
  case FyshBinary::NotEqual:   return "!=";
  case FyshBinary::GT:         return ">";
  case FyshBinary::LT:         return "<";
  case FyshBinary::GTE:        return ">=";
  case FyshBinary::LTE:        return "<=";
  case FyshBinary::BitwiseAnd: return "&";
  case FyshBinary::BitwiseOr:  return "|";
  case FyshBinary::BitwiseXor: return "^";
  case FyshBinary::ShiftLeft:  return "<<";
  case FyshBinary::ShiftRight: return ">>";
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

template <class> inline constexpr bool always_false_v = false;

std::ostream &fysh::ast::operator<<(std::ostream &os,
                                    const fysh::ast::FyshExpr &f) {
  std::visit(
      [&](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Error>)
          os << "ERROR(\"" << *arg.t << "\"";
        else if constexpr (std::is_same_v<T, Box<FyshBinaryExpr>>)
          os << "(" << arg.t->left << " " << str(arg.t->op) << " "
             << arg.t->right << ")";
        else if constexpr (std::is_same_v<T, Box<FyshUnaryExpr>>)
          os << "(" << str(arg.t->op) << " " << arg.t->expr << ")";
        else if constexpr (std::is_same_v<T, FyshIdentifier>)
          os << "(" << arg.name << ")";
        else if constexpr (std::is_same_v<T, FyshLiteral>)
          os << "(" << arg.num << ")";
        else
          static_assert(always_false_v<T>, "non-exhaustive visitor!");
      },
      f);
  return os;
}
