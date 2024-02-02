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
Fysh FyshLexer::nextFysh() { return Fysh{Species::EQUAL}; }
