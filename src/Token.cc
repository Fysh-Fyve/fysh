#include "Token.h"

TokenType Token::get_type() { return tokenType; }

bool Token::is_type(TokenType in_type) const noexcept {
  return tokenType == in_type;
}

bool Token::is_one_of(TokenType in_type1, TokenType in_type2) const noexcept {
  return is_type(in_type1) || is_type(in_type2);
}

std::string_view Token::get_value() const noexcept { return value; }

void Token::set_value(std::string_view in_value) noexcept {
  value = std::move(in_value);
}
