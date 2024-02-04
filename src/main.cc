#include "Lexer.h"

int main() {
  std::string_view input{"><{{({(o> <3 ><{{({(o>"};
  // Assuming `input` is a std::string or std::string_view
  fysh::FyshLexer lexer{input.data()};
  lexer.nextFysh();
  lexer.nextFysh();
  lexer.nextFysh();

  return 0;
}
