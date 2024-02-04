#include "../src/Fysh.h"

#include "doctest.h"

using namespace fysh;

TEST_CASE("isOneOf") {
  Fysh t{Species::HEART_MULTIPLY};
  CHECK(t.isOneOf(Species::HEART_MULTIPLY, Species::DIVIDE));
}
