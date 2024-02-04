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

Fysh FyshLexer::nextFysh() noexcept {
  while (isSpace(peek()))
    get();
  switch (peek()) {
  case '\0':
    return Fysh(Species::END);
  case '<':
  case '>':
    return fyshOutline();
  }
  std::cout << peek() << std::endl;
  return Fysh(Species::END);
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

Fysh FyshLexer::scales() noexcept {
  const char *start = current;
  get();
  while (isScale(peek()))
    get();
  return Fysh(Species::FYSH_SCALES, start, current);
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

// TODO: Implement!
// Fysh FyshLexer::nextFysh() { return Fysh{Species::EQUAL}; }
