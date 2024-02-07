/**
 * Copyright (C) 2024 Yahya Al-Shamali
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
 * \file Lexer.cc
 */

#include "Lexer.h"

#ifdef FYSH_DEBUG
#include <iostream>

void fysh::FyshLexer::printRest() { std::cerr << rest() << std::endl; }
char fysh::FyshLexer::peek(int line) const noexcept {
  if (line > 0) {
    std::cerr << "Current (line:" << line << "): " << *current << std::endl;
  }
  return *current;
}
#define peek() peek(__LINE__)
#endif

// -------------- Utility functions --------------
static bool isSpace(char c) noexcept {
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static bool isScale(char c) noexcept {
  return c == '(' || c == ')' || c == '{' || c == '}';
}

void fysh::FyshLexer::skipWhitespace() noexcept {
  while (isSpace(peek())) {
    get();
  }
}

void fysh::FyshLexer::gotoEndOfToken() noexcept {
  while (!isSpace(peek())) {
    get();
  }
}

// o or ° (eye of the fysh)
bool fysh::FyshLexer::isFyshEye(char c) noexcept {
  switch (c) {
  case 'o':
    // case '°': UNICODE
    return true;
  default:
    return false;
  }
}

fysh::Fysh fysh::FyshLexer::tryUnicode(const char *bytes, Species s) noexcept {
  bool touched{false};
  for (size_t i = 0; (unsigned char)bytes[i] != 0x00; i++) {
    if ((unsigned char)peek() == (unsigned char)bytes[i]) {
      get();
      touched = true;
    } else {
      if (touched) {
        return cullDeformedFysh();
      } else {
        // Contiue looping through the characters
        return fysh::Fysh{Species::CONTINUE};
      }
    }
  }
  return fysh::Fysh{s};
}

// -------------- Token functions --------------

struct Unicode {
  const char *codePoint;
  fysh::Species species;
};

/**
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
fysh::Fysh fysh::FyshLexer::unicode() noexcept {
  static const struct Unicode chars[] = {
      {"💔", Species::HEART_DIVIDE},
      {"♡", Species::HEART_MULTIPLY},
  };
  for (const struct Unicode &c : chars) {
    fysh::Fysh fysh{tryUnicode(c.codePoint, c.species)};
    // We either get an invalid token or a non-continue token
    if (fysh == Species::INVALID || !(fysh == Species::CONTINUE)) {
      return fysh;
    }
  }

  return cullDeformedFysh();
}

fysh::Fysh fysh::FyshLexer::cullDeformedFysh() noexcept {
  gotoEndOfToken();
  const char *fyshEnd{current};
  return fysh::Fysh{Species::INVALID, fyshStart, fyshEnd};
}

// <3 or ♡
fysh::Fysh fysh::FyshLexer::heart() noexcept {
  ;
  get();
  return fysh::Fysh{Species::HEART_MULTIPLY};
}

// </3 or 💔
fysh::Fysh fysh::FyshLexer::heartBreak() noexcept {
  get();
  if (peek() == '3') {
    get();
    return fysh::Fysh{Species::HEART_DIVIDE};
  }
  return cullDeformedFysh();
}

// opening for error handling ><!@#$>
fysh::Fysh fysh::FyshLexer::openWTF() noexcept {
  if (get() == '!' && get() == '@' && get() == '#' && get() == '$' &&
      peek() == '>') {
    get();
    return fysh::Fysh{Species::WTF_OPEN};
  }
  return cullDeformedFysh();
}

// closing for error handling <!@#$><
fysh::Fysh fysh::FyshLexer::closeWTF() noexcept {
  if (get() == '!' && get() == '@' && get() == '#' && get() == '$' &&
      get() == '>' && peek() == '<') {
    get();
    return fysh::Fysh{Species::WTF_CLOSE};
  }
  return cullDeformedFysh();
}

// ><>
fysh::Fysh fysh::FyshLexer::fyshOpen() noexcept {
  get();
  return fysh::Fysh{Species::FYSH_OPEN};
}

// <><
fysh::Fysh fysh::FyshLexer::fyshClose() noexcept {
  get();
  if (peek() == '<') {
    get();
    return fysh::Fysh{Species::FYSH_CLOSE};
  }
  return cullDeformedFysh();
}

fysh::Fysh fysh::FyshLexer::slashOrComment() noexcept {
  return fysh::Fysh{Species::INVALID};
}

fysh::Fysh fysh::FyshLexer::identifier() noexcept {
  return fysh::Fysh{Species::INVALID};
}

fysh::Fysh fysh::FyshLexer::random() noexcept {
  for (size_t i = 0; i < 3; i++) {
    if (peek() != '#') {
      return cullDeformedFysh();
    }
    get();
  }
  if (peek() == '>') {
    get();
    return fysh::Fysh{Species::RANDOM};
  }
  return cullDeformedFysh();
}

fysh::Fysh fysh::FyshLexer::scales(fysh::FyshDirection dir) noexcept {
  // gets all the scales and converts them to a binary number
  char c = get();
  uint32_t value{c == '{' ||
                 c == '}'}; // stores the first scale as a binary number
  while (isScale(peek())) {
    c = get();
    value = (value << 1) |
            (c == '{' || c == '}'); // shifts the bits to the left and stores
                                    // the next scale using bitwise OR
  }

  c = get(); // stores the value after the last scale

  // check if the current character is an eye or >
  if (!(isFyshEye(c) && peek() == '>') && c != '>') {
    return cullDeformedFysh();
  }

  // check if its the end of the token or not (2nd character after the scales)
  if (!isSpace(peek())) {
    c = peek();
    if ((dir == FyshDirection::RIGHT &&
         c != '>') || // checks for '°>' (fysh head)
        (dir == FyshDirection::LEFT &&
         c != '<')) { // checks for '><' (fysh tail)
      return cullDeformedFysh();
    }
    get();
  }

  // make sure the token ends
  if (!isSpace(peek()) && peek() != '\0') {
    return cullDeformedFysh();
  }

  fysh::Fysh ret{value};
  ret.negate = dir == FyshDirection::LEFT;
  return ret;
}

// --------------------------Check for the token--------------------------------

// Token starts with '<' or '>'
fysh::Fysh fysh::FyshLexer::fyshOutline() noexcept {
  switch (peek()) {
  case ('<'):
    get();
    switch (peek()) {
    case ('3'):
      return heart(); // <3 multiplication heart
    case ('/'):
      return heartBreak(); // </3 division heart
    default:
      return swimLeft(); // a fysh swimming left
    }
  case '>':
    get();
    switch (peek()) {
    case ('<'):
      return swimRight(); // a fysh swimming right
    default:
      return cullDeformedFysh();
    }
  default:
    return cullDeformedFysh();
  }
}

fysh::Fysh fysh::FyshLexer::swimLeft() noexcept {
  // current is the 2nd character of the token
  switch (peek()) {
  case ('{'):
  case ('('):
  case ('}'):
  case (')'):
  case ('o'):
    return scales(FyshDirection::LEFT); // negative fysh literal <°)})}><
  case ('>'):
    return fyshClose(); // close curly bracket
  case ('!'):
    return closeWTF(); // error handling close tag
  }
  return cullDeformedFysh();
}

// all fysh that start with >< are swimming right e.g. ><>
fysh::Fysh fysh::FyshLexer::swimRight() noexcept {
  get(); // 2nd swim right character '<'
  switch (peek()) {
  case ('{'):
  case ('('):
  case ('}'):
  case (')'):
    return scales(FyshDirection::RIGHT); // fysh literal ><{{({(°>
  case ('>'):
    return fyshOpen(); // open curly bracket
  case ('!'):
    return openWTF(); // error handling
  case ('/'):
    return slashOrComment(); // comment
  case ('#'):
    return random(); // random number
  }
  return cullDeformedFysh();
}

// Where the magic happens
fysh::Fysh fysh::FyshLexer::nextFysh() noexcept {
  skipWhitespace();
  fyshStart = current;
  switch (peek()) {
  case '\0':
    return fysh::Fysh{Species::END};
  case '<':
  case '>':
    return fyshOutline();
  default:
    return unicode();
  }
}
