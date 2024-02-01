#include "../src/Lexer.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("testing the next token") {
  std::string_view input{"<3"};
  FyshLexer lexer{input};
  CHECK(lexer.nextToken().is_type(TokenType::HEART_MULTIPLY));
}
