/*
Reference:
https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

Definitions for the Fysh class
Species: enum class for the different types of Fysh tokens 
body: string_view for each token (the actual value of the token)
Fysh: an object with a species and body
Stream: the input string
Current: the current position in the input string
*/

#include <ostream>
#include <string_view>

enum class Species {
  FYSH_SCALES,    // binary value
  FYSH_IDENTIFIER, // variable
  HEART_MULTIPLY,  // <3 or ♡
  DIVIDE,          // </3 or 💔
  TADPOLE_LT,      // ~o (less than    '<' )
  TADPOLE_GT,      // o~ (greater than '>' )
  TADPOLE_LTE,     // ~o≈ (less than equal to    '<=' )
  TADPOLE_GTE,     // o~≈ (greater than equal to '>=' )
  EQUAL,           // ≈≈  (Equal to '==')
  NOT_EQUAL,       // ~≈  (Not equal to '!=')
  INCREMENT,       // >><fysh> (add 1 'fysh++')
  DECREMENT,       // <fysh><< (sub 1 'fysh--')
  FYSH_TANK_OPEN,  // [ (same as open bracket  '('  )
  FYSH_TANK_CLOSE, // ] (same as closing bracket ')' )
  FYSH_OPEN,       // ><> (same as open curly bracket '{' )
  FYSH_CLOSE,      // <>< (same as closing curly bracket '}' )
  WTF_OPEN,        // WHAT THE FYSH (Throw error opening) ><!@#$>
  WTF_CLOSE,       // WHAT THE FYSH (Throw error closing) <!@#$><
  COMMENT,         // ><//> Comment
  OPENING_COMMENT, // ></*> Comment
  CLOSING_COMMENT, // Comment <*/><

  // TODO bit manipulation
};

class Fysh {
public:

  //-----------------Constructors---------------------
  
  Fysh(Species inType) noexcept : species{inType} {}

  Fysh(Species inType, const char *start, std::size_t len) noexcept
      : species{inType}, body(start, len) {}

  Fysh(Species inType, const char *start, const char *end) noexcept
      : species{inType}, body(start, std::distance(start, end)) {}

  // -----------------------METHODS-----------------------

  // check if the species is one of the given species (2 species)
  bool isOneOf(Species type1, Species type2) const noexcept;

  // check if the species is one of the given species (more than 2 species)
  template <typename... Ts>
  bool isOneOf(Species species1, Species species2, Ts... ks) const noexcept {
    return species == species1 || isOneOf(species2, ks...);
  }

  Species getSpecies() const noexcept;
  std::string_view getBody() const noexcept;


  // -----------------------OPERATORS-----------------------
  bool operator==(const Species &in_species) const noexcept {
    return species == in_species;
  }
  
  bool operator==(const Fysh &other) const noexcept {
    return other.species == species && other.body == body;
  }

private:
  Species species{};
  std::string_view body{};
};


class FyshLexer {
public:
  // stream is the start of the input string
  FyshLexer(const char *streamStart) noexcept : current{streamStart} {}

  Fysh nextFysh() noexcept;

  private:
  Fysh identifier() noexcept;
  Fysh number() noexcept;
  Fysh scales() noexcept;
  Fysh slash_or_comment() noexcept;
  Fysh atom(Species) noexcept;

  char peek() const noexcept { return *current; }
  char get() noexcept { return *current++; }

  const char* current = nullptr;
};

bool isSpace(char c) noexcept {
  switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
      return true;
    default:
      return false;
  }
}

bool isScale(char c) noexcept { 
  switch (c) {
    case '(':
    case ')':
    case '{':
    case '}':
      return true;
    default:
      return false;
  }
} 


Fysh FyshLexer::scales() noexcept {
  const char *start = current;
  get();
  while (isScale(peek())) get();
  if (peek() == 'o'){
    get();
    if (peek() == '>'){
      // positive
    } else {
      // error
    }
  }
  else if (peek() == '>'){
    // negative
  }
  else {
    // error
  }
  return Fysh(Species::FYSH_SCALES, start, current);
}
/*
Token Lexer::number() noexcept {
  const char* start = m_beg;
  get();
  while (is_digit(peek())) get();
  return Token(Token::Kind::Number, start, m_beg);
}*/








// string representation of token type (for testing)
std::ostream &operator<<(std::ostream &os, const Fysh &body);
