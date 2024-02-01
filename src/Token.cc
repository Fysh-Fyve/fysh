#include "Token.h"

TokenType Token::type() const noexcept { return tokenType; }

bool Token::isType(TokenType in_type) const noexcept {
  return tokenType == in_type;
}

bool Token::isOneOf(TokenType type1, TokenType type2) const noexcept {
  return isType(type1) || isType(type2);
}

std::string_view Token::val() const noexcept { return value; }
