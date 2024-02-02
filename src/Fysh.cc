#include "Fysh.h"
#include <cassert>

Species Fysh::type() const noexcept { return species; }

bool Fysh::isOneOf(Species type1, Species type2) const noexcept {
  return species == type1 || species == type2;
}

std::string_view Fysh::val() const noexcept { return value; }

constexpr const char *debugType(const Species &type) {
  switch (type) {
  case Species::FYSH_LITERAL:
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
  os << "'" << debugType(value.type()) << "'" << value.val();
  return os;
}
