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

bool fysh::Fysh::isOneOf(Species species1, Species species2) const noexcept {
  return species == species1 || species == species2;
}

std::string_view fysh::Fysh::getBody() const noexcept { return body; }

bool fysh::Fysh::operator==(const Species &in_species) const noexcept {
  return species == in_species;
}

bool fysh::Fysh::operator==(const char *other) const noexcept {
  using S = Species;
  switch (species) {
  case S::FYSH_IDENTIFIER:
  case S::INCREMENT:
  case S::DECREMENT:
  case S::COMMENT:
  case S::MULTI_COMMENT:
  case S::SUBMARINE:
  case S::INVALID:
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

std::string std::to_string(const fysh::Fysh &f) {
  using S = fysh::Species;
  switch (f.getSpecies()) {
  case S::FYSH_LITERAL: {
    std::optional<uint32_t> val{f.getValue()};
    return {(f.negate ? "-" : "") +
            (val.has_value() ? std::to_string(val.value()) : "None")};
  }
  case S::FYSH_BONES: {
    std::optional<double> val{f.getFloat()};
    return {(f.negate ? "-" : "") +
            (val.has_value() ? std::to_string(val.value()) : "None")};
  }
  case S::INCREMENT:
  case S::DECREMENT:
  case S::FYSH_IDENTIFIER:
  case S::COMMENT:
  case S::SUBMARINE:
  case S::MULTI_COMMENT:
  case S::INVALID: {
    return {std::to_string(f.getSpecies()) + "`" + std::string(f.getBody()) +
            "`"};
  }
  default:
    return {"'" + std::to_string(f.getSpecies()) + "'"};
  }
}
