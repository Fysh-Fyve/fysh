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
#include <cassert>
#include <cstdint>

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

llvm::raw_ostream &fysh::operator<<(llvm::raw_ostream &os,
                                    const fysh::Fysh &f) {
  using fysh::Species;
  switch (f.getSpecies()) {
  case Species::FYSH_LITERAL: {
    std::optional<uint32_t> val{f.getValue()};
    os << "(";
    if (f.negate) {
      os << "-";
    }
    if (val.has_value()) {
      os << val.value();
    } else {
      os << "None";
    }
    os << ")";
    break;
  }
  case Species::FYSH_BONES: {
    std::optional<double> val{f.getFloat()};
    os << "(";
    if (f.negate) {
      os << "-";
    }
    if (val.has_value()) {
      os << val.value();
    } else {
      os << "None";
    }
    os << ")";
    break;
  }
  case Species::INCREMENT:
  case Species::DECREMENT:
  case Species::FYSH_IDENTIFIER:
  case Species::COMMENT:
  case Species::SUBMARINE:
  case Species::MULTILINE_COMMENT:
  case Species::INVALID: {
    os << debugType(f.getSpecies()) << "`" << f.getBody() << "`";
    break;
  }
  default:
    os << "'" << debugType(f.getSpecies()) << "'";
  }
  return os;
}

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
