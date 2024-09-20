#include "tree_sitter/parser.h"

#include <wctype.h>

enum TokenType { MULTILINE_COMMENT };

#define F(x) tree_sitter_fysh_external_scanner_##x

// Not needed
void *F(create)() { return NULL; }
void F(destroy)(void *payload) {}
unsigned F(serialize)(void *payload, char *buffer) { return 0; }
void F(deserialize)(void *payload, const char *buffer, unsigned length) {}

static void advance(TSLexer *lexer) { lexer->advance(lexer, false); }
static void skip(TSLexer *lexer) { lexer->advance(lexer, true); }

static bool scan_multiline_comment(TSLexer *lexer) {
  while (iswspace(lexer->lookahead) || lexer->lookahead == 0x2028 ||
         lexer->lookahead == 0x2029) {
    skip(lexer);
  }
  const char *comment_start = "></*>";
  const char *comment_end = "<*/><";

  if (lexer->lookahead == '>') {
    for (unsigned i = 0; i < 5; i++) {
      if (lexer->lookahead != comment_start[i]) {
        return false;
      }
      advance(lexer);
    }
  }

  while (1) {
    while (lexer->lookahead != 0 && lexer->lookahead != '<') {
      advance(lexer);
    }

    if (lexer->lookahead == '<') {
      for (unsigned i = 0; i < 4; i++) {
        if (lexer->lookahead != comment_end[i]) {
          return false;
        }
        advance(lexer);
      }

      advance(lexer);

      lexer->result_symbol = MULTILINE_COMMENT;
      lexer->mark_end(lexer);

      return true;
    } else {
      return false;
    }
  }
}

bool F(scan)(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  if (valid_symbols[MULTILINE_COMMENT]) {
    return scan_multiline_comment(lexer);
  }

  return false;
}
