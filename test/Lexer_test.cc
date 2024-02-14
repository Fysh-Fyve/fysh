#include "../src/Lexer.h"

#include "doctest.h"

using namespace fysh;

#define T(x) CHECK(lexer.nextFysh() == (x));
#define IDENT(x)                                                               \
  do {                                                                         \
    auto fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == Species::FYSH_IDENTIFIER);                                   \
  } while (0)

#define INVALID(x)                                                             \
  do {                                                                         \
    auto fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == Species::INVALID);                                           \
  } while (0)

TEST_CASE("operators") {
  std::string_view input{"♡ "
                         "<3 "
                         "💔 "
                         "</3 "
                         "& "
                         "| "
                         "^ "
                         "~= "
                         "== "
                         "= "
                         "o~ "
                         "~o "
                         "o~= "
                         "~o= "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  T(Species::HEART_MULTIPLY);
  T(Species::HEART_MULTIPLY);
  T(Species::HEART_DIVIDE);
  T(Species::HEART_DIVIDE);

  T(Species::BITWISE_AND);
  T(Species::BITWISE_OR);
  T(Species::BITWISE_XOR);

  T(Species::NOT_EQUAL);
  T(Species::EQUAL);

  T(Species::ASSIGN);

  T(Species::TADPOLE_GT);
  T(Species::TADPOLE_LT);
  T(Species::TADPOLE_GTE);
  T(Species::TADPOLE_LTE);

  T(Species::END);
}

TEST_CASE("positive fysh multiply") {
  std::string_view input{"><{{({(o> <3 ><{{({(o>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  T(0b011010);
  T(Species::HEART_MULTIPLY);
  T(0b011010);
  T(Species::END);
}

TEST_CASE("fysh open & wtf open") {
  std::string_view input{"><> <3 ><{{({(o> ><!@#$> ><> ><!@#$>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  T(Species::FYSH_OPEN);
  T(Species::HEART_MULTIPLY);
  T(0b011010);
  T(Species::WTF_OPEN);
  T(Species::FYSH_OPEN);
  T(Species::WTF_OPEN);
  T(Species::END);
}

TEST_CASE("random fysh") {
  std::string_view input{"><##> ><###> ><####> <###>< "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  INVALID("><##>");
  T(Species::RANDOM);
  INVALID("><####>");
  INVALID("<###><");
  T(Species::END);
}

TEST_CASE("negative fysh") {
  std::string_view input{"><{{({(o> <3 <o})}>< <o})}><"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  T(0b011010);
  T(Species::HEART_MULTIPLY);
  T(-0b0101);
  T(-0b0101);
  T(Species::END);
}

TEST_CASE("weird fysh") {
  std::string_view input{"><{{({(> ><{)()}{)()}> <o{}{()}>< <{}{()}>< ><{}o>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};

  T(0b011010);
  T(0b01000110001);
  T(-0b0111001);
  T(-0b0111001);
  T(0b011);
  T(Species::END);
}

TEST_CASE("Bad fysh") {
  std::string_view input{"><{{({(o><DQHUD ><{{({(o>< ><{{((>< ><{{{< ><o{{}}>< "
                         "><{{({(o <o{{}}o ><>"};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  INVALID("><{{({(o><DQHUD");
  INVALID("><{{({(o><");
  INVALID("><{{((><");
  INVALID("><{{{<");
  INVALID("><o{{}}><");
  INVALID("><{{({(o");
  INVALID("<o{{}}o");
  T(Species::FYSH_OPEN);
  T(Species::END);
}

TEST_CASE("Swim Left") {
  std::string_view input{"<!@#$>< <>< <!@%$>< <!@#$> <>< "};
  // Assuming `input` is a std::string or std::string_view
  FyshLexer lexer{input.data()};
  T(Species::WTF_CLOSE);
  T(Species::FYSH_CLOSE);
  INVALID("<!@%$><");
  INVALID("<!@#$>");
  T(Species::FYSH_CLOSE);
  T(Species::END);
}

TEST_CASE("identifiers") {
  std::string_view input{"><pos> <neg>< "};
  FyshLexer lexer{input.data()};
  auto fysh{lexer.nextFysh()};

  CHECK(fysh == "pos");
  CHECK(fysh == Species::FYSH_IDENTIFIER);
  CHECK(fysh.negate == false);

  fysh = lexer.nextFysh();

  CHECK(fysh == "neg");
  CHECK(fysh == Species::FYSH_IDENTIFIER);
  CHECK(fysh.negate == true);

  T(Species::END);
}

TEST_CASE("increment & decrement") {
  std::string_view input{">><inc> <dec><< "};
  FyshLexer lexer{input.data()};

  auto fysh{lexer.nextFysh()};
  CHECK(fysh == "inc");
  CHECK(fysh == Species::INCREMENT);

  fysh = lexer.nextFysh();
  CHECK(fysh == "dec");
  CHECK(fysh == Species::DECREMENT);

  T(Species::END);
}

TEST_CASE("Terminate") {
  std::string_view input{"~ ~~ "};
  FyshLexer lexer{input.data()};
  T(Species::TERMINATE);
  T(Species::TERMINATE);
  T(Species::TERMINATE);
  T(Species::END);
}

TEST_CASE("Fysh Tank") {
  std::string_view input{"[] "};
  FyshLexer lexer{input.data()};
  T(Species::FYSH_TANK_OPEN);
  T(Species::FYSH_TANK_CLOSE);
  T(Species::END);
}

TEST_CASE("Fysh Factorial") {
  std::string_view input{R"(
><fysh>   = ><{({o> ~
><result> = ><(({o> ~

><(((@> [ ><fysh> o~ ><(({o> ]
><>
	><result> = ><result> ♡ ><fysh> ~
	<fysh><< ~
<><
)"};
  FyshLexer lexer{input.data()};

  IDENT("fysh");
  T(Species::ASSIGN);
  T(5);
  T(Species::TERMINATE);

  IDENT("result");
  T(Species::ASSIGN);
  T(1);
  T(Species::TERMINATE);

  T(Species::FYSH_LOOP);

  T(Species::FYSH_TANK_OPEN);
  IDENT("fysh");
  T(Species::TADPOLE_GT);
  T(1);
  T(Species::FYSH_TANK_CLOSE);

  T(Species::FYSH_OPEN);

  IDENT("result");
  T(Species::ASSIGN);
  IDENT("result");
  T(Species::HEART_MULTIPLY);
  IDENT("fysh");
  T(Species::TERMINATE);

  auto fysh{lexer.nextFysh()};
  CHECK(fysh == "fysh");
  CHECK(fysh == Species::DECREMENT);
  T(Species::TERMINATE);

  T(Species::FYSH_CLOSE);

  T(Species::END);
}
