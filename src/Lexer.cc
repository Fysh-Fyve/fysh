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
#include "Species.h"
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
static bool isScale(char c) noexcept {
  return c == '(' || c == ')' || c == '{' || c == '}';
}

// Checks if the current character is a Unicode character
bool fysh::FyshLexer::isUnicode() noexcept {
        unsigned char c = static_cast<unsigned char>(*current);

        // If the first byte is 0xxxxxxx, it's ASCII, not Unicode.
        if ((c & 0x80) == 0x00) {
            return false; 
        }
        // If the first byte starts with 110xxxxx, 1110xxxx, or 11110xxx, it's a Unicode character.
        else if ((c & 0xE0) == 0xC0 || // 110xxxxx, two-byte sequence
                 (c & 0xF0) == 0xE0 || // 1110xxxx, three-byte sequence
                 (c & 0xF8) == 0xF0) { // 11110xxx, four-byte sequence
            return true; 
        }
        return false; // Not a start of Unicode sequence (likely a continuation byte or invalid UTF-8)
    
}

char fysh::FyshLexer::reel() noexcept {
  char c = *current;
  if (c == '\n') {
    line++;
  }
  current++;
  return c;
};

// Consume a character and return its species
fysh::Fysh fysh::FyshLexer::goFysh(Species s) noexcept {
  reel();
  return s;
}

// Decodes and consumes a character, handling both single-byte and multi-byte characters
fysh::FyshChar fysh::FyshLexer::eatFyshChar() noexcept {
  return std::visit(
      [&](auto &&arg) -> FyshChar {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, const char *>) {
          if (*arg != '\0') {
            current = arg + 1;
          }
        } else if constexpr (std::is_same_v<T, std::string_view>) {
          current = arg.end();
        }
        return {arg};
      },
      peekFyshChar());
}

// Peeks at the next character without consuming it, supporting multi-byte characters
fysh::FyshChar fysh::FyshLexer::peekFyshChar() noexcept {
  size_t offset = 0;
  // Skip continuation bytes;
  while ((current[offset] & 0xC0) == 0x80) {
    offset++;
  }
  const char *start{current + offset};
  size_t bytesToRead = 1;
  // Determine the number of bytes to read based on the first byte
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
  while (!std::isspace(periscope()) && periscope() != '\0') {
    reel();
  }
  const char *fyshEnd{current};
  return {Species::INVALID, fyshStart, fyshEnd};
}

// opening for error handling ><!@#$>
fysh::Fysh fysh::FyshLexer::openWTF() noexcept {
  reel();
  if (match("@#$>")) {
    return Species::WTF_OPEN;
  }
  return cullDeformedFysh();
}

// closing for error handling <!@#$><
fysh::Fysh fysh::FyshLexer::closeWTF() noexcept {
  reel();
  if (match("@#$><")) {
    return Species::WTF_CLOSE;
  }
  return cullDeformedFysh();
}

// <><
fysh::Fysh fysh::FyshLexer::fyshClose() noexcept {
  reel();
  if (match('<')) {
    return Species::FYSH_CLOSE;
  }
  return cullDeformedFysh();
}

bool fysh::FyshLexer::match(const char *c) noexcept {
  for (; *c != '\0'; c++) {
    if (!match(*c)) {
      return false;
    }
  }
  return true;
}

bool fysh::FyshLexer::match(char c) noexcept {
  if (periscope() == c) {
    reel();
    return true;
  } else {
    return false;
  }
}

static std::string_view trim(std::string_view in) {
  auto left = in.begin();
  for (;; ++left) {
    if (left == in.end())
      return std::string_view();
    if (!std::isspace(*left))
      break;
  }
  auto right = in.end() - 1;
  for (; right > left && isspace(*right); --right)
    ;
  return std::string_view(left, std::distance(left, right) + 1);
}

fysh::Fysh fysh::FyshLexer::slashOrComment() noexcept {
  reel();
  switch (periscope()) {
    // single-line
  case '/': {
    reel();
    if (!match('>')) {
      return cullDeformedFysh();
    }
    while (periscope() == ' ' || periscope() == '\t') {
      reel();
    }
    const char *commentStart{current};
    while (periscope() != '\n' && periscope() != '\r') {
      reel();
    }
    const char *commentEnd{current};
    // Remove any extra newlines
    while (periscope() == '\n' || periscope() == '\r') {
      reel();
    }

    return {Species::COMMENT, commentStart, commentEnd};
  }
    // multi-line
  case '*': {
    reel();
    if (!match('>')) {
      return cullDeformedFysh();
    }
    const char *commentStart{current};
    while (true) {
      while (periscope() != '<' && periscope() != '\0') {
        reel();
      }
      // We reached the end... yikes
      if (periscope() == '\0') {
        return Species::INVALID;
      }
      const char *commentEnd{current};
      reel();
      if (match("*/><")) {
        auto comment{std::string_view(commentStart,
                                      std::distance(commentStart, commentEnd))};
        auto trimmed{trim(comment)};
        return {Species::MULTILINE_COMMENT, trimmed.data(), trimmed.length()};
      }
    }
  }
  default:
    return cullDeformedFysh();
  }
}

fysh::Fysh fysh::FyshLexer::identifier(FyshDirection dir,
                                       bool increment) noexcept {
  if (increment) {
    reel();
  }
  const char *identStart{current};
  if (isUnicode()) {
    eatFyshChar();
  } else {
    reel();
  }
  while (std::isalnum(periscope()) || isUnicode()) {
    if (isUnicode()) {
      eatFyshChar();
    } else {
      reel();
    }
  }
  if (periscope() != '>') {
    return cullDeformedFysh();
  }
  const char *identEnd{current};
  reel();
  if (dir == FyshDirection::LEFT) {
    if (!match('<')) {
      return cullDeformedFysh();
    }
    if (match('<')) {
      return {Species::DECREMENT, identStart, identEnd};
    }
  }

  if (increment) {
    return {Species::INCREMENT, identStart, identEnd};
  }

  return {Species::FYSH_IDENTIFIER, identStart, identEnd,
          dir == FyshDirection::LEFT};
}

fysh::Fysh fysh::FyshLexer::random() noexcept {
  reel();
  for (size_t i = 1; i < 3; i++) {
    if (!match('#')) {
      return cullDeformedFysh();
    }
  }
  if (match('>')) {
    return Species::RANDOM;
  }
  return cullDeformedFysh();
}

fysh::Fysh fysh::FyshLexer::scales(fysh::FyshDirection dir) noexcept {
  // gets all the scales and converts them to a binary number
  char c = reel();
  // stores the first scale as a binary number
  std::uint32_t value{c == '{' || c == '}'};
  int scaleCount = 1;
  while (isScale(periscope())) {
    c = reel();
    // shifts the bits to the left and stores the next scale using bitwise OR
    value = (value << 1) | (c == '{' || c == '}');
    scaleCount++;
  }
  // Special control sequence fysh
  if (scaleCount == 3 && value == 0 && dir == FyshDirection::RIGHT) {
    switch (periscope()) {
      // loopy
    case '@':
      reel();
      if (match('>')) {
        return Species::FYSH_LOOP;
      }
      return cullDeformedFysh();
      // happy
    case '^':
      reel();
      if (match('>')) {
        return Species::IF;
      }
      return cullDeformedFysh();
      // dead
    case '*':
      reel();
      if (match('>')) {
        return Species::ELSE;
      }
      return cullDeformedFysh();
    }
  }

  if (dir == FyshDirection::LEFT) {
    // Left fysh
    if (!match("><")) {
      return cullDeformedFysh();
    }
  } else {
    // Right Fysh

    // Eat any fysh eyes
    if (peekFyshChar() == "°") {
      eatFyshChar();
    }
    match('o');

    if (!match('>')) {
      return cullDeformedFysh();
    }
  }



  return {value, dir == FyshDirection::LEFT};
}

// --------------------------Check for the token--------------------------------

// Token starts with '<' or '>'
fysh::Fysh fysh::FyshLexer::fyshOutline() noexcept {
  switch (periscope()) {
  case ('<'):
    reel();
    switch (periscope()) {
    case ('3'):
      return goFysh(Species::HEART_MULTIPLY); // <3 multiplication heart
    case ('/'):
      reel();
      if (match('3')) {
        return Species::HEART_DIVIDE;
      }
      return cullDeformedFysh();
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
      }

      return Species::SHIFT_RIGHT;
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
    return scales(FyshDirection::LEFT); // eyeless negative fysh literal <)})}><
  case ('>'):
    return fyshClose(); // close curly bracket
  case ('!'):
    return closeWTF(); // error handling close tag
  case ('o'):
    reel();
    switch (periscope()) {
    case ('{'):
    case ('('):
    case ('}'):
    case (')'):
      // negative fysh literal with eye <o)})}><
      return scales(FyshDirection::LEFT);
    default:
      // negative fysh identifier starting with 'o' <open><
      current--;
      return identifier(FyshDirection::LEFT);
    }
    return scales(FyshDirection::LEFT);
  default:
    if (peekFyshChar() == "°") {
      eatFyshChar();
      return scales(FyshDirection::LEFT);
    }
    if (std::isalpha(periscope()) || isUnicode()) {
      return identifier(FyshDirection::LEFT);
    }
    return cullDeformedFysh();
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
    return goFysh(Species::FYSH_OPEN);
  case ('!'):
    return openWTF(); // error handling
  case ('/'):
    return slashOrComment(); // comment
  case ('#'):
    return random(); // random number
  default:
    if (std::isalpha(periscope()) || isUnicode()) {
      return identifier(FyshDirection::RIGHT);
    }
    return cullDeformedFysh();
  }
}

fysh::Fysh fysh::FyshLexer::tilde() noexcept {
  reel();
  if (match('=')) {
    return Species::NOT_EQUAL;
  }
  if (peekFyshChar() == "≈") {
    eatFyshChar();
    return Species::NOT_EQUAL;
  }
  if (match('o')) {
    if (match('=')) {
      return Species::TADPOLE_LTE;
    }
    if (peekFyshChar() == "≈") {
      eatFyshChar();
      return Species::TADPOLE_LTE;
    }
    // We already reeled in o, do not go fysh.
    return Species::TADPOLE_LT;
  }
  // We already reeled in ~, do not go fysh.
  return Species::FYSH_WATER;
}

// Where the magic happens
fysh::Fysh fysh::FyshLexer::nextFysh() noexcept {
  while (std::isspace(periscope())) {
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
  case '~': {
    return tilde();
  }
  case '[':
    return goFysh(Species::FYSH_TANK_OPEN);
  case ']':
    return goFysh(Species::FYSH_TANK_CLOSE);
  case '(':
    return goFysh(Species::FYSH_BOWL_OPEN);
  case ')':
    return goFysh(Species::FYSH_BOWL_CLOSE);
  case '-':
    return goFysh(Species::FYSH_FOOD);
  case '=': {
    reel();
    if (match('=')) {
      return Species::EQUAL;
    }
    // We already reeled in =, do not go fysh.
    return Species::ASSIGN;
  }
  case 'o': {
    // Tadpole
    reel();
    if (!match('~')) {
      return cullDeformedFysh();
    }
    if (match('=')) {
      return Species::TADPOLE_GTE;
    }
    if (peekFyshChar() == "≈") {
      eatFyshChar();
      return Species::TADPOLE_GTE;
    }
    // We already reeled in ~, do not go fysh.
    return Species::TADPOLE_GT;
  }
  default:
    // Ascii characters
    if (peekFyshChar() == "♡") {
      eatFyshChar();
      return Species::HEART_MULTIPLY;
    }
    if (peekFyshChar() == "💔") {
      eatFyshChar();
      return Species::HEART_DIVIDE;
    }

    if (peekFyshChar() == "≈") {
      eatFyshChar();

      if (peekFyshChar() == "≈") {
        eatFyshChar();
        return Species::EQUAL;
      }

      return Species::ASSIGN;
    } else {
      return cullDeformedFysh();
    }
  }
}

std::ostream &fysh::operator<<(std::ostream &os, const fysh::FyshChar &f) {
  if (std::holds_alternative<const char *>(f)) {
    os << *std::get<const char *>(f);
  } else {
    os << std::get<std::string_view>(f);
  }
  return os;
}
