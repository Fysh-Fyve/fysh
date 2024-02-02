#include "../src/Lexer.h"

#include "doctest.h"

TEST_CASE("nextFysh") {
  std::string_view input{"<3"};
  FyshLexer lexer{input};
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
}
