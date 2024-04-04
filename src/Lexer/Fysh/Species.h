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

#include <cassert>
#include <string>
namespace fysh {

enum class Species {
  /*! binary value */
  FYSH_LITERAL,
  /*! floating point value ><}-}-}> */
  FYSH_BONES,
  /*! variable */
  FYSH_IDENTIFIER,
  /*! <3 or ♡ */
  HEART_MULTIPLY,
  /*! </3 or 💔 */
  HEART_DIVIDE,
  /*! ~o (less than    '<' ) */
  TADPOLE_LT,
  /*! o~ (greater than '>' ) */
  TADPOLE_GT,
  /*! ~o≈ (less than equal to    '<=' ) */
  TADPOLE_LTE,
  /*! o~≈ (greater than equal to '>=' ) */
  TADPOLE_GTE,
  /*! ≈ */
  ASSIGN,
  /*! ≈≈  (Equal to '==') */
  EQUAL,
  /*! ~≈  (Not equal to '!=') */
  NOT_EQUAL,
  /*! >><fysh> (add 1 'fysh++') */
  INCREMENT,
  /*! <fysh><< (sub 1 'fysh--') */
  DECREMENT,
  /*! [ (used for Arrays, loops, and conditionals) */
  FYSH_TANK_OPEN,
  /*! ] */
  FYSH_TANK_CLOSE,
  /*! ( (Used for FISHS (BEDMAS)) */
  FYSH_BOWL_OPEN,
  /*! ) */
  FYSH_BOWL_CLOSE,
  /*! ><> (same as open curly bracket '{' ) */
  FYSH_OPEN,
  /*! <>< (same as closing curly bracket '}' ) */
  FYSH_CLOSE,
  /*! WHAT THE FYSH (Throw error opening) ><!@#$> */
  WTF_OPEN,
  /*! WHAT THE FYSH (Throw error closing) <!@#$>< */
  WTF_CLOSE,
  /*! Random fysh ><###> */
  GRILLED_FYSH,
  /*! ><(((@> */
  FYSH_LOOP,
  /*! ><//> Comment */
  COMMENT,
  /*! Multiline Comment */
  MULTI_COMMENT,
  /*! Invalid token! */
  INVALID,
  /*! End of the input */
  END,
  /*! & */
  BITWISE_AND,
  /*! | */
  BITWISE_OR,
  /*! ! */
  BITWISE_NOT,
  /*! ^ */
  CARET,
  /*! && */
  LOGICAL_AND,
  /*! || */
  LOGICAL_OR,
  /* !! */
  LOGICAL_NOT,
  /*! ~ */
  FYSH_WATER,
  /*! << */
  SHIFT_LEFT,
  /*! \>\> */
  SHIFT_RIGHT,
  /*! ><(((^> */
  IF,
  /*! ><(((*> */
  ELSE,
  /*! \- */
  FYSH_FOOD,
  /*! (+o */
  ANCHOR_LEFT,
  /*! o+) */
  ANCHOR_RIGHT,
  /*! (submarine)< */
  SUBMARINE,
  /*! <~ return operator */
  SQUID,
  /*! ><\/> or <\/>< (break) */
  BROKEN_FYSH,
};

/**
 * String representation of token type (for testing)
 */
constexpr const char *str(const fysh::Species &species) {
  using S = fysh::Species;
  switch (species) {
    // clang-format off
  case S::FYSH_LITERAL:    return "LITERAL";
  case S::FYSH_BONES:      return "FLOAT";
  case S::FYSH_IDENTIFIER: return "IDENT";
  case S::ASSIGN:          return "=";
  case S::FYSH_LOOP:       return "while";
  case S::HEART_MULTIPLY:  return "*";
  case S::HEART_DIVIDE:    return "/";
  case S::TADPOLE_LT:      return "<";
  case S::TADPOLE_GT:      return ">";
  case S::TADPOLE_LTE:     return "<=";
  case S::TADPOLE_GTE:     return ">=";
  case S::EQUAL:           return "==";
  case S::NOT_EQUAL:       return "!=";
  case S::INCREMENT:       return "++";
  case S::DECREMENT:       return "--";
  case S::FYSH_TANK_OPEN:  return "[";
  case S::FYSH_TANK_CLOSE: return "]";
  case S::FYSH_BOWL_OPEN:  return "(";
  case S::FYSH_BOWL_CLOSE: return ")";
  case S::FYSH_OPEN:       return "{";
  case S::FYSH_CLOSE:      return "}";
  case S::WTF_OPEN:        return "WTF(";
  case S::WTF_CLOSE:       return ")WTF";
  case S::GRILLED_FYSH:    return "GRILLED_FYSH";
  case S::COMMENT:         return "//";
  case S::MULTI_COMMENT:   return "/**/";
  case S::INVALID:         return "INVALID";
  case S::END:             return "END";
  case S::BITWISE_AND:     return "&";
  case S::BITWISE_OR:      return "|";
  case S::BITWISE_NOT:     return "!";
  case S::CARET:           return "^";
  case S::LOGICAL_AND:     return "&&";
  case S::LOGICAL_OR:      return "||";
  case S::LOGICAL_NOT:     return "!!";
  case S::FYSH_WATER:      return "~";
  case S::SHIFT_LEFT:      return "<<";
  case S::SHIFT_RIGHT:     return ">>";
  case S::IF:              return "if";
  case S::ELSE:            return "else";
  case S::FYSH_FOOD:       return "-";
  case S::ANCHOR_LEFT:     return "(+o";
  case S::ANCHOR_RIGHT:    return "o+)";
  case S::SUBMARINE:       return "SUBMARINE";
  case S::SQUID:           return "return";
  case S::BROKEN_FYSH:     return "break";
    // clang-format on
  }
  assert(false);
  // should never be here
  return nullptr;
}

} // namespace fysh

namespace std {
inline string to_string(fysh::Species s) { return string(str(s)); }
}; // namespace std

#endif // !FYSH_SPECIES_H_
