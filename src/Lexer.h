#include <string_view>

#include "Fysh.h"

// code is based off of this:
// https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

class FyshLexer {
public:
  // Fyshize everything (modularize it)
  FyshLexer(std::string_view s) : source(s){};
  Fysh nextFysh();

private:
  std::string_view source;
  // peak and consume
};
