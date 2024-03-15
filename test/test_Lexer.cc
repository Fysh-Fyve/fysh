#include "../src/Lexer/Lexer.h"

#include "doctest.h"

using namespace fysh;

#define T(x) CHECK(lexer.nextFysh() == (x));
#define IDENT_DIR(x, n)                                                        \
  do {                                                                         \
    Fysh fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == Species::FYSH_IDENTIFIER);                                   \
    CHECK(fysh.negate == n);                                                   \
  } while (0)

#define SUB_DIR(x, n)                                                          \
  do {                                                                         \
    Fysh fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == Species::SUBMARINE);                                         \
    CHECK(fysh.negate == n);                                                   \
  } while (0)

#define IDENT(x) IDENT_DIR(x, false)

#define INVALID(x)                                                             \
  do {                                                                         \
    Fysh fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == Species::INVALID);                                           \
  } while (0)

TEST_CASE("operators") {
  FyshLexer lexer{"♡ "
                  "<3 "
                  "💔 "
                  "</3 "
                  "& "
                  "| "
                  "^ "
                  "~= "
                  "~≈ "
                  "== "
                  "≈≈ "
                  "= "
                  "≈ "
                  "o~ "
                  "~o "
                  "o~= "
                  "o~≈ "
                  "~o= "
                  "~o≈ "
                  ">> "
                  "<< "};

  T(Species::HEART_MULTIPLY);
  T(Species::HEART_MULTIPLY);
  T(Species::HEART_DIVIDE);
  T(Species::HEART_DIVIDE);

  T(Species::BITWISE_AND);
  T(Species::BITWISE_OR);
  T(Species::CARET);

  T(Species::NOT_EQUAL);
  T(Species::NOT_EQUAL);
  T(Species::EQUAL);
  T(Species::EQUAL);

  T(Species::ASSIGN);
  T(Species::ASSIGN);

  T(Species::TADPOLE_GT);
  T(Species::TADPOLE_LT);
  T(Species::TADPOLE_GTE);
  T(Species::TADPOLE_GTE);
  T(Species::TADPOLE_LTE);
  T(Species::TADPOLE_LTE);

  T(Species::SHIFT_RIGHT);
  T(Species::SHIFT_LEFT);

  T(Species::END);
}

TEST_CASE("positive fysh multiply") {
  FyshLexer lexer{"><{{({(o> <3 ><{{({(o>"};

  T(0b011010);
  T(Species::HEART_MULTIPLY);
  T(0b011010);
  T(Species::END);
}

TEST_CASE("biblically accurate fysh") {
  FyshLexer lexer{"><{{oooo> <ooooooooo}}>< ><oolong> <oomph><"};

  T(0b011);
  T(-0b011);
  IDENT_DIR("oolong", false);
  IDENT_DIR("oomph", true);

  T(Species::END);
}

TEST_CASE("fysh open & wtf open") {
  FyshLexer lexer{"><> <3 ><{{({(o> ><!@#$> ><> ><!@#$>"};

  T(Species::FYSH_OPEN);
  T(Species::HEART_MULTIPLY);
  T(0b011010);
  T(Species::WTF_OPEN);
  T(Species::FYSH_OPEN);
  T(Species::WTF_OPEN);
  T(Species::END);
}

TEST_CASE("random fysh") {
  FyshLexer lexer{"><##> ><###> ><####> <###><"};

  INVALID("><##>");
  T(Species::RANDOM);
  INVALID("><####>");
  INVALID("<###><");
  T(Species::END);
}

TEST_CASE("fysh eye") {
  FyshLexer lexer{"><{{({(°> <3 <°})}>< <°})}><"};

  T(0b011010);
  T(Species::HEART_MULTIPLY);
  T(-0b0101);
  T(-0b0101);
  T(Species::END);
}

TEST_CASE("negative fysh") {
  FyshLexer lexer{"><{{({(o> <3 <o})}>< <o})}><"};

  T(0b011010);
  T(Species::HEART_MULTIPLY);
  T(-0b0101);
  T(-0b0101);
  T(Species::END);
}

TEST_CASE("weird fysh") {
  FyshLexer lexer{"><{{({(> ><{)()}{)()}> <o{}{()}>< <{}{()}>< ><{}o>"};

  T(0b011010);
  T(0b01000110001);
  T(-0b0111001);
  T(-0b0111001);
  T(0b011);
  T(Species::END);
}

TEST_CASE("Bad fysh") {
  FyshLexer lexer{"><{{({(o><DQHUD ><{{({(o>< ><{{((>< ><{{{< ><o{{}}>< "
                  "><{{({(o <o{{}}o ><>"};
  T(0b11010);
  INVALID("<DQHUD");
  T(0b11010);
  INVALID("<");
  T(0b1100);
  INVALID("<");
  INVALID("><{{{<");
  INVALID("><o{{}}><");
  INVALID("><{{({(o");
  INVALID("<o{{}}o");
  T(Species::FYSH_OPEN);
  T(Species::END);
}

TEST_CASE("Swim Left") {
  FyshLexer lexer{"<!@#$>< <>< <!@%$>< <!@#$> <><"};

  T(Species::WTF_CLOSE);
  T(Species::FYSH_CLOSE);
  INVALID("<!@%$><");
  INVALID("<!@#$>");
  T(Species::FYSH_CLOSE);
  T(Species::END);
}

TEST_CASE("identifiers") {
  FyshLexer lexer{
      "><pos> <neg>< ><ostart> <ostart>< ><鱼> ><とと> <魚>< "
      "<سمكة>< ><ᜁᜐ᜔ᜇ> ><ᠨᡳᠮᠠᡥᠠ> "
      // "<°isthisallowed>< ><whataboutthis°>"
  };

  IDENT_DIR("pos", false);
  IDENT_DIR("neg", true);
  IDENT_DIR("ostart", false);
  IDENT_DIR("ostart", true);
  IDENT_DIR("鱼", false);
  IDENT_DIR("とと", false);
  IDENT_DIR("魚", true);
  IDENT_DIR("سمكة", true);
  IDENT_DIR("ᜁᜐ᜔ᜇ", false);
  IDENT_DIR("ᠨᡳᠮᠠᡥᠠ", false);

  // Comment out until we decide what to do with it
  // IDENT_DIR("°isthisallowed", true);
  // IDENT_DIR("whataboutthis°", false);

  T(Species::END);
}

TEST_CASE("increment & decrement") {
  FyshLexer lexer{">><inc> <dec><<"};

  Fysh fysh{lexer.nextFysh()};
  CHECK(fysh == "inc");
  CHECK(fysh == Species::INCREMENT);

  fysh = lexer.nextFysh();
  CHECK(fysh == "dec");
  CHECK(fysh == Species::DECREMENT);

  T(Species::END);
}

TEST_CASE("Terminate") {
  FyshLexer lexer{"~ ~~"};

  T(Species::FYSH_WATER);
  T(Species::FYSH_WATER);
  T(Species::FYSH_WATER);
  T(Species::END);
}

TEST_CASE("Fysh Tank") {
  FyshLexer lexer{"[]"};

  T(Species::FYSH_TANK_OPEN);
  T(Species::FYSH_TANK_CLOSE);
  T(Species::END);
}

TEST_CASE("Fysh If Else") {
  FyshLexer lexer{R"(
><(((^> [ ><fysh> ] ><> <><
><(((*> ><(((^> [ ><result> ] ><> <><
><(((*> ><> <><
)"};

  T(Species::IF);
  T(Species::FYSH_TANK_OPEN);
  IDENT("fysh");
  T(Species::FYSH_TANK_CLOSE);
  T(Species::FYSH_OPEN);
  T(Species::FYSH_CLOSE);

  T(Species::ELSE);
  T(Species::IF);
  T(Species::FYSH_TANK_OPEN);
  IDENT("result");
  T(Species::FYSH_TANK_CLOSE);
  T(Species::FYSH_OPEN);
  T(Species::FYSH_CLOSE);

  T(Species::ELSE);
  T(Species::FYSH_OPEN);
  T(Species::FYSH_CLOSE);

  T(Species::END);
}

TEST_CASE("Arrays") {
  FyshLexer lexer{"><fysh> = [ ><{}o> - ><{}o> ] ~"};

  IDENT("fysh");
  T(Species::ASSIGN);
  T(Species::FYSH_TANK_OPEN);
  T(3);
  T(Species::FYSH_FOOD);
  T(3);
  T(Species::FYSH_TANK_CLOSE);
  T(Species::FYSH_WATER);
  T(Species::END);
}

TEST_CASE("Anchors") {
  FyshLexer lexer{R"(
  (+o ><fysh> ~
  o+) ><fysh> ~
  ><{{> (+o ><fysh> ~
  ><{{> o+) ><fysh> ~
  )"};

  T(Species::ANCHOR_LEFT);
  IDENT("fysh");
  T(Species::FYSH_WATER);

  T(Species::ANCHOR_RIGHT);
  IDENT("fysh");
  T(Species::FYSH_WATER);

  T(3);
  T(Species::ANCHOR_LEFT);
  IDENT("fysh");
  T(Species::FYSH_WATER);

  T(3);
  T(Species::ANCHOR_RIGHT);
  IDENT("fysh");
  T(Species::FYSH_WATER);
  T(Species::END);
}

TEST_CASE("Fysh Factorial") {
  FyshLexer lexer{R"(
><fysh>   = ><{({o> ~
><result> = ><(({o> ~

><(((@> [ ><fysh> o~ ><(({o> ]
><>
	><result> = ><result> ♡ ><fysh> ~
	<fysh><< ~
<><
)"};

  IDENT("fysh");
  T(Species::ASSIGN);
  T(5);
  T(Species::FYSH_WATER);

  IDENT("result");
  T(Species::ASSIGN);
  T(1);
  T(Species::FYSH_WATER);

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
  T(Species::FYSH_WATER);

  Fysh fysh{lexer.nextFysh()};
  CHECK(fysh == "fysh");
  CHECK(fysh == Species::DECREMENT);
  T(Species::FYSH_WATER);

  T(Species::FYSH_CLOSE);

  T(Species::END);
}

TEST_CASE("Comments") {
  FyshLexer lexer{R"(
><//> This is a comment
></*>
This is also a comment
<*/><
)"};

  Fysh fysh{lexer.nextFysh()};
  CHECK(fysh == "This is a comment");
  CHECK(fysh == Species::COMMENT);

  fysh = lexer.nextFysh();
  CHECK(fysh.getBody() == "This is also a comment");
  CHECK(fysh == Species::MULTILINE_COMMENT);

  T(Species::END);
}

TEST_CASE("Fysh Bowl") {
  FyshLexer lexer{"><> ♡ ( ><fysh> ♡ <{{{(())}}}>< ♡ ><fysh> ) <><"};
  T(Species::FYSH_OPEN);
  T(Species::HEART_MULTIPLY);
  T(Species::FYSH_BOWL_OPEN);
  IDENT("fysh");
  T(Species::HEART_MULTIPLY);
  T(-0b1110000111);
  T(Species::HEART_MULTIPLY);
  IDENT("fysh");
  T(Species::FYSH_BOWL_CLOSE);
  T(Species::FYSH_CLOSE);
  T(Species::END);
}

TEST_CASE("TOUCHING") {
  FyshLexer lexer{
      "><>♡(><fysh>♡<{{{(())}}}><<{{{(())}}}><><)))>♡><)))><FYSH><><)))>♡)<><"};
  // ><> ♡ ( ><fysh> ♡ <{{{(())}}}>< <{{{(())}}}>< ><)))> ♡ ><)))> <FYSH><
  // ><)))> ♡ ) <><
  T(Species::FYSH_OPEN);
  T(Species::HEART_MULTIPLY);
  T(Species::FYSH_BOWL_OPEN);
  IDENT_DIR("fysh", false);
  T(Species::HEART_MULTIPLY);
  T(-0b1110000111);
  T(-0b1110000111);
  T(0b000);
  T(Species::HEART_MULTIPLY);
  T(0b000);
  IDENT_DIR("FYSH", true);
  T(0b000);
  T(Species::HEART_MULTIPLY);
  T(Species::FYSH_BOWL_CLOSE);
  T(Species::FYSH_CLOSE);
  T(Species::END);
}

TEST_CASE("Submarines (SUBroutines)") {
  FyshLexer lexer{">(submarine) (submarine)<"};
  SUB_DIR("submarine", false);
  SUB_DIR("submarine", true);
}
