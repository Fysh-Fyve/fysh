#include "Lexer.h"

bool is_space(char c) noexcept {
  switch (c) {
  case ' ':
  case '\t':
  case '\r':
  case '\n':
    return true;
  default:
    return false;
  }
}

// TODO: Implement!
Token FyshLexer::nextToken() { return Token{TokenType::EQUAL}; }
