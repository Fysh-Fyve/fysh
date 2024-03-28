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
 * \file Fysh.cc
 */
#include "Fysh.h"
#include <cstdint>
#include <string>

fysh::Species fysh::Fysh::getSpecies() const noexcept { return species; }
std::optional<std::uint32_t> fysh::Fysh::getValue() const noexcept {
  return value;
}

std::optional<double> fysh::Fysh::getFloat() const noexcept {
  return value_float;
}

bool fysh::Fysh::isOneOf(fysh::Species species1,
                         fysh::Species species2) const noexcept {
  return species == species1 || species == species2;
}

std::string_view fysh::Fysh::getBody() const noexcept { return body; }

bool fysh::Fysh::operator==(const Species &in_species) const noexcept {
  return species == in_species;
}

bool fysh::Fysh::operator==(const char *other) const noexcept {
  switch (species) {
  case Species::FYSH_IDENTIFIER:
  case Species::INCREMENT:
  case Species::DECREMENT:
  case Species::COMMENT:
  case Species::MULTILINE_COMMENT:
  case Species::SUBMARINE:
  case Species::INVALID:
    return body == other;
  default:
    return false;
  }
}

bool fysh::Fysh::operator==(const Fysh &other) const noexcept {
  return other.species == species && other.body == body && other.value == value;
}

bool fysh::Fysh::operator==(const std::uint32_t &other) const noexcept {
  if (!value.has_value()) {
    return false;
  }
  std::uint32_t intValue = value.value();
  return species == Species::FYSH_LITERAL &&
         (negate ? -intValue : intValue) == other;
}

bool fysh::Fysh::compareDouble(const double &other) const noexcept {
  if (!value_float.has_value()) {
    return false;
  }
  double floatValue = value_float.value();
  return species == Species::FYSH_BONES &&
         (negate ? -floatValue : floatValue) == other;
}

std::string fysh::debugType(const fysh::Fysh &f) {
  using fysh::Species;
  switch (f.getSpecies()) {
  case Species::FYSH_LITERAL: {
    std::optional<uint32_t> val{f.getValue()};
    return {(f.negate ? "-" : "") +
            (val.has_value() ? std::to_string(val.value()) : "None")};
  }
  case Species::FYSH_BONES: {
    std::optional<double> val{f.getFloat()};
    return {(f.negate ? "-" : "") +
            (val.has_value() ? std::to_string(val.value()) : "None")};
  }
  case Species::INCREMENT:
  case Species::DECREMENT:
  case Species::FYSH_IDENTIFIER:
  case Species::COMMENT:
  case Species::SUBMARINE:
  case Species::MULTILINE_COMMENT:
  case Species::INVALID: {
    return {std::string(fysh::debugType(f.getSpecies())) + "`" +
            std::string(f.getBody()) + "`"};
  }
  default:
    return {"'" + std::string(fysh::debugType(f.getSpecies())) + "'"};
  }
}
