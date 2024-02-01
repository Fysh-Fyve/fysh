#include "../asm/Register.h"

#include "doctest.h"

TEST_CASE("lookupRegister") {
  CHECK(lookupRegister("x0") == 0);
  CHECK(lookupRegister("zero") == 0);
  CHECK(lookupRegister("sp") == 2);

  CHECK(lookupRegister("invalid") == -1);
}
