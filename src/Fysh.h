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

#include <optional>
#include <ostream>
#include <string_view>

#ifndef FYSH_FYSH_H_
#define FYSH_FYSH_H_

namespace fysh {

enum class Species {
  FYSH_LITERAL,      // binary value
  FYSH_IDENTIFIER, // variable
  HEART_MULTIPLY,  // <3 or ♡
  DIVIDE,          // </3 or 💔
  TADPOLE_LT,      // ~o (less than    '<' )
  TADPOLE_GT,      // o~ (greater than '>' )
  TADPOLE_LTE,     // ~o≈ (less than equal to    '<=' )
  TADPOLE_GTE,     // o~≈ (greater than equal to '>=' )
  EQUAL,           // ≈≈  (Equal to '==')
  NOT_EQUAL,       // ~≈  (Not equal to '!=')
  INCREMENT,       // >><fysh> (add 1 'fysh++')
  DECREMENT,       // <fysh><< (sub 1 'fysh--')
  FYSH_TANK_OPEN,  // [ (same as open bracket  '('  )
  FYSH_TANK_CLOSE, // ] (same as closing bracket ')' )
  FYSH_OPEN,       // ><> (same as open curly bracket '{' )
  FYSH_CLOSE,      // <>< (same as closing curly bracket '}' )
  WTF_OPEN,        // WHAT THE FYSH (Throw error opening) ><!@#$>
  WTF_CLOSE,       // WHAT THE FYSH (Throw error closing) <!@#$><
  RANDOM,          // Random fysh ><###>
  COMMENT,         // ><//> Comment
  OPENING_COMMENT, // ></*> Comment
  CLOSING_COMMENT, // Comment <*/><
  INVALID,         // Invalid token!
  CONTINUE,        // Continue trying to parse unicode
  END,             // End of the input

  // TODO bit manipulation
};

class Fysh {
public:
  //-----------------Constructors---------------------
  Fysh() noexcept : species{Species::INVALID} {}
  Fysh(Species inType) noexcept : species{inType} {}

  Fysh(uint32_t integer) noexcept
      : species{Species::FYSH_LITERAL}, value{integer} {}

  Fysh(Species inType, const char *start, std::size_t len) noexcept
      : species{inType}, body(start, len) {}

  Fysh(Species inType, const char *start, const char *end) noexcept
      : species{inType}, body(start, std::distance(start, end)) {}

  // -----------------------METHODS-----------------------

  // check if the species is one of the given species (2 species)
  bool isOneOf(Species type1, Species type2) const noexcept;

  // check if the species is one of the given species (more than 2 species)
  template <typename... Ts>
  bool isOneOf(Species species1, Species species2, Ts... ks) const noexcept {
    return species == species1 || isOneOf(species2, ks...);
  }

  Species getSpecies() const noexcept;
  std::string_view getBody() const noexcept;

  // -----------------------OPERATORS-----------------------
  bool operator==(const Species &in_species) const noexcept {
    return species == in_species;
  }

  bool operator==(const Fysh &other) const noexcept {
    return other.species == species && other.body == body &&
           other.value == value;
  }

  bool operator==(const uint32_t &other) const noexcept {
    return species == Species::FYSH_LITERAL && value == other;
  }

private:
  Species species{};
  std::string_view body{};
  std::optional<uint32_t> value{};
};

// string representation of token type (for testing)
std::ostream &operator<<(std::ostream &os, const Fysh &body);

}; // namespace fysh

#endif // !FYSH_FYSH_H_
