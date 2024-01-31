#include <string>

using namespace std;

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

struct {
    TokenType type;
    string value;
} Token;


class FyshLexer {
    public:
    // tokenize everything (modularize it)

    private:
    // peak and consume
};