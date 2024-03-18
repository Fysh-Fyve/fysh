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
 * \file Fysh.h
 */
/*
Reference:
https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

Definitions for the Fysh class
Species: enum class for the different types of Fysh tokens
body: string_view for each token (the actual value of the token)
Fysh: an object with a species and body
Stream: the input string
Current: the current position in the input string
*/
#ifndef FYSH_SPECIES_H_
#define FYSH_SPECIES_H_

namespace fysh {

enum class Species {
  FYSH_LITERAL,      // binary value
  FYSH_IDENTIFIER,   // variable
  HEART_MULTIPLY,    // <3 or ♡
  HEART_DIVIDE,      // </3 or 💔
  TADPOLE_LT,        // ~o (less than    '<' )
  TADPOLE_GT,        // o~ (greater than '>' )
  TADPOLE_LTE,       // ~o≈ (less than equal to    '<=' )
  TADPOLE_GTE,       // o~≈ (greater than equal to '>=' )
  ASSIGN,            // ≈
  EQUAL,             // ≈≈  (Equal to '==')
  NOT_EQUAL,         // ~≈  (Not equal to '!=')
  INCREMENT,         // >><fysh> (add 1 'fysh++')
  DECREMENT,         // <fysh><< (sub 1 'fysh--')
  FYSH_TANK_OPEN,    // [ (used for Arrays, loops, and conditionals)
  FYSH_TANK_CLOSE,   // ]
  FYSH_BOWL_OPEN,    // ( (Used for FISHS (BEDMAS))
  FYSH_BOWL_CLOSE,   // )
  FYSH_OPEN,         // ><> (same as open curly bracket '{' )
  FYSH_CLOSE,        // <>< (same as closing curly bracket '}' )
  WTF_OPEN,          // WHAT THE FYSH (Throw error opening) ><!@#$>
  WTF_CLOSE,         // WHAT THE FYSH (Throw error closing) <!@#$><
  GRILLED_FYSH,      // Random fysh ><###>
  FYSH_LOOP,         // ><(((@>
  COMMENT,           // ><//> Comment
  MULTILINE_COMMENT, // ></*> Comment <*/><
  INVALID,           // Invalid token!
  END,               // End of the input
  BITWISE_AND,       // &
  BITWISE_OR,        // |
  CARET,             // ^
  FYSH_WATER,        // ~
  SHIFT_LEFT,        // <<
  SHIFT_RIGHT,       // >>
  IF,                // ><(((^>
  ELSE,              // ><(((*>
  FYSH_FOOD,         // -
  ANCHOR_LEFT,       // (+o
  ANCHOR_RIGHT,      // o+)
  SUBMARINE,         // (submarine)<
  SQUID,             // <~ return operator
};

}

#endif // !FYSH_SPECIES_H_
