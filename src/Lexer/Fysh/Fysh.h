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
#include <cstdint>
#include <llvm/Support/raw_ostream.h>
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

  // -----------------------OPERATORS-----------------------
  template <typename T> bool operator!=(const T &other) const noexcept {
    return !(*this == other);
  }

  bool operator==(const Species &in_species) const noexcept;
  bool operator==(const char *other) const noexcept;
  bool operator==(const Fysh &other) const noexcept;
  bool operator==(const std::uint32_t &other) const noexcept;

  bool negate{};

private:
  Species species{};
  std::string_view body{};
  std::optional<std::uint32_t> value{};
};

// string representation of token type (for testing)
llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const Fysh &body);

}; // namespace fysh

#endif // !FYSH_FYSH_H_
