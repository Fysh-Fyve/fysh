#include "../src/Lexer.h"

#include "doctest.h"
#include <iostream>

using namespace fysh;

TEST_CASE("operators") {
  std::string_view input{"♡ "
                         "<3 "
                         "💔 "
                         "</3 "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == Species::DIVIDE);
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

TEST_CASE("random fysh") {
  std::string_view input{"><##> ><###> ><####> <###><"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::RANDOM);
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::INVALID);
}

TEST_CASE("negative fysh") {
  std::string_view input{"><{{({(o> <3 <o})}>< <o})}><"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == ~0b0101);
}

TEST_CASE("weird fysh") {
  std::string_view input{"><{{({(> ><{)()}{)()}> <o{}{()}>< <{}{()}>< ><{}o>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == 0b01000110001);
  CHECK(lexer.nextFysh() == ~0b0111001);
  CHECK(lexer.nextFysh() == ~0b0111001);
  CHECK(lexer.nextFysh() == 0b011);
}

TEST_CASE("Bad fysh") {
  std::string_view input{
      "><{{({(o><DQHUD ><{{({(o>< ><{{((>< ><{{{< ><o{{}}><"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::INVALID);
}

TEST_CASE("Swim Left") {
  std::string_view input{"<!@#$>< <>< <!@%$>< <!@#$>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == Species::WTF_CLOSE);
  CHECK(lexer.nextFysh() == Species::FYSH_CLOSE);
  CHECK(lexer.nextFysh() == Species::INVALID);
  CHECK(lexer.nextFysh() == Species::INVALID);
}
