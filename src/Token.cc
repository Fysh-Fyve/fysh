#include "Token.h"
#include <cassert>

TokenType Token::type() const noexcept { return tokenType; }

bool Token::isOneOf(TokenType type1, TokenType type2) const noexcept {
  return tokenType == type1 || tokenType == type2;
}

std::string_view Token::val() const noexcept { return value; }

constexpr const char *debugType(const TokenType &type) {
  switch (type) {
  case TokenType::FYSH_LITERAL:
    return "LITERAL";
  case TokenType::FYSH_IDENTIFIER:
    return "IDENT";
  case TokenType::HEART_MULTIPLY:
    return "*";
  case TokenType::DIVIDE:
    return "/";
  case TokenType::TADPOLE_LT:
    return "<";
  case TokenType::TADPOLE_GT:
    return ">";
  case TokenType::TADPOLE_LTE:
    return "<=";
  case TokenType::TADPOLE_GTE:
    return ">=";
  case TokenType::EQUAL:
    return "==";
  case TokenType::NOT_EQUAL:
    return "!=";
  case TokenType::INCREMENT:
    return "++";
  case TokenType::DECREMENT:
    return "--";
  case TokenType::FYSH_TANK_OPEN:
    return "[";
  case TokenType::FYSH_TANK_CLOSE:
    return "]";
  case TokenType::FYSH_OPEN:
    return "{";
  case TokenType::FYSH_CLOSE:
    return "}";
  case TokenType::WTF_OPEN:
    return "WTF(";
  case TokenType::WTF_CLOSE:
    return ")WTF";
  case TokenType::COMMENT:
    return "//";
  case TokenType::OPENING_COMMENT:
    return "/*";
  case TokenType::CLOSING_COMMENT:
    return "*/";
  }

  assert(false);
}

std::ostream &operator<<(std::ostream &os, const Token &value) {
  os << "'" << debugType(value.type()) << "'" << value.val();
  return os;
}
