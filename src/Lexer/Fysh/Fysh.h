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
#ifndef FYSH_FYSH_H_
#define FYSH_FYSH_H_

#include "Species.h"
#include <cassert>
#include <cstdint>
#include <optional>
#include <string_view>

namespace fysh {

class Fysh {
public:
  //-----------------Constructors---------------------
  Fysh() noexcept : species{Species::INVALID} {}
  Fysh(Species inType) noexcept : species{inType} {}

  // fysh literals
  Fysh(std::uint32_t integer, bool negate) noexcept
      : negate{negate}, species{Species::FYSH_LITERAL}, value{integer} {}

  // fysh bones
  Fysh(double floating, bool negate) noexcept
      : negate{negate}, species{Species::FYSH_BONES}, value_float{floating} {}

  Fysh(Species inType, const char *start, std::size_t len) noexcept
      : species{inType}, body(start, len) {}

  Fysh(Species inType, const char *start, const char *end) noexcept
      : species{inType}, body(start, std::distance(start, end)) {}

  // fysh identifiers & submarines
  Fysh(Species inType, const char *start, const char *end, bool negate) noexcept
      : negate{negate}, species{inType},
        body(start, std::distance(start, end)) {}

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
  std::optional<std::uint32_t> getValue() const noexcept;
  std::optional<double> getFloat() const noexcept;

  // -----------------------OPERATORS-----------------------
  template <typename T> bool operator!=(const T &other) const noexcept {
    return !(*this == other);
  }

  bool operator==(const Species &in_species) const noexcept;
  bool operator==(const char *other) const noexcept;
  bool operator==(const Fysh &other) const noexcept;
  bool operator==(const std::uint32_t &other) const noexcept;
  bool compareDouble(const double &other) const noexcept;

  bool negate{};

private:
  Species species{};
  std::string_view body{};
  std::optional<std::uint32_t> value{};
  std::optional<double> value_float{};
};

// string representation of token type (for testing)
std::string debugType(const Fysh &f);

// string representation of token type (for testing)
constexpr const char *debugType(const fysh::Species &species) {
  using fysh::Species;
  switch (species) {
  case Species::FYSH_LITERAL:
    return "LITERAL";
  case Species::FYSH_BONES:
    return "FLOAT";
  case Species::FYSH_IDENTIFIER:
    return "IDENT";
  case Species::ASSIGN:
    return "=";
  case Species::FYSH_LOOP:
    return "while";
  case Species::HEART_MULTIPLY:
    return "*";
  case Species::HEART_DIVIDE:
    return "/";
  case Species::TADPOLE_LT:
    return "<";
  case Species::TADPOLE_GT:
    return ">";
  case Species::TADPOLE_LTE:
    return "<=";
  case Species::TADPOLE_GTE:
    return ">=";
  case Species::EQUAL:
    return "==";
  case Species::NOT_EQUAL:
    return "!=";
  case Species::INCREMENT:
    return "++";
  case Species::DECREMENT:
    return "--";
  case Species::FYSH_TANK_OPEN:
    return "[";
  case Species::FYSH_TANK_CLOSE:
    return "]";
  case Species::FYSH_BOWL_OPEN:
    return "(";
  case Species::FYSH_BOWL_CLOSE:
    return ")";
  case Species::FYSH_OPEN:
    return "{";
  case Species::FYSH_CLOSE:
    return "}";
  case Species::WTF_OPEN:
    return "WTF(";
  case Species::WTF_CLOSE:
    return ")WTF";
  case Species::GRILLED_FYSH:
    return "GRILLED_FYSH";
  case Species::COMMENT:
    return "//";
  case Species::MULTILINE_COMMENT:
    return "/**/";
  case Species::INVALID:
    return "INVALID";
  case Species::END:
    return "END";
  case Species::BITWISE_AND:
    return "&";
  case Species::BITWISE_OR:
    return "|";
  case Species::CARET:
    return "^";
  case Species::FYSH_WATER:
    return "~";
  case Species::SHIFT_LEFT:
    return "<<";
  case Species::SHIFT_RIGHT:
    return ">>";
  case Species::IF:
    return "if";
  case Species::ELSE:
    return "else";
  case Species::FYSH_FOOD:
    return "-";
  case Species::ANCHOR_LEFT:
    return "(+o";
  case Species::ANCHOR_RIGHT:
    return "o+)";
  case Species::SUBMARINE:
    return "SUBMARINE";
  case Species::SQUID:
    return "return";
  case Species::BROKEN_FYSH:
    return "break";
  }
  assert(false);
}

}; // namespace fysh

#endif // !FYSH_FYSH_H_
