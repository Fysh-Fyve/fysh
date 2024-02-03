#include <string_view>
#include "Fysh.h"

// code is based off of this:
// https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

class FyshLexer {
public:
  // stream is the start of the input string
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}

  Fysh nextFysh() noexcept;

  private:
  Fysh identifier() noexcept;
  Fysh number() noexcept;
  Fysh scales() noexcept;
  Fysh slashOrComment() noexcept;
  Fysh atom(Species) noexcept;
  Fysh fyshOutline() noexcept;

  char peek() const noexcept { return *current; }
  char get() noexcept { return *current++; }

  const char* current = nullptr;
};