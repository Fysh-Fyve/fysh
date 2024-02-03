#include "../src/Lexer.h"

#include "doctest.h"

TEST_CASE("nextFysh") {
  std::string_view input{"<3"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
}
