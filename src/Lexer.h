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

namespace fysh {

// code is based off of this:
// https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

class FyshLexer {
public:
  // stream is the start of the input string
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}

  Fysh nextFysh() noexcept;

private:
  Fysh identifier() noexcept;
  Fysh number() noexcept;
  Fysh scales() noexcept;
  Fysh slashOrComment() noexcept;
  Fysh atom(Species) noexcept;
  Fysh unicode() noexcept;
  Fysh tryUnicode(const char *bytes, Species s) noexcept;
  Fysh fyshOutline() noexcept;

  char peek() const noexcept { return *current; }
  char get() noexcept { return *current++; }

  const char *current = nullptr;
};

}; // namespace fysh

#endif // !FYSH_LEXER_H_
