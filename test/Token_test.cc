#include "../src/Token.h"

#include "doctest.h"

TEST_CASE("testing isOneOf") {
  Token t{TokenType::HEART_MULTIPLY};
  CHECK(t.isOneOf(TokenType::HEART_MULTIPLY, TokenType::DIVIDE));
}
