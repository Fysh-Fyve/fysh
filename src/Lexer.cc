#include "Lexer.h"
#include <iostream>

bool isSpace(char c) noexcept {
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

bool isScale(char c) noexcept {
  switch (c) {
  case '(':
  case ')':
  case '{':
  case '}':
    return true;
  default:
    return false;
  }
}

/*

bool isFyshEye(char c) noexcept {
  switch (c) {
    case 'o':
    case '°':
      return true;
    default:
      return false;
  }
}


bool isNegativeScale(char c) noexcept {
  switch (c) {
    case ')':
    case '}':
      return true;
    default:
      return false;
  }
}*/

bool isPositiveScale(char c) noexcept {
  switch (c) {
  case '(':
  case '{':
    return true;
  default:
    return false;
  }
}

Fysh FyshLexer::tryUnicode(const char *bytes, Species s) noexcept {
  bool touched{false};
  for (size_t i = 0; (unsigned char)bytes[i] != 0x00; i++) {
    if ((unsigned char)peek() == (unsigned char)bytes[i]) {
      get();
      touched = true;
    } else {
      if (touched) {
        return Fysh{Species::INVALID};
      } else {
        // Contiue looping through the characters
        return Fysh{Species::CONTINUE};
      }
    }
  }
  return Fysh{s};
}

struct Unicode {
  const char *codePoint;
  Species species;
};

/**!
 * Try to match the token to Unicode characters.
 *
 * This assumes that none of these characters start with the same byte, or
 * else trying to check the next character will not work anymore because it
 * will already be marked as invalid.
 * Example:
 * ♡  - U+2661 - 0xE2 0x99 0xA1
 * ♥  - U+2665 - 0xE2 0x99 0xA5
 * These two start with the same bytes 0xE2 and 0x99.
 * if we add ♥ to the list of valid tokens, it will never be checked because
 * the lexer will match the first two bytes of ♡, see that 0xA5 != 0xA1,
 * and return an invalid token (instead of continuing to check).
 * Maybe we can implement this with a Trie, but it doesn't seem worth it
 * for only two tokens.
 */
Fysh FyshLexer::unicode() noexcept {
  static const struct Unicode chars[] = {
      {"💔", Species::DIVIDE},
      {"♡", Species::HEART_MULTIPLY},
  };
  for (const struct Unicode &c : chars) {
    Fysh fysh{tryUnicode(c.codePoint, c.species)};
    // We either get an invalid token or a non-continue token
    if (fysh == Species::INVALID || !(fysh == Species::CONTINUE)) {
      return fysh;
    }
  }
  std::cout << peek() << '(' << +peek() << ')' << std::endl;
  return Fysh(Species::INVALID);
}

Fysh FyshLexer::nextFysh() noexcept {
  while (isSpace(peek()))
    get();
  switch (peek()) {
  case '\0':
    return Fysh(Species::END);
  case '<':
  case '>':
    return fyshOutline();
  default:
    return unicode();
  }
}

Fysh FyshLexer::fyshOutline() noexcept {
  const char *start = current;
  get();

  // get multiply token
  if (*start == '<' && peek() == '3') {
    get();
    return Fysh(Species::HEART_MULTIPLY, start, current);
  }

  // get divide token
  /*else if (*start == '<' && peek() == '/') {
    get();
    if (peek() == '3') {
      get();
      return Fysh(Species::DIVIDE, start, current);
    }
  }*/

  // swim right
  else if (*start == '>' && peek() == '<') {
    get();
    if (isPositiveScale(peek())) {
      return scales();
    }
    /*else if (peek() == '!') {
      return openWTF();
    } else if (peek() == '/') {
      return slashOrComment();
    } else if (peek() == '>') {
      return Fysh(Species::FYSH_OPEN, start, current);
    } else {
      return identifier();
    } */
  }

  /*
  // get negative scale fysh
  else if (start* == '<' && isFyshEye(peek())) {
    get();
    // get identifier token
    if (isNegativeScale(peek())){
      return negativeFysh();
    }
  }
  // get positive scale fysh
  else if (start* == '>' && peek() == '<') {
    get();
    if (isPositiveScale(peek())){
      return positiveFysh();
    }
  } */
  return Fysh(Species::END);
}

// TODO: Handle negative case
Fysh FyshLexer::scales() noexcept {
  auto c{get()};
  uint32_t value{c == '{' || c == '}'};
  while (isScale(peek())) {
    auto c{get()};
    value = (value << 1) | (c == '{' || c == '}');
  }
  // Parse the head of the positive fysh
  if (get() != 'o' || get() != '>') {
    return Fysh{Species::INVALID};
  }
  return Fysh{value};
}

/*Fysh FyshLexer::scales() noexcept {
  const char *start = current;
  get();
  while (isScale(peek())) get();
  if (peek() == 'o'){
    get();
    if (peek() == '>'){
      // positive
    } else {
      // error
    }
  }
  else if (peek() == '>'){
    // negative
  }
  else {
    // error
  }
  return Fysh(Species::FYSH_SCALES, start, current);
}*/
/*
Token Lexer::number() noexcept {
  const char* start = m_beg;
  get();
  while (is_digit(peek())) get();
  return Token(Token::Kind::Number, start, m_beg);
}*/
