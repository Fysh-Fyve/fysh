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
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}
  Fysh nextFysh() noexcept;
  const char* rest() const noexcept { return current; }

private:
    const char* current = nullptr;

    char get()  noexcept {return *current++;};
    char peek() noexcept {return *current;};
    void skipWhitespace() noexcept;
    void gotoEndOfToken() noexcept;
    bool isFyshEye(char c) noexcept;
    Fysh tryUnicode(const char* bytes, Species s) noexcept;
    Fysh unicode() noexcept;
    Fysh heart() noexcept;
    Fysh heartBreak() noexcept;
    Fysh openWTF() noexcept;
    Fysh closeWTF() noexcept;
    Fysh fyshOpen() noexcept;
    Fysh fyshClose() noexcept;
    Fysh scales(bool positive) noexcept;
    Fysh positiveScales() noexcept;
    Fysh negativeScales() noexcept;
    Fysh fyshOutline() noexcept;
    Fysh swimLeft() noexcept;
    Fysh swimRight() noexcept;
    Fysh random() noexcept;
    Fysh slashOrComment() noexcept;
    Fysh identifier() noexcept;
    Fysh isScaleChar(char c) noexcept;
    Fysh convertScaleToBinary(bool positive) noexcept;
};

}; // namespace fysh

#ifdef FYSH_DEBUG
#define peek() peek(__LINE__)
#endif

#endif // !FYSH_LEXER_H_
