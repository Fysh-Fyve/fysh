#include "../src/Lexer.h"

#include "doctest.h"

using namespace fysh;

TEST_CASE("operators") {
  std::string_view input{"♡ "
                         "<3 "
                         "💔 "
                         "</3 "
                         "& "
                         "| "
                         "^ "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == Species::HEART_DIVIDE);
  CHECK(lexer.nextFysh() == Species::HEART_DIVIDE);

  CHECK(lexer.nextFysh() == Species::BITWISE_AND);
  CHECK(lexer.nextFysh() == Species::BITWISE_OR);
  CHECK(lexer.nextFysh() == Species::BITWISE_XOR);

  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("positive fysh multiply") {
  std::string_view input{"><{{({(o> <3 ><{{({(o>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == Species::END);
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
  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("random fysh") {
  std::string_view input{"><##> ><###> ><####> <###>< "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == "><##>");
  CHECK(lexer.nextFysh() == Species::RANDOM);
  CHECK(lexer.nextFysh() == "><####>");
  CHECK(lexer.nextFysh() == "<###><");
  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("negative fysh") {
  std::string_view input{"><{{({(o> <3 <o})}>< <o})}><"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == Species::HEART_MULTIPLY);
  CHECK(lexer.nextFysh() == -0b0101);
  CHECK(lexer.nextFysh() == -0b0101);
  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("weird fysh") {
  std::string_view input{"><{{({(> ><{)()}{)()}> <o{}{()}>< <{}{()}>< ><{}o>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  CHECK(lexer.nextFysh() == 0b011010);
  CHECK(lexer.nextFysh() == 0b01000110001);
  CHECK(lexer.nextFysh() == -0b0111001);
  CHECK(lexer.nextFysh() == -0b0111001);
  CHECK(lexer.nextFysh() == 0b011);
  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("Bad fysh") {
  std::string_view input{"><{{({(o><DQHUD ><{{({(o>< ><{{((>< ><{{{< ><o{{}}>< "
                         "><{{({(o <o{{}}o ><>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == "><{{({(o><DQHUD");
  CHECK(lexer.nextFysh() == "><{{({(o><");
  CHECK(lexer.nextFysh() == "><{{((><");
  CHECK(lexer.nextFysh() == "><{{{<");
  CHECK(lexer.nextFysh() == "><o{{}}><");
  CHECK(lexer.nextFysh() == "><{{({(o");
  CHECK(lexer.nextFysh() == "<o{{}}o");
  CHECK(lexer.nextFysh() == Species::FYSH_OPEN);
  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("Swim Left") {
  std::string_view input{"<!@#$>< <>< <!@%$>< <!@#$> <>< "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == Species::WTF_CLOSE);
  CHECK(lexer.nextFysh() == Species::FYSH_CLOSE);
  CHECK(lexer.nextFysh() == "<!@%$><");
  CHECK(lexer.nextFysh() == "<!@#$>");
  CHECK(lexer.nextFysh() == Species::FYSH_CLOSE);
  CHECK(lexer.nextFysh() == Species::END);
}

TEST_CASE("identifiers") {
  std::string_view input{"><fysh> <fysh>< "};
  FyshLexer lexer{input.data()};
  CHECK(lexer.nextFysh() == "fysh");
  CHECK(lexer.nextFysh() == "fysh");
  CHECK(lexer.nextFysh() == Species::END);
}
