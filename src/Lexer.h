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
 * \file Lexer.h
 */
#include "Fysh.h"

#ifndef FYSH_LEXER_H_
#define FYSH_LEXER_H_

// Uncomment to print the current line where peek is called
// #define FYSH_DEBUG

#ifdef FYSH_DEBUG
#include <iostream>
#endif // FYSH_DEBUG

namespace fysh {

// code is based off of this:
// https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

class FyshLexer {
public:
  // stream is the start of the input string
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}

  Fysh nextFysh() noexcept;
  const char *rest() const noexcept { return current; }

private:
  Fysh identifier() noexcept;
  Fysh number() noexcept;
  Fysh scales(bool) noexcept;
  Fysh slashOrComment() noexcept;
  Fysh atom(Species) noexcept;
  Fysh unicode() noexcept;
  Fysh tryUnicode(const char *bytes, Species s) noexcept;
  Fysh fyshOutline() noexcept;
  Fysh openWTF() noexcept;
  Fysh closeWTF() noexcept;
  Fysh fyshOpen() noexcept;
  Fysh fyshClose() noexcept;
  Fysh tadpole() noexcept;
  Fysh random() noexcept;
  Fysh heart() noexcept;
  Fysh heartBreak() noexcept;
  Fysh swimRight() noexcept;
  Fysh swimLeft() noexcept;
  bool isFyshEye(char) noexcept;
  bool isPositiveScale() noexcept;
#ifdef FYSH_DEBUG
  char peek(int line = -1) const noexcept {
    if (line > 0) {
      std::cout << "Current (line " << line << "): " << *current << std::endl;
    }
#else
  char peek() const noexcept {
#endif // FYSH_DEBUG
    return *current;
  }
  char get() noexcept { return *current++; }
  void gotoEndOfToken() noexcept;

  const char *current = nullptr;
};

}; // namespace fysh

#ifdef FYSH_DEBUG
#define peek() peek(__LINE__)
#endif

#endif // !FYSH_LEXER_H_
