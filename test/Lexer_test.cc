#include "../src/Lexer.h"

#include "doctest.h"

using namespace fysh;

TEST_CASE("operators") {
  std::string_view input{"♡ "
                         "<3 "
                         "💔 "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == Species::DIVIDE);
}

TEST_CASE("positive fysh multiply") {
  std::string_view input{"><{{({(o> <3 ><{{({(o>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == 0b011010);
}

TEST_CASE("fysh open & wtf open") {
  std::string_view input{"><> <3 ><{{({(o> ><!@#$> ><> ><!@#$>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == Species::FYSH_OPEN);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == Species::WTF_OPEN);
  CHECK(lexer.nextFysh() == Species::FYSH_OPEN);
  CHECK(lexer.nextFysh() == Species::WTF_OPEN);
}
