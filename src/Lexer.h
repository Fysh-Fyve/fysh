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
#include "Fysh.h"
#include <variant>

#ifndef FYSH_LEXER_H_
#define FYSH_LEXER_H_

// Uncomment to print the current line where periscope is called
// #define FYSH_DEBUG

namespace fysh {

struct FyshChar : public std::variant<const char *, std::string_view> {
  template <typename T> bool operator!=(const T &x) const { return *this != x; }
  bool operator==(const char &x) const {
    return std::holds_alternative<const char *>(*this) &&
           *std::get<const char *>(*this) == x;
  }
  bool operator==(const char *x) const {
    return std::holds_alternative<std::string_view>(*this) &&
           std::get<std::string_view>(*this) == x;
  }
};

std::ostream &operator<<(std::ostream &os, const fysh::FyshChar &f);

enum class FyshDirection { RIGHT, LEFT };

// code is based off of this:
// https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

class FyshLexer {
public:
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}
  Fysh nextFysh() noexcept;
  const char *rest() const noexcept { return current; }
#ifdef FYSH_DEBUG
  void printRest();
#endif // FYSH_DEBUG

private:
  const char *current = nullptr;
  // Marks the start of the current fysh
  const char *fyshStart = nullptr;

  char reel() noexcept { return *current++; };
#ifdef FYSH_DEBUG
  char periscope(int line = -1) const noexcept;
#else
  char periscope() const noexcept { return *current; };
#endif // FYSH_DEBUG
  Fysh goFysh(Species species) noexcept;
  bool isFyshEye(char c) noexcept;
  Fysh tryUnicode(const char *bytes, Species s) noexcept;
  Fysh unicode() noexcept;
  Fysh heart() noexcept;
  Fysh heartBreak() noexcept;
  Fysh openWTF() noexcept;
  Fysh closeWTF() noexcept;
  Fysh fyshOpen() noexcept;
  Fysh fyshClose() noexcept;
  Fysh fyshOutline() noexcept;
  Fysh scales(FyshDirection dir) noexcept;
  Fysh swimLeft() noexcept;
  Fysh swimRight() noexcept;
  Fysh random() noexcept;
  Fysh slashOrComment() noexcept;
  Fysh identifier(FyshDirection dir, bool increment = false) noexcept;
  Fysh cullDeformedFysh() noexcept;
  FyshChar eatFyshChar() noexcept;
  FyshChar peekFyshChar() noexcept;
};

}; // namespace fysh

#endif // !FYSH_LEXER_H_
