#include <string>

using namespace std;

// code is based off of this: https://gist.github.com/arrieta/1a309138689e09375b90b3b1aa768e20

enum class TokenType {
    FYSH_LITERAL,    // binary value
    FYSH_IDENTIFER,  // variable
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
    FYSH_CLOSE,      // <>< (same as closing curly bracket '{' )
    WTF_OPEN,        // WHAT THE FYSH (Throw error opening) ><!@#$>
    WTF_CLOSE,       // WHAT THE FYSH (Throw error closing) <!@#$><
    COMMENT,         // ><//> Comment 
    OPENING_COMMENT, // ></*> Comment
    CLOSING_COMMENT, // Comment <*/>< 

    //TODO bit manipulation
};

bool is_space(char c) noexcept {
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

class Token {
    public:

      // PLEASE DELETE THE EXPLINATION COMMENTS WHEN YOU NO LONGER NEED THEM

      // std::string_view https://www.educative.io/answers/what-is-the-cpp-string-view-in-cpp-17
      // std::size_t: https://stackoverflow.com/questions/502856/whats-the-difference-between-size-t-and-int-in-c
      // noexcept: supposed to be faster by saying this function does not throw exceptions
      // std::distance: returns the length when you give a pointer to the start and end of the char array
      // std::move: transfers ownership making the original owner lose its ownership

      // constructors
      /*
      original:
      Token (TokenType in_type) {
        this->type = in_type;
      }

      short version:
        Token (TokenType in_type): type(in_type) {}
      
      The last curly brackets are for the body but its empty
      */

      //-----------------Constructors---------------------

      // only the TokenType is given: useful for brackets and stuff since there is only one possible value
      Token(TokenType in_type) noexcept: tokenType{in_type} {}

      // TokenType, pointer to first element in char array and length of char array is given
      // stores the string_view of the element into value
      Token(TokenType in_type, const char* start, std::size_t len) noexcept: tokenType{in_type}, value(start, len) {}

      // TokenType, pointer to start of char array, pointer to end of char array. gets length and stores into string_view
      Token(TokenType in_type, const char* start, const char* end) noexcept: tokenType{in_type}, value(start, std::distance(start, end)) {}

      // -----------------------METHODS-----------------------
      TokenType get_type() {return tokenType;}
      void      set_type(TokenType in_type) noexcept {tokenType = in_type;}

      bool is_type (TokenType in_type) const noexcept {return tokenType == in_type;}
      bool not_type(TokenType in_type) const noexcept {return tokenType != in_type;}

      bool is_one_of(TokenType in_type1, TokenType in_type2) const noexcept { return is_type(in_type1) || is_type(in_type2); }

      //TODO add template (not sure what it does yet)

      std::string_view get_value() const noexcept {return value;}

      void set_value(std::string_view in_value) noexcept {
        value = std::move(in_value);
      }

      private:
      // curly bracker means initialize to default value (example: 0)
        TokenType tokenType {};
        std::string_view value {};
};


class FyshLexer {
    public:
    // tokenize everything (modularize it)

    private:
    // peak and consume
};