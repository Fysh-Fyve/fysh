#include "Fysh.h"
#include <cassert>

Species Fysh::getSpecies() const noexcept { return species; }

bool Fysh::isOneOf(Species species1, Species species2) const noexcept {
  return species == species1 || species == species2;
}

std::string_view Fysh::getBody() const noexcept { return body; }

// string representation of token type (for testing)
constexpr const char *debugType(const Species &species) {
  switch (species) {
  case Species::FYSH_SCALES:
    return "LITERAL";
  case Species::FYSH_IDENTIFIER:
    return "IDENT";
  case Species::HEART_MULTIPLY:
    return "*";
  case Species::DIVIDE:
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
  case Species::COMMENT:
    return "//";
  case Species::OPENING_COMMENT:
    return "/*";
  case Species::CLOSING_COMMENT:
    return "*/";
  }

  assert(false);
}

std::ostream &operator<<(std::ostream &os, const Fysh &value) {
  os << "'" << debugType(value.getSpecies()) << "'" << value.getBody();
  return os;
}
