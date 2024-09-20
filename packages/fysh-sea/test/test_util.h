#ifndef FYSH_TEST_UTIL_H_
#define FYSH_TEST_UTIL_H_

#include <iterator>
#include <sstream>

#define T(x) CHECK(lexer.nextFysh() == (x));
#define F(x) CHECK(lexer.nextFysh().compareDouble(x));
#define IDENT_DIR(x, n)                                                        \
  do {                                                                         \
    Fysh fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == S::FYSH_IDENTIFIER);                                         \
    CHECK(fysh.negate == n);                                                   \
  } while (0)

#define SUB_DIR(x, n)                                                          \
  do {                                                                         \
    Fysh fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == S::SUBMARINE);                                               \
    CHECK(fysh.negate == n);                                                   \
  } while (0)

#define IDENT(x) IDENT_DIR(x, false)

#define INVALID(x)                                                             \
  do {                                                                         \
    Fysh fysh{lexer.nextFysh()};                                               \
    CHECK(fysh == (x));                                                        \
    CHECK(fysh == S::INVALID);                                                 \
  } while (0)

// https://stackoverflow.com/a/20986310
inline std::string join_chars(const std::initializer_list<const char *> &vs) {
  std::ostringstream result_stream;
  std::ostream_iterator<std::string> oit(result_stream, " ");
  std::copy(vs.begin(), vs.end(), oit);
  return result_stream.str();
}

#endif // !FYSH_TEST_UTIL_H_
