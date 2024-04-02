#include "../src/Lexer/Lexer.h"

#include "doctest.h"
#include "test_util.h"
#include <initializer_list>

using namespace fysh;
using S = Species;

// TODO: Do the other characters
TEST_CASE("Zero Width Joiner") {
  FyshLexer lexer{
      "❤️ "
      "❤️‍🔥 "
      "❤️‍🩹 "
      // "💝 "
      // "❣️ "
      // "🫶🏻 "
      // "🫶🏽 "
      // "🫶🏾 "
      // "🫶🏿 "
  };

  T(S::HEART_MULTIPLY);
  T(S::HEART_MULTIPLY);
  T(S::HEART_MULTIPLY);
  // T(S::HEART_MULTIPLY);
  // T(S::HEART_MULTIPLY);

  T(S::END);
}

TEST_CASE("hearts") {
  const std::initializer_list<const char *> vs = {
      "☙",  "♡",  "♥",  "❣",  "❤",  "❥",  "❦",  "❧",  "🎔", "🖤", "💙",
      "💚", "💛", "💜", "🧡", "🤍", "🤎", "🩶", "🩷", "🩵", "💓", "💕",
      "💖", "💗", "💘", "🫀", "💌", "💞", "💟", "🫶", "<3"};
  std::string input = join_chars(vs);
  FyshLexer lexer{input.data()};

  for (const auto &_ : vs) {
    T(S::HEART_MULTIPLY);
  }
  T(S::END);
}

TEST_CASE("operators") {
  const std::initializer_list<const char *> vs = {
      "💔", "</3", "&",   "|",   "^",   "~=", "~≈", "==", "≈≈", "=",  "≈", "o~",
      "~o", "o~=", "o~≈", "~o=", "~o≈", "=o", "o=", "o≈", "≈o", ">>", "<<"};
  std::string input = join_chars(vs);
  FyshLexer lexer{input.data()};

  T(S::HEART_DIVIDE);
  T(S::HEART_DIVIDE);

  T(S::BITWISE_AND);
  T(S::BITWISE_OR);
  T(S::CARET);

  T(S::NOT_EQUAL);
  T(S::NOT_EQUAL);
  T(S::EQUAL);
  T(S::EQUAL);

  T(S::ASSIGN);
  T(S::ASSIGN);

  T(S::TADPOLE_GT);
  T(S::TADPOLE_LT);
  T(S::TADPOLE_GTE);
  T(S::TADPOLE_GTE);
  T(S::TADPOLE_LTE);
  T(S::TADPOLE_LTE);
  T(S::TADPOLE_LTE);
  T(S::TADPOLE_GTE);
  T(S::TADPOLE_GTE);
  T(S::TADPOLE_LTE);

  T(S::SHIFT_RIGHT);
  T(S::SHIFT_LEFT);

  T(S::END);
}

TEST_CASE("positive fysh multiply") {
  FyshLexer lexer{"><{{({(o> <3 ><{{({(o>"};

  T(0b011010);
  T(S::HEART_MULTIPLY);
  T(0b011010);
  T(S::END);
}
