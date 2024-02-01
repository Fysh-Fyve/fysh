#include "../src/Lexer.h"

#include "doctest.h"

TEST_CASE("testing the next token") {
  std::string_view input{"<3"};
  FyshLexer lexer{input};
  CHECK(lexer.nextToken().isType(TokenType::HEART_MULTIPLY));
}
