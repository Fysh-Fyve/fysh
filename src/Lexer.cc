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
 * \file Lexer.cc
 */

#include "Lexer.h"
#include <cctype>
#include <string_view>
#include <variant>

#ifdef FYSH_DEBUG
#include <iostream>

void fysh::FyshLexer::printRest() { std::cerr << rest() << std::endl; }

char fysh::FyshLexer::periscope(int line) const noexcept {
  if (line > 0) {
    std::cerr << "Current (line:" << line << "): " << *current << std::endl;
  }
  return *current;
}
#define periscope() periscope(__LINE__)
#endif

// -------------- Utility functions --------------
static bool isSpace(char c) noexcept {
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static bool isScale(char c) noexcept {
  return c == '(' || c == ')' || c == '{' || c == '}';
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

// dude this is just the species, there is no start/end so it will pass the
// testcase but wont contain the token
//
// Talk to me! - Charles
fysh::Fysh fysh::FyshLexer::goFysh(Species s) noexcept {
  reel();
  return s;
}

fysh::FyshChar fysh::FyshLexer::eatFyshChar() noexcept {
  FyshChar cur{peekFyshChar()};
  if (std::holds_alternative<const char *>(cur)) {
    auto curFysh{std::get<const char *>(cur)};
    current = curFysh + 1;
    return cur;
  } else {
    auto curFysh{std::get<std::string_view>(cur)};
    current = curFysh.end();
    return cur;
  }
}

fysh::FyshChar fysh::FyshLexer::peekFyshChar() noexcept {
  size_t offset = 0;
  // Skip continuation bytes;
  while ((current[offset] & 0xC0) == 0x80) {
    offset++;
  }
  const char *start{current + offset};
  size_t bytesToRead = 1;
  if ((*start & 0xE0) == 0xC0) {
    bytesToRead = 2;
  } else if ((*start & 0xF0) == 0xE0) {
    bytesToRead = 3;
  } else if ((*start & 0xF8) == 0xF0) {
    bytesToRead = 4;
  } else {
    // Single-byte char
    return FyshChar{start};
  }
  return FyshChar{std::string_view{start, bytesToRead}};
}

// -------------- Token functions --------------
fysh::Fysh fysh::FyshLexer::cullDeformedFysh() noexcept {
  while (!isSpace(periscope()) && periscope() != '\0') {
    reel();
  }

  const char *fyshEnd{current};
  return {Species::INVALID, fyshStart, fyshEnd};
}

// <3 or ♡
fysh::Fysh fysh::FyshLexer::heart() noexcept {
  return goFysh(Species::HEART_MULTIPLY);
}

// </3 or 💔
fysh::Fysh fysh::FyshLexer::heartBreak() noexcept {
  reel();
  if (periscope() == '3') {
    return goFysh(Species::HEART_DIVIDE);
  }
  return cullDeformedFysh();
}

// opening for error handling ><!@#$>
fysh::Fysh fysh::FyshLexer::openWTF() noexcept {
  reel();
  if (reel() == '@' && reel() == '#' && reel() == '$' && periscope() == '>') {
    return goFysh(Species::WTF_OPEN);
  }
  return cullDeformedFysh();
}

// closing for error handling <!@#$><
fysh::Fysh fysh::FyshLexer::closeWTF() noexcept {
  reel();
  if (reel() == '@' && reel() == '#' && reel() == '$' && reel() == '>' &&
      periscope() == '<') {
    return goFysh(Species::WTF_CLOSE);
  }
  return cullDeformedFysh();
}

// ><>
fysh::Fysh fysh::FyshLexer::fyshOpen() noexcept {
  return goFysh(Species::FYSH_OPEN);
}

// <><
fysh::Fysh fysh::FyshLexer::fyshClose() noexcept {
  reel();
  if (periscope() == '<') {
    return goFysh(Species::FYSH_CLOSE);
  }
  return cullDeformedFysh();
}

fysh::Fysh fysh::FyshLexer::slashOrComment() noexcept {
  // TODO: Implement
  return goFysh(Species::INVALID);
}

fysh::Fysh fysh::FyshLexer::identifier(FyshDirection dir,
                                       bool increment) noexcept {
  if (increment) {
    reel();
  }
  const char *identStart{current};
  reel();
  while (std::isalnum(periscope())) {
    reel();
  }
  if (periscope() != '>') {
    return cullDeformedFysh();
  }
  const char *identEnd{current};
  reel();
  if (dir == FyshDirection::LEFT) {
    if (periscope() != '<') {
      return cullDeformedFysh();
    } else {
      reel();
      if (periscope() == '<') {
        reel();
        return {Species::DECREMENT, identStart, identEnd};
      }
    }
  }
  if (increment) {
    return {Species::INCREMENT, identStart, identEnd};
  }

  Fysh fysh{Species::FYSH_IDENTIFIER, identStart, identEnd};
  fysh.negate = dir == FyshDirection::LEFT;
  return fysh;
}

fysh::Fysh fysh::FyshLexer::random() noexcept {
  reel();
  for (size_t i = 1; i < 3; i++) {
    if (periscope() != '#') {
      return cullDeformedFysh();
    }
    reel();
  }
  if (periscope() == '>') {
    return goFysh(Species::RANDOM);
  }
  return cullDeformedFysh();
}

fysh::Fysh fysh::FyshLexer::scales(fysh::FyshDirection dir) noexcept {
  // gets all the scales and converts them to a binary number
  char c = reel();
  std::uint32_t value{c == '{' ||
                      c == '}'}; // stores the first scale as a binary number
  int scaleCount = 1;
  while (isScale(periscope())) {
    c = reel();
    value = (value << 1) |
            (c == '{' || c == '}'); // shifts the bits to the left and stores
                                    // the next scale using bitwise OR
    scaleCount++;
  }
  // Special loopy fysh
  if (scaleCount == 3 && value == 0 && dir == FyshDirection::RIGHT) {
    switch (periscope()) {
    case '@':
      reel();
      if (periscope() == '>') {
        return goFysh(Species::FYSH_LOOP);
      } else {
        return cullDeformedFysh();
      }
    case '^':
      reel();
      if (periscope() == '>') {
        return goFysh(Species::IF);
      } else {
        return cullDeformedFysh();
      }
    case '*':
      reel();
      if (periscope() == '>') {
        return goFysh(Species::ELSE);
      } else {
        return cullDeformedFysh();
      }
    }
  }

  c = reel(); // stores the value after the last scale

  // check if the current character is an eye or >
  if (!(isFyshEye(c) && periscope() == '>') && c != '>') {
    return cullDeformedFysh();
  }

  // check if its the end of the token or not (2nd character after the scales)
  if (!isSpace(periscope())) {
    c = periscope();
    if ((dir == FyshDirection::RIGHT &&
         c != '>') || // checks for '°>' (fysh head)
        (dir == FyshDirection::LEFT &&
         c != '<')) { // checks for '><' (fysh tail)
      return cullDeformedFysh();
    }
    reel();
  }

  // make sure the token ends
  if (!isSpace(periscope()) && periscope() != '\0') {
    return cullDeformedFysh();
  }

  fysh::Fysh ret{value};
  ret.negate = dir == FyshDirection::LEFT;
  return ret;
}

// --------------------------Check for the token--------------------------------

// Token starts with '<' or '>'
fysh::Fysh fysh::FyshLexer::fyshOutline() noexcept {
  switch (periscope()) {
  case ('<'):
    reel();
    switch (periscope()) {
    case ('3'):
      return heart(); // <3 multiplication heart
    case ('/'):
      return heartBreak(); // </3 division heart
    case ('<'):
      return goFysh(Species::SHIFT_LEFT);
    default:
      return swimLeft(); // a fysh swimming left
    }
  case '>':
    reel();
    switch (periscope()) {
    case ('<'):
      return swimRight(); // a fysh swimming right
    case ('>'):
      reel();
      if (periscope() == '<') {
        return identifier(FyshDirection::RIGHT, true);
      } else {
        return Species::SHIFT_RIGHT;
      }
    default:
      return cullDeformedFysh();
    }
  default:
    return cullDeformedFysh();
  }
}

fysh::Fysh fysh::FyshLexer::swimLeft() noexcept {
  // current is the 2nd character of the token
  switch (periscope()) {
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
  default:
    if (std::isalpha(periscope())) {
      return identifier(FyshDirection::LEFT);
    } else {
      return cullDeformedFysh();
    }
  }
}

// all fysh that start with >< are swimming right e.g. ><>
fysh::Fysh fysh::FyshLexer::swimRight() noexcept {
  reel(); // 2nd swim right character '<'
  switch (periscope()) {
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
  default:
    if (std::isalpha(periscope()) && periscope() != 'o') {
      return identifier(FyshDirection::RIGHT);
    } else {
      return cullDeformedFysh();
    }
  }
}

// Where the magic happens
fysh::Fysh fysh::FyshLexer::nextFysh() noexcept {
  while (isSpace(periscope())) {
    reel();
  }

  fyshStart = current;
  switch (periscope()) {
  case '\0':
    return Species::END;
  case '<':
  case '>':
    return fyshOutline();
  case '&':
    return goFysh(Species::BITWISE_AND);
  case '|':
    return goFysh(Species::BITWISE_OR);
    // I think this has to change if not is also going to be ^
  case '^':
    return goFysh(Species::CARET);
  case '~':
    reel();
    if (periscope() == '=') {
      return goFysh(Species::NOT_EQUAL);
    } else if (peekFyshChar() == "≈") {
      eatFyshChar();
      return Species::NOT_EQUAL;
    } else if (periscope() == 'o') {
      reel();
      if (periscope() == '=') {
        return goFysh(Species::TADPOLE_LTE);
      } else if (peekFyshChar() == "≈") {
        eatFyshChar();
        return Species::TADPOLE_LTE;
      } else {
        // We already reeled in o, do not go fysh.
        return Species::TADPOLE_LT;
      }
    } else {
      // We already reeled in ~, do not go fysh.
      return Species::TERMINATE;
    }
  case '[':
    return goFysh(Species::FYSH_TANK_OPEN);
  case ']':
    return goFysh(Species::FYSH_TANK_CLOSE);
  case '=':
    reel();
    if (periscope() == '=') {
      return goFysh(Species::EQUAL);
    } else {
      // We already reeled in =, do not go fysh.
      return Species::ASSIGN;
    }
  case 'o':
    reel();
    if (periscope() == '~') {
      reel();
      if (periscope() == '=') {
        return goFysh(Species::TADPOLE_GTE);
      } else if (peekFyshChar() == "≈") {
        eatFyshChar();
        return Species::TADPOLE_GTE;
      } else {
        // We already reeled in ~, do not go fysh.
        return Species::TADPOLE_GT;
      }
    } else {
      return cullDeformedFysh();
    }
  default:
    if (peekFyshChar() == "♡") {
      eatFyshChar();
      return Species::HEART_MULTIPLY;
    } else if (peekFyshChar() == "💔") {
      eatFyshChar();
      return Species::HEART_DIVIDE;
    } else if (peekFyshChar() == "≈") {
      eatFyshChar();
      if (peekFyshChar() == "≈") {
        eatFyshChar();
        return Species::EQUAL;
      } else {
        return Species::ASSIGN;
      }
    } else {
      return cullDeformedFysh();
    }
  }
}
