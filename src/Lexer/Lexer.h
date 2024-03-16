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
 * \file Lexer.h
 */
#ifndef FYSH_LEXER_H_
#define FYSH_LEXER_H_

#include "../Fysh/Fysh.h"
#include <variant>

// Uncomment to print the current line where periscope is called
// #define FYSH_DEBUG

namespace fysh {

struct FyshChar : public std::variant<const char *, std::string_view> {
  bool operator==(const char &x) const;
  bool operator==(const char *x) const;
};

std::ostream &operator<<(std::ostream &os, const fysh::FyshChar &f);

enum class FyshDirection { RIGHT, LEFT };

// code is based off of this:
// https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

class FyshLexer {
public:
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}
  Fysh nextFysh() noexcept;
  unsigned int fyshingLine() { return line; }
  const char *rest() const noexcept { return current; }
#ifdef FYSH_DEBUG
  void printRest();
#endif // FYSH_DEBUG

private:
  const char *current = nullptr;
  // Marks the start of the current fysh
  const char *fyshStart = nullptr;
  unsigned int line = 1;

  char reel() noexcept;
  bool isUnicode() const noexcept;
  bool isUnicode(char c) const noexcept;
  bool match(char x) noexcept;
  bool match(const char *x) noexcept;
#ifdef FYSH_DEBUG
  char periscope(int line = -1) const noexcept;
#else
  char periscope() const noexcept { return *current; };
#endif // FYSH_DEBUG
  Fysh goFysh(Species species) noexcept;
  Fysh openWTF() noexcept;
  Fysh closeWTF() noexcept;
  Fysh fyshClose() noexcept;
  Fysh fyshOutline() noexcept;
  Fysh scales(FyshDirection dir) noexcept;
  Fysh swimLeft() noexcept;
  Fysh swimRight() noexcept;
  Fysh random() noexcept;
  Fysh slashOrComment() noexcept;
  Fysh namedFysh(FyshDirection dir, Species species) noexcept;
  Fysh cullDeformedFysh() noexcept;
  Fysh tilde() noexcept;
  FyshChar eatFyshChar() noexcept;
  FyshChar peekFyshChar() noexcept;
  bool expectFyshChar(const char *c) noexcept;
};

}; // namespace fysh

#endif // !FYSH_LEXER_H_
