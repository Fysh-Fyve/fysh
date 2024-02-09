/**
 * Copyright (C) 2024 Yahya Al-Shamali, Kyle Prince
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

fysh::Species fysh::Fysh::getSpecies() const noexcept { return species; }
std::optional<uint32_t> fysh::Fysh::getValue() const noexcept { return value; }

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
  case Species::FYSH_IDENTIFIER:
    return "IDENT";
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
  case Species::FYSH_OPEN:
    return "{";
  case Species::FYSH_CLOSE:
    return "}";
  case Species::WTF_OPEN:
    return "WTF(";
  case Species::WTF_CLOSE:
    return ")WTF";
  case Species::RANDOM:
    return "RANDOM";
  case Species::COMMENT:
    return "//";
  case Species::OPENING_COMMENT:
    return "/*";
  case Species::CLOSING_COMMENT:
    return "*/";
  case Species::INVALID:
    return "INVALID";
  case Species::CONTINUE:
    return "CONTINUE";
  case Species::END:
    return "END";
  case Species::BITWISE_AND:
    return "&";
  case Species::BITWISE_OR:
    return "|";
  case Species::BITWISE_XOR:
    return "^";
  }

  assert(false);
}

std::ostream &fysh::operator<<(std::ostream &os, const fysh::Fysh &f) {
  using fysh::Species;
  switch (f.getSpecies()) {
  case Species::FYSH_LITERAL: {
    auto val{f.getValue()};
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
  case Species::FYSH_IDENTIFIER:
  case Species::INVALID: {
    os << debugType(f.getSpecies()) << "`" << f.getBody() << "`";
    break;
  }
  default:
    os << "'" << debugType(f.getSpecies()) << "'";
  }
  return os;
}
