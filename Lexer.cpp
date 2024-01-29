#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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
    FYSH_TANK_LEFT,  // [ (same as left bracket  '('  )
    FYSH_TANK_RIGHT, // ] (same as right bracker ')' )
    FYSH_LEFT,       // ><> (same as right curly bracket '{' )
    FYSH_RIGHT,      // <>< (same as left  curly bracket '{' )

    //TODO bit manipulation
};

struct {
    TokenType type;
    string value;
} Token;


class FyshLexer {
    public:

    private:
};
