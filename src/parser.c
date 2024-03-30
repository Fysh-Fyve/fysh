#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 157
#define LARGE_STATE_COUNT 37
#define SYMBOL_COUNT 139
#define ALIAS_COUNT 0
#define TOKEN_COUNT 94
#define EXTERNAL_TOKEN_COUNT 1
#define FIELD_COUNT 13
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 17

enum ts_symbol_identifiers {
  sym__name = 1,
  anon_sym_GT_LPAREN = 2,
  anon_sym_RPAREN = 3,
  anon_sym_LPAREN = 4,
  anon_sym_RPAREN_LT = 5,
  anon_sym_TILDE = 6,
  anon_sym_LT_TILDE = 7,
  anon_sym_U0001f991 = 8,
  anon_sym_GT_LT_BSLASH_SLASH_GT = 9,
  anon_sym_LT_BSLASH_SLASH_GT_LT = 10,
  anon_sym_GT_LT_GT = 11,
  anon_sym_LT_GT_LT = 12,
  anon_sym_LPAREN_PLUSo = 13,
  anon_sym_o_PLUS_RPAREN = 14,
  anon_sym_GT_LT = 15,
  anon_sym_LPAREN_LPAREN_LPAREN = 16,
  anon_sym_AT = 17,
  anon_sym_GT = 18,
  anon_sym_CARET = 19,
  anon_sym_STAR = 20,
  anon_sym_POUND_POUND_POUND = 21,
  anon_sym_LT = 22,
  anon_sym_u2248 = 23,
  anon_sym_EQ = 24,
  anon_sym_LBRACK = 25,
  anon_sym_DASH = 26,
  anon_sym_RBRACK = 27,
  aux_sym_positive_scales_token1 = 28,
  sym_one = 29,
  sym_zero = 30,
  anon_sym_LT_LT = 31,
  anon_sym_GT_GT = 32,
  anon_sym_AMP = 33,
  anon_sym_LT3 = 34,
  anon_sym_u2661 = 35,
  anon_sym_LT_SLASH3 = 36,
  anon_sym_U0001f494 = 37,
  anon_sym_u2764ufe0fu200dU0001fa79 = 38,
  anon_sym_u2619 = 39,
  anon_sym_u2665 = 40,
  anon_sym_u2763 = 41,
  anon_sym_u2764 = 42,
  anon_sym_u2765 = 43,
  anon_sym_u2766 = 44,
  anon_sym_u2767 = 45,
  anon_sym_U0001f394 = 46,
  anon_sym_U0001fac0 = 47,
  anon_sym_U0001f5a4 = 48,
  anon_sym_U0001f499 = 49,
  anon_sym_U0001fa77 = 50,
  anon_sym_U0001fa75 = 51,
  anon_sym_U0001f49a = 52,
  anon_sym_U0001f49b = 53,
  anon_sym_U0001f49c = 54,
  anon_sym_U0001f9e1 = 55,
  anon_sym_U0001f90d = 56,
  anon_sym_U0001f90e = 57,
  anon_sym_U0001fa76 = 58,
  anon_sym_u2764ufe0f = 59,
  anon_sym_U0001f493 = 60,
  anon_sym_U0001f495 = 61,
  anon_sym_U0001f496 = 62,
  anon_sym_U0001f497 = 63,
  anon_sym_U0001f498 = 64,
  anon_sym_U0001f49d = 65,
  anon_sym_u2763ufe0f = 66,
  anon_sym_U0001f48c = 67,
  anon_sym_U0001f49e = 68,
  anon_sym_U0001f49f = 69,
  anon_sym_U0001faf6 = 70,
  anon_sym_U0001faf6U0001f3fb = 71,
  anon_sym_U0001faf6U0001f3fc = 72,
  anon_sym_U0001faf6U0001f3fd = 73,
  anon_sym_U0001faf6U0001f3fe = 74,
  anon_sym_U0001faf6U0001f3ff = 75,
  anon_sym_U0001f3e9 = 76,
  anon_sym_PIPE = 77,
  anon_sym_EQ_EQ = 78,
  anon_sym_u2248u2248 = 79,
  anon_sym_TILDE_EQ = 80,
  anon_sym_TILDEu2248 = 81,
  anon_sym_o_TILDE = 82,
  anon_sym_TILDEo = 83,
  anon_sym_o_TILDE_EQ = 84,
  anon_sym_o_TILDEu2248 = 85,
  anon_sym_TILDEo_EQ = 86,
  anon_sym_TILDEou2248 = 87,
  anon_sym_ou2248 = 88,
  anon_sym_u2248o = 89,
  anon_sym_o_EQ = 90,
  anon_sym_EQo = 91,
  sym_comment = 92,
  sym_multiline_comment = 93,
  sym_source_file = 94,
  sym_subroutine = 95,
  sym_right_sub = 96,
  sym_left_sub = 97,
  sym__statement = 98,
  sym__simple_statement = 99,
  sym__statement_list = 100,
  sym_return_statement = 101,
  sym_break_statement = 102,
  sym_block = 103,
  sym_anchor_statement = 104,
  sym_loopy_fysh = 105,
  sym_happy_fysh = 106,
  sym_dead_fysh = 107,
  sym_grilled_fysh = 108,
  sym_loop_statement = 109,
  sym_if_statement = 110,
  sym_expression_statement = 111,
  sym_inc_statement = 112,
  sym_dec_statement = 113,
  sym_assignment_statement = 114,
  sym__expression = 115,
  sym_aquarium = 116,
  sym_fysh_tank = 117,
  sym_fysh_bowl = 118,
  sym_positive_ident = 119,
  sym_positive_scales = 120,
  sym_positive_bones = 121,
  sym_negative_ident = 122,
  sym_negative_scales = 123,
  sym_negative_bones = 124,
  sym__scales = 125,
  sym__bones = 126,
  sym_spine = 127,
  sym_binary_expression = 128,
  sym_call_expression = 129,
  sym_addition = 130,
  aux_sym_source_file_repeat1 = 131,
  aux_sym_subroutine_repeat1 = 132,
  aux_sym__statement_list_repeat1 = 133,
  aux_sym_aquarium_repeat1 = 134,
  aux_sym_positive_scales_repeat1 = 135,
  aux_sym__scales_repeat1 = 136,
  aux_sym__bones_repeat1 = 137,
  aux_sym_call_expression_repeat1 = 138,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym__name] = "_name",
  [anon_sym_GT_LPAREN] = ">(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN_LT] = ")<",
  [anon_sym_TILDE] = "~",
  [anon_sym_LT_TILDE] = "<~",
  [anon_sym_U0001f991] = "\U0001f991",
  [anon_sym_GT_LT_BSLASH_SLASH_GT] = "><\\/>",
  [anon_sym_LT_BSLASH_SLASH_GT_LT] = "<\\/><",
  [anon_sym_GT_LT_GT] = "><>",
  [anon_sym_LT_GT_LT] = "<><",
  [anon_sym_LPAREN_PLUSo] = "(+o",
  [anon_sym_o_PLUS_RPAREN] = "o+)",
  [anon_sym_GT_LT] = "><",
  [anon_sym_LPAREN_LPAREN_LPAREN] = "(((",
  [anon_sym_AT] = "@",
  [anon_sym_GT] = ">",
  [anon_sym_CARET] = "^",
  [anon_sym_STAR] = "*",
  [anon_sym_POUND_POUND_POUND] = "###",
  [anon_sym_LT] = "<",
  [anon_sym_u2248] = "\u2248",
  [anon_sym_EQ] = "=",
  [anon_sym_LBRACK] = "[",
  [anon_sym_DASH] = "-",
  [anon_sym_RBRACK] = "]",
  [aux_sym_positive_scales_token1] = "positive_scales_token1",
  [sym_one] = "one",
  [sym_zero] = "zero",
  [anon_sym_LT_LT] = "<<",
  [anon_sym_GT_GT] = ">>",
  [anon_sym_AMP] = "&",
  [anon_sym_LT3] = "<3",
  [anon_sym_u2661] = "\u2661",
  [anon_sym_LT_SLASH3] = "</3",
  [anon_sym_U0001f494] = "\U0001f494",
  [anon_sym_u2764ufe0fu200dU0001fa79] = "\u2764\ufe0f\u200d\U0001fa79",
  [anon_sym_u2619] = "\u2619",
  [anon_sym_u2665] = "\u2665",
  [anon_sym_u2763] = "\u2763",
  [anon_sym_u2764] = "\u2764",
  [anon_sym_u2765] = "\u2765",
  [anon_sym_u2766] = "\u2766",
  [anon_sym_u2767] = "\u2767",
  [anon_sym_U0001f394] = "\U0001f394",
  [anon_sym_U0001fac0] = "\U0001fac0",
  [anon_sym_U0001f5a4] = "\U0001f5a4",
  [anon_sym_U0001f499] = "\U0001f499",
  [anon_sym_U0001fa77] = "\U0001fa77",
  [anon_sym_U0001fa75] = "\U0001fa75",
  [anon_sym_U0001f49a] = "\U0001f49a",
  [anon_sym_U0001f49b] = "\U0001f49b",
  [anon_sym_U0001f49c] = "\U0001f49c",
  [anon_sym_U0001f9e1] = "\U0001f9e1",
  [anon_sym_U0001f90d] = "\U0001f90d",
  [anon_sym_U0001f90e] = "\U0001f90e",
  [anon_sym_U0001fa76] = "\U0001fa76",
  [anon_sym_u2764ufe0f] = "\u2764\ufe0f",
  [anon_sym_U0001f493] = "\U0001f493",
  [anon_sym_U0001f495] = "\U0001f495",
  [anon_sym_U0001f496] = "\U0001f496",
  [anon_sym_U0001f497] = "\U0001f497",
  [anon_sym_U0001f498] = "\U0001f498",
  [anon_sym_U0001f49d] = "\U0001f49d",
  [anon_sym_u2763ufe0f] = "\u2763\ufe0f",
  [anon_sym_U0001f48c] = "\U0001f48c",
  [anon_sym_U0001f49e] = "\U0001f49e",
  [anon_sym_U0001f49f] = "\U0001f49f",
  [anon_sym_U0001faf6] = "\U0001faf6",
  [anon_sym_U0001faf6U0001f3fb] = "\U0001faf6\U0001f3fb",
  [anon_sym_U0001faf6U0001f3fc] = "\U0001faf6\U0001f3fc",
  [anon_sym_U0001faf6U0001f3fd] = "\U0001faf6\U0001f3fd",
  [anon_sym_U0001faf6U0001f3fe] = "\U0001faf6\U0001f3fe",
  [anon_sym_U0001faf6U0001f3ff] = "\U0001faf6\U0001f3ff",
  [anon_sym_U0001f3e9] = "\U0001f3e9",
  [anon_sym_PIPE] = "|",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_u2248u2248] = "\u2248\u2248",
  [anon_sym_TILDE_EQ] = "~=",
  [anon_sym_TILDEu2248] = "~\u2248",
  [anon_sym_o_TILDE] = "o~",
  [anon_sym_TILDEo] = "~o",
  [anon_sym_o_TILDE_EQ] = "o~=",
  [anon_sym_o_TILDEu2248] = "o~\u2248",
  [anon_sym_TILDEo_EQ] = "~o=",
  [anon_sym_TILDEou2248] = "~o\u2248",
  [anon_sym_ou2248] = "o\u2248",
  [anon_sym_u2248o] = "\u2248o",
  [anon_sym_o_EQ] = "o=",
  [anon_sym_EQo] = "=o",
  [sym_comment] = "comment",
  [sym_multiline_comment] = "multiline_comment",
  [sym_source_file] = "source_file",
  [sym_subroutine] = "subroutine",
  [sym_right_sub] = "right_sub",
  [sym_left_sub] = "left_sub",
  [sym__statement] = "_statement",
  [sym__simple_statement] = "_simple_statement",
  [sym__statement_list] = "_statement_list",
  [sym_return_statement] = "return_statement",
  [sym_break_statement] = "break_statement",
  [sym_block] = "block",
  [sym_anchor_statement] = "anchor_statement",
  [sym_loopy_fysh] = "loopy_fysh",
  [sym_happy_fysh] = "happy_fysh",
  [sym_dead_fysh] = "dead_fysh",
  [sym_grilled_fysh] = "grilled_fysh",
  [sym_loop_statement] = "loop_statement",
  [sym_if_statement] = "if_statement",
  [sym_expression_statement] = "expression_statement",
  [sym_inc_statement] = "inc_statement",
  [sym_dec_statement] = "dec_statement",
  [sym_assignment_statement] = "assignment_statement",
  [sym__expression] = "_expression",
  [sym_aquarium] = "aquarium",
  [sym_fysh_tank] = "fysh_tank",
  [sym_fysh_bowl] = "fysh_bowl",
  [sym_positive_ident] = "positive_ident",
  [sym_positive_scales] = "positive_scales",
  [sym_positive_bones] = "positive_bones",
  [sym_negative_ident] = "negative_ident",
  [sym_negative_scales] = "negative_scales",
  [sym_negative_bones] = "negative_bones",
  [sym__scales] = "_scales",
  [sym__bones] = "_bones",
  [sym_spine] = "spine",
  [sym_binary_expression] = "binary_expression",
  [sym_call_expression] = "call_expression",
  [sym_addition] = "addition",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_subroutine_repeat1] = "subroutine_repeat1",
  [aux_sym__statement_list_repeat1] = "_statement_list_repeat1",
  [aux_sym_aquarium_repeat1] = "aquarium_repeat1",
  [aux_sym_positive_scales_repeat1] = "positive_scales_repeat1",
  [aux_sym__scales_repeat1] = "_scales_repeat1",
  [aux_sym__bones_repeat1] = "_bones_repeat1",
  [aux_sym_call_expression_repeat1] = "call_expression_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym__name] = sym__name,
  [anon_sym_GT_LPAREN] = anon_sym_GT_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN_LT] = anon_sym_RPAREN_LT,
  [anon_sym_TILDE] = anon_sym_TILDE,
  [anon_sym_LT_TILDE] = anon_sym_LT_TILDE,
  [anon_sym_U0001f991] = anon_sym_U0001f991,
  [anon_sym_GT_LT_BSLASH_SLASH_GT] = anon_sym_GT_LT_BSLASH_SLASH_GT,
  [anon_sym_LT_BSLASH_SLASH_GT_LT] = anon_sym_LT_BSLASH_SLASH_GT_LT,
  [anon_sym_GT_LT_GT] = anon_sym_GT_LT_GT,
  [anon_sym_LT_GT_LT] = anon_sym_LT_GT_LT,
  [anon_sym_LPAREN_PLUSo] = anon_sym_LPAREN_PLUSo,
  [anon_sym_o_PLUS_RPAREN] = anon_sym_o_PLUS_RPAREN,
  [anon_sym_GT_LT] = anon_sym_GT_LT,
  [anon_sym_LPAREN_LPAREN_LPAREN] = anon_sym_LPAREN_LPAREN_LPAREN,
  [anon_sym_AT] = anon_sym_AT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_CARET] = anon_sym_CARET,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_POUND_POUND_POUND] = anon_sym_POUND_POUND_POUND,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_u2248] = anon_sym_u2248,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [aux_sym_positive_scales_token1] = aux_sym_positive_scales_token1,
  [sym_one] = sym_one,
  [sym_zero] = sym_zero,
  [anon_sym_LT_LT] = anon_sym_LT_LT,
  [anon_sym_GT_GT] = anon_sym_GT_GT,
  [anon_sym_AMP] = anon_sym_AMP,
  [anon_sym_LT3] = anon_sym_LT3,
  [anon_sym_u2661] = anon_sym_u2661,
  [anon_sym_LT_SLASH3] = anon_sym_LT_SLASH3,
  [anon_sym_U0001f494] = anon_sym_U0001f494,
  [anon_sym_u2764ufe0fu200dU0001fa79] = anon_sym_u2764ufe0fu200dU0001fa79,
  [anon_sym_u2619] = anon_sym_u2619,
  [anon_sym_u2665] = anon_sym_u2665,
  [anon_sym_u2763] = anon_sym_u2763,
  [anon_sym_u2764] = anon_sym_u2764,
  [anon_sym_u2765] = anon_sym_u2765,
  [anon_sym_u2766] = anon_sym_u2766,
  [anon_sym_u2767] = anon_sym_u2767,
  [anon_sym_U0001f394] = anon_sym_U0001f394,
  [anon_sym_U0001fac0] = anon_sym_U0001fac0,
  [anon_sym_U0001f5a4] = anon_sym_U0001f5a4,
  [anon_sym_U0001f499] = anon_sym_U0001f499,
  [anon_sym_U0001fa77] = anon_sym_U0001fa77,
  [anon_sym_U0001fa75] = anon_sym_U0001fa75,
  [anon_sym_U0001f49a] = anon_sym_U0001f49a,
  [anon_sym_U0001f49b] = anon_sym_U0001f49b,
  [anon_sym_U0001f49c] = anon_sym_U0001f49c,
  [anon_sym_U0001f9e1] = anon_sym_U0001f9e1,
  [anon_sym_U0001f90d] = anon_sym_U0001f90d,
  [anon_sym_U0001f90e] = anon_sym_U0001f90e,
  [anon_sym_U0001fa76] = anon_sym_U0001fa76,
  [anon_sym_u2764ufe0f] = anon_sym_u2764ufe0f,
  [anon_sym_U0001f493] = anon_sym_U0001f493,
  [anon_sym_U0001f495] = anon_sym_U0001f495,
  [anon_sym_U0001f496] = anon_sym_U0001f496,
  [anon_sym_U0001f497] = anon_sym_U0001f497,
  [anon_sym_U0001f498] = anon_sym_U0001f498,
  [anon_sym_U0001f49d] = anon_sym_U0001f49d,
  [anon_sym_u2763ufe0f] = anon_sym_u2763ufe0f,
  [anon_sym_U0001f48c] = anon_sym_U0001f48c,
  [anon_sym_U0001f49e] = anon_sym_U0001f49e,
  [anon_sym_U0001f49f] = anon_sym_U0001f49f,
  [anon_sym_U0001faf6] = anon_sym_U0001faf6,
  [anon_sym_U0001faf6U0001f3fb] = anon_sym_U0001faf6U0001f3fb,
  [anon_sym_U0001faf6U0001f3fc] = anon_sym_U0001faf6U0001f3fc,
  [anon_sym_U0001faf6U0001f3fd] = anon_sym_U0001faf6U0001f3fd,
  [anon_sym_U0001faf6U0001f3fe] = anon_sym_U0001faf6U0001f3fe,
  [anon_sym_U0001faf6U0001f3ff] = anon_sym_U0001faf6U0001f3ff,
  [anon_sym_U0001f3e9] = anon_sym_U0001f3e9,
  [anon_sym_PIPE] = anon_sym_PIPE,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_u2248u2248] = anon_sym_u2248u2248,
  [anon_sym_TILDE_EQ] = anon_sym_TILDE_EQ,
  [anon_sym_TILDEu2248] = anon_sym_TILDEu2248,
  [anon_sym_o_TILDE] = anon_sym_o_TILDE,
  [anon_sym_TILDEo] = anon_sym_TILDEo,
  [anon_sym_o_TILDE_EQ] = anon_sym_o_TILDE_EQ,
  [anon_sym_o_TILDEu2248] = anon_sym_o_TILDEu2248,
  [anon_sym_TILDEo_EQ] = anon_sym_TILDEo_EQ,
  [anon_sym_TILDEou2248] = anon_sym_TILDEou2248,
  [anon_sym_ou2248] = anon_sym_ou2248,
  [anon_sym_u2248o] = anon_sym_u2248o,
  [anon_sym_o_EQ] = anon_sym_o_EQ,
  [anon_sym_EQo] = anon_sym_EQo,
  [sym_comment] = sym_comment,
  [sym_multiline_comment] = sym_multiline_comment,
  [sym_source_file] = sym_source_file,
  [sym_subroutine] = sym_subroutine,
  [sym_right_sub] = sym_right_sub,
  [sym_left_sub] = sym_left_sub,
  [sym__statement] = sym__statement,
  [sym__simple_statement] = sym__simple_statement,
  [sym__statement_list] = sym__statement_list,
  [sym_return_statement] = sym_return_statement,
  [sym_break_statement] = sym_break_statement,
  [sym_block] = sym_block,
  [sym_anchor_statement] = sym_anchor_statement,
  [sym_loopy_fysh] = sym_loopy_fysh,
  [sym_happy_fysh] = sym_happy_fysh,
  [sym_dead_fysh] = sym_dead_fysh,
  [sym_grilled_fysh] = sym_grilled_fysh,
  [sym_loop_statement] = sym_loop_statement,
  [sym_if_statement] = sym_if_statement,
  [sym_expression_statement] = sym_expression_statement,
  [sym_inc_statement] = sym_inc_statement,
  [sym_dec_statement] = sym_dec_statement,
  [sym_assignment_statement] = sym_assignment_statement,
  [sym__expression] = sym__expression,
  [sym_aquarium] = sym_aquarium,
  [sym_fysh_tank] = sym_fysh_tank,
  [sym_fysh_bowl] = sym_fysh_bowl,
  [sym_positive_ident] = sym_positive_ident,
  [sym_positive_scales] = sym_positive_scales,
  [sym_positive_bones] = sym_positive_bones,
  [sym_negative_ident] = sym_negative_ident,
  [sym_negative_scales] = sym_negative_scales,
  [sym_negative_bones] = sym_negative_bones,
  [sym__scales] = sym__scales,
  [sym__bones] = sym__bones,
  [sym_spine] = sym_spine,
  [sym_binary_expression] = sym_binary_expression,
  [sym_call_expression] = sym_call_expression,
  [sym_addition] = sym_addition,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_subroutine_repeat1] = aux_sym_subroutine_repeat1,
  [aux_sym__statement_list_repeat1] = aux_sym__statement_list_repeat1,
  [aux_sym_aquarium_repeat1] = aux_sym_aquarium_repeat1,
  [aux_sym_positive_scales_repeat1] = aux_sym_positive_scales_repeat1,
  [aux_sym__scales_repeat1] = aux_sym__scales_repeat1,
  [aux_sym__bones_repeat1] = aux_sym__bones_repeat1,
  [aux_sym_call_expression_repeat1] = aux_sym_call_expression_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym__name] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_GT_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_TILDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f991] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_LT_BSLASH_SLASH_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_BSLASH_SLASH_GT_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_LT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_GT_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN_PLUSo] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_o_PLUS_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN_LPAREN_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_CARET] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_POUND_POUND_POUND] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2248] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_positive_scales_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_one] = {
    .visible = true,
    .named = true,
  },
  [sym_zero] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LT_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT3] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2661] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_SLASH3] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f494] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2764ufe0fu200dU0001fa79] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2619] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2665] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2763] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2764] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2765] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2766] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2767] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f394] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001fac0] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f5a4] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f499] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001fa77] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001fa75] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f49a] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f49b] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f49c] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f9e1] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f90d] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f90e] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001fa76] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2764ufe0f] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f493] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f495] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f496] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f497] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f498] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f49d] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2763ufe0f] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f48c] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f49e] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f49f] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001faf6] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001faf6U0001f3fb] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001faf6U0001f3fc] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001faf6U0001f3fd] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001faf6U0001f3fe] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001faf6U0001f3ff] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U0001f3e9] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2248u2248] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDE_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDEu2248] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_o_TILDE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDEo] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_o_TILDE_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_o_TILDEu2248] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDEo_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_TILDEou2248] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_ou2248] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u2248o] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_o_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQo] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_multiline_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_subroutine] = {
    .visible = true,
    .named = true,
  },
  [sym_right_sub] = {
    .visible = true,
    .named = true,
  },
  [sym_left_sub] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym__simple_statement] = {
    .visible = false,
    .named = true,
  },
  [sym__statement_list] = {
    .visible = false,
    .named = true,
  },
  [sym_return_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_break_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym_anchor_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_loopy_fysh] = {
    .visible = true,
    .named = true,
  },
  [sym_happy_fysh] = {
    .visible = true,
    .named = true,
  },
  [sym_dead_fysh] = {
    .visible = true,
    .named = true,
  },
  [sym_grilled_fysh] = {
    .visible = true,
    .named = true,
  },
  [sym_loop_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_if_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_expression_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_inc_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_dec_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_assignment_statement] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_aquarium] = {
    .visible = true,
    .named = true,
  },
  [sym_fysh_tank] = {
    .visible = true,
    .named = true,
  },
  [sym_fysh_bowl] = {
    .visible = true,
    .named = true,
  },
  [sym_positive_ident] = {
    .visible = true,
    .named = true,
  },
  [sym_positive_scales] = {
    .visible = true,
    .named = true,
  },
  [sym_positive_bones] = {
    .visible = true,
    .named = true,
  },
  [sym_negative_ident] = {
    .visible = true,
    .named = true,
  },
  [sym_negative_scales] = {
    .visible = true,
    .named = true,
  },
  [sym_negative_bones] = {
    .visible = true,
    .named = true,
  },
  [sym__scales] = {
    .visible = false,
    .named = true,
  },
  [sym__bones] = {
    .visible = false,
    .named = true,
  },
  [sym_spine] = {
    .visible = true,
    .named = true,
  },
  [sym_binary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_call_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_addition] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_subroutine_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__statement_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_aquarium_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_positive_scales_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__scales_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__bones_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_call_expression_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_body = 1,
  field_bones = 2,
  field_cond = 3,
  field_dir = 4,
  field_else = 5,
  field_left = 6,
  field_name = 7,
  field_operator = 8,
  field_params = 9,
  field_right = 10,
  field_scales = 11,
  field_then = 12,
  field_value = 13,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_bones] = "bones",
  [field_cond] = "cond",
  [field_dir] = "dir",
  [field_else] = "else",
  [field_left] = "left",
  [field_name] = "name",
  [field_operator] = "operator",
  [field_params] = "params",
  [field_right] = "right",
  [field_scales] = "scales",
  [field_then] = "then",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 1},
  [4] = {.index = 4, .length = 2},
  [5] = {.index = 6, .length = 1},
  [6] = {.index = 7, .length = 1},
  [7] = {.index = 8, .length = 1},
  [8] = {.index = 9, .length = 2},
  [9] = {.index = 11, .length = 2},
  [10] = {.index = 13, .length = 2},
  [11] = {.index = 15, .length = 3},
  [12] = {.index = 18, .length = 2},
  [13] = {.index = 20, .length = 1},
  [14] = {.index = 21, .length = 1},
  [15] = {.index = 22, .length = 1},
  [16] = {.index = 23, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_right, 1},
  [1] =
    {field_dir, 0},
    {field_value, 1},
  [3] =
    {field_body, 1},
  [4] =
    {field_left, 0},
    {field_right, 1},
  [6] =
    {field_name, 1},
  [7] =
    {field_scales, 1},
  [8] =
    {field_bones, 1},
  [9] =
    {field_body, 2},
    {field_params, 1},
  [11] =
    {field_body, 2},
    {field_cond, 1},
  [13] =
    {field_cond, 1},
    {field_then, 2},
  [15] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
  [18] =
    {field_left, 0},
    {field_right, 2},
  [20] =
    {field_name, 2},
  [21] =
    {field_scales, 2},
  [22] =
    {field_bones, 2},
  [23] =
    {field_cond, 1},
    {field_else, 4},
    {field_then, 2},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 40,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 62,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 67,
  [72] = 68,
  [73] = 63,
  [74] = 64,
  [75] = 65,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 76,
  [85] = 85,
  [86] = 80,
  [87] = 87,
  [88] = 88,
  [89] = 78,
  [90] = 90,
  [91] = 91,
  [92] = 90,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 85,
  [99] = 99,
  [100] = 83,
  [101] = 87,
  [102] = 94,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 111,
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 114,
  [116] = 112,
  [117] = 111,
  [118] = 113,
  [119] = 119,
  [120] = 16,
  [121] = 121,
  [122] = 95,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 146,
  [148] = 145,
  [149] = 144,
  [150] = 141,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 130,
  [155] = 155,
  [156] = 156,
};

static inline bool sym__name_character_set_1(int32_t c) {
  return (c < 43514
    ? (c < 4193
      ? (c < 2707
        ? (c < 1994
          ? (c < 910
            ? (c < 736
              ? (c < 186
                ? (c < 'a'
                  ? (c < '_'
                    ? (c >= 'A' && c <= 'Z')
                    : c <= '_')
                  : (c <= 'z' || (c < 181
                    ? c == 170
                    : c <= 181)))
                : (c <= 186 || (c < 248
                  ? (c < 216
                    ? (c >= 192 && c <= 214)
                    : c <= 246)
                  : (c <= 705 || (c >= 710 && c <= 721)))))
              : (c <= 740 || (c < 891
                ? (c < 880
                  ? (c < 750
                    ? c == 748
                    : c <= 750)
                  : (c <= 884 || (c >= 886 && c <= 887)))
                : (c <= 893 || (c < 904
                  ? (c < 902
                    ? c == 895
                    : c <= 902)
                  : (c <= 906 || c == 908))))))
            : (c <= 929 || (c < 1649
              ? (c < 1376
                ? (c < 1162
                  ? (c < 1015
                    ? (c >= 931 && c <= 1013)
                    : c <= 1153)
                  : (c <= 1327 || (c < 1369
                    ? (c >= 1329 && c <= 1366)
                    : c <= 1369)))
                : (c <= 1416 || (c < 1568
                  ? (c < 1519
                    ? (c >= 1488 && c <= 1514)
                    : c <= 1522)
                  : (c <= 1610 || (c >= 1646 && c <= 1647)))))
              : (c <= 1747 || (c < 1791
                ? (c < 1774
                  ? (c < 1765
                    ? c == 1749
                    : c <= 1766)
                  : (c <= 1775 || (c >= 1786 && c <= 1788)))
                : (c <= 1791 || (c < 1869
                  ? (c < 1810
                    ? c == 1808
                    : c <= 1839)
                  : (c <= 1957 || c == 1969))))))))
          : (c <= 2026 || (c < 2482
            ? (c < 2208
              ? (c < 2088
                ? (c < 2048
                  ? (c < 2042
                    ? (c >= 2036 && c <= 2037)
                    : c <= 2042)
                  : (c <= 2069 || (c < 2084
                    ? c == 2074
                    : c <= 2084)))
                : (c <= 2088 || (c < 2160
                  ? (c < 2144
                    ? (c >= 2112 && c <= 2136)
                    : c <= 2154)
                  : (c <= 2183 || (c >= 2185 && c <= 2190)))))
              : (c <= 2249 || (c < 2417
                ? (c < 2384
                  ? (c < 2365
                    ? (c >= 2308 && c <= 2361)
                    : c <= 2365)
                  : (c <= 2384 || (c >= 2392 && c <= 2401)))
                : (c <= 2432 || (c < 2451
                  ? (c < 2447
                    ? (c >= 2437 && c <= 2444)
                    : c <= 2448)
                  : (c <= 2472 || (c >= 2474 && c <= 2480)))))))
            : (c <= 2482 || (c < 2579
              ? (c < 2527
                ? (c < 2510
                  ? (c < 2493
                    ? (c >= 2486 && c <= 2489)
                    : c <= 2493)
                  : (c <= 2510 || (c >= 2524 && c <= 2525)))
                : (c <= 2529 || (c < 2565
                  ? (c < 2556
                    ? (c >= 2544 && c <= 2545)
                    : c <= 2556)
                  : (c <= 2570 || (c >= 2575 && c <= 2576)))))
              : (c <= 2600 || (c < 2649
                ? (c < 2613
                  ? (c < 2610
                    ? (c >= 2602 && c <= 2608)
                    : c <= 2611)
                  : (c <= 2614 || (c >= 2616 && c <= 2617)))
                : (c <= 2652 || (c < 2693
                  ? (c < 2674
                    ? c == 2654
                    : c <= 2676)
                  : (c <= 2701 || (c >= 2703 && c <= 2705)))))))))))
        : (c <= 2728 || (c < 3242
          ? (c < 2962
            ? (c < 2858
              ? (c < 2784
                ? (c < 2741
                  ? (c < 2738
                    ? (c >= 2730 && c <= 2736)
                    : c <= 2739)
                  : (c <= 2745 || (c < 2768
                    ? c == 2749
                    : c <= 2768)))
                : (c <= 2785 || (c < 2831
                  ? (c < 2821
                    ? c == 2809
                    : c <= 2828)
                  : (c <= 2832 || (c >= 2835 && c <= 2856)))))
              : (c <= 2864 || (c < 2911
                ? (c < 2877
                  ? (c < 2869
                    ? (c >= 2866 && c <= 2867)
                    : c <= 2873)
                  : (c <= 2877 || (c >= 2908 && c <= 2909)))
                : (c <= 2913 || (c < 2949
                  ? (c < 2947
                    ? c == 2929
                    : c <= 2947)
                  : (c <= 2954 || (c >= 2958 && c <= 2960)))))))
            : (c <= 2965 || (c < 3090
              ? (c < 2984
                ? (c < 2974
                  ? (c < 2972
                    ? (c >= 2969 && c <= 2970)
                    : c <= 2972)
                  : (c <= 2975 || (c >= 2979 && c <= 2980)))
                : (c <= 2986 || (c < 3077
                  ? (c < 3024
                    ? (c >= 2990 && c <= 3001)
                    : c <= 3024)
                  : (c <= 3084 || (c >= 3086 && c <= 3088)))))
              : (c <= 3112 || (c < 3168
                ? (c < 3160
                  ? (c < 3133
                    ? (c >= 3114 && c <= 3129)
                    : c <= 3133)
                  : (c <= 3162 || c == 3165))
                : (c <= 3169 || (c < 3214
                  ? (c < 3205
                    ? c == 3200
                    : c <= 3212)
                  : (c <= 3216 || (c >= 3218 && c <= 3240)))))))))
          : (c <= 3251 || (c < 3648
            ? (c < 3412
              ? (c < 3332
                ? (c < 3293
                  ? (c < 3261
                    ? (c >= 3253 && c <= 3257)
                    : c <= 3261)
                  : (c <= 3294 || (c < 3313
                    ? (c >= 3296 && c <= 3297)
                    : c <= 3314)))
                : (c <= 3340 || (c < 3389
                  ? (c < 3346
                    ? (c >= 3342 && c <= 3344)
                    : c <= 3386)
                  : (c <= 3389 || c == 3406))))
              : (c <= 3414 || (c < 3507
                ? (c < 3461
                  ? (c < 3450
                    ? (c >= 3423 && c <= 3425)
                    : c <= 3455)
                  : (c <= 3478 || (c >= 3482 && c <= 3505)))
                : (c <= 3515 || (c < 3585
                  ? (c < 3520
                    ? c == 3517
                    : c <= 3526)
                  : (c <= 3632 || c == 3634))))))
            : (c <= 3654 || (c < 3782
              ? (c < 3749
                ? (c < 3718
                  ? (c < 3716
                    ? (c >= 3713 && c <= 3714)
                    : c <= 3716)
                  : (c <= 3722 || (c >= 3724 && c <= 3747)))
                : (c <= 3749 || (c < 3773
                  ? (c < 3762
                    ? (c >= 3751 && c <= 3760)
                    : c <= 3762)
                  : (c <= 3773 || (c >= 3776 && c <= 3780)))))
              : (c <= 3782 || (c < 3976
                ? (c < 3904
                  ? (c < 3840
                    ? (c >= 3804 && c <= 3807)
                    : c <= 3840)
                  : (c <= 3911 || (c >= 3913 && c <= 3948)))
                : (c <= 3980 || (c < 4176
                  ? (c < 4159
                    ? (c >= 4096 && c <= 4138)
                    : c <= 4159)
                  : (c <= 4181 || (c >= 4186 && c <= 4189)))))))))))))
      : (c <= 4193 || (c < 8134
        ? (c < 6176
          ? (c < 4808
            ? (c < 4688
              ? (c < 4295
                ? (c < 4213
                  ? (c < 4206
                    ? (c >= 4197 && c <= 4198)
                    : c <= 4208)
                  : (c <= 4225 || (c < 4256
                    ? c == 4238
                    : c <= 4293)))
                : (c <= 4295 || (c < 4348
                  ? (c < 4304
                    ? c == 4301
                    : c <= 4346)
                  : (c <= 4680 || (c >= 4682 && c <= 4685)))))
              : (c <= 4694 || (c < 4752
                ? (c < 4704
                  ? (c < 4698
                    ? c == 4696
                    : c <= 4701)
                  : (c <= 4744 || (c >= 4746 && c <= 4749)))
                : (c <= 4784 || (c < 4800
                  ? (c < 4792
                    ? (c >= 4786 && c <= 4789)
                    : c <= 4798)
                  : (c <= 4800 || (c >= 4802 && c <= 4805)))))))
            : (c <= 4822 || (c < 5792
              ? (c < 5024
                ? (c < 4888
                  ? (c < 4882
                    ? (c >= 4824 && c <= 4880)
                    : c <= 4885)
                  : (c <= 4954 || (c >= 4992 && c <= 5007)))
                : (c <= 5109 || (c < 5743
                  ? (c < 5121
                    ? (c >= 5112 && c <= 5117)
                    : c <= 5740)
                  : (c <= 5759 || (c >= 5761 && c <= 5786)))))
              : (c <= 5866 || (c < 5984
                ? (c < 5919
                  ? (c < 5888
                    ? (c >= 5870 && c <= 5880)
                    : c <= 5905)
                  : (c <= 5937 || (c >= 5952 && c <= 5969)))
                : (c <= 5996 || (c < 6103
                  ? (c < 6016
                    ? (c >= 5998 && c <= 6000)
                    : c <= 6067)
                  : (c <= 6103 || c == 6108))))))))
          : (c <= 6264 || (c < 7312
            ? (c < 6823
              ? (c < 6512
                ? (c < 6320
                  ? (c < 6314
                    ? (c >= 6272 && c <= 6312)
                    : c <= 6314)
                  : (c <= 6389 || (c < 6480
                    ? (c >= 6400 && c <= 6430)
                    : c <= 6509)))
                : (c <= 6516 || (c < 6656
                  ? (c < 6576
                    ? (c >= 6528 && c <= 6571)
                    : c <= 6601)
                  : (c <= 6678 || (c >= 6688 && c <= 6740)))))
              : (c <= 6823 || (c < 7098
                ? (c < 7043
                  ? (c < 6981
                    ? (c >= 6917 && c <= 6963)
                    : c <= 6988)
                  : (c <= 7072 || (c >= 7086 && c <= 7087)))
                : (c <= 7141 || (c < 7258
                  ? (c < 7245
                    ? (c >= 7168 && c <= 7203)
                    : c <= 7247)
                  : (c <= 7293 || (c >= 7296 && c <= 7304)))))))
            : (c <= 7354 || (c < 8008
              ? (c < 7418
                ? (c < 7406
                  ? (c < 7401
                    ? (c >= 7357 && c <= 7359)
                    : c <= 7404)
                  : (c <= 7411 || (c >= 7413 && c <= 7414)))
                : (c <= 7418 || (c < 7960
                  ? (c < 7680
                    ? (c >= 7424 && c <= 7615)
                    : c <= 7957)
                  : (c <= 7965 || (c >= 7968 && c <= 8005)))))
              : (c <= 8013 || (c < 8031
                ? (c < 8027
                  ? (c < 8025
                    ? (c >= 8016 && c <= 8023)
                    : c <= 8025)
                  : (c <= 8027 || c == 8029))
                : (c <= 8061 || (c < 8126
                  ? (c < 8118
                    ? (c >= 8064 && c <= 8116)
                    : c <= 8124)
                  : (c <= 8126 || (c >= 8130 && c <= 8132)))))))))))
        : (c <= 8140 || (c < 12337
          ? (c < 8544
            ? (c < 8458
              ? (c < 8305
                ? (c < 8160
                  ? (c < 8150
                    ? (c >= 8144 && c <= 8147)
                    : c <= 8155)
                  : (c <= 8172 || (c < 8182
                    ? (c >= 8178 && c <= 8180)
                    : c <= 8188)))
                : (c <= 8305 || (c < 8450
                  ? (c < 8336
                    ? c == 8319
                    : c <= 8348)
                  : (c <= 8450 || c == 8455))))
              : (c <= 8467 || (c < 8488
                ? (c < 8484
                  ? (c < 8472
                    ? c == 8469
                    : c <= 8477)
                  : (c <= 8484 || c == 8486))
                : (c <= 8488 || (c < 8517
                  ? (c < 8508
                    ? (c >= 8490 && c <= 8505)
                    : c <= 8511)
                  : (c <= 8521 || c == 8526))))))
            : (c <= 8584 || (c < 11680
              ? (c < 11559
                ? (c < 11506
                  ? (c < 11499
                    ? (c >= 11264 && c <= 11492)
                    : c <= 11502)
                  : (c <= 11507 || (c >= 11520 && c <= 11557)))
                : (c <= 11559 || (c < 11631
                  ? (c < 11568
                    ? c == 11565
                    : c <= 11623)
                  : (c <= 11631 || (c >= 11648 && c <= 11670)))))
              : (c <= 11686 || (c < 11720
                ? (c < 11704
                  ? (c < 11696
                    ? (c >= 11688 && c <= 11694)
                    : c <= 11702)
                  : (c <= 11710 || (c >= 11712 && c <= 11718)))
                : (c <= 11726 || (c < 12293
                  ? (c < 11736
                    ? (c >= 11728 && c <= 11734)
                    : c <= 11742)
                  : (c <= 12295 || (c >= 12321 && c <= 12329)))))))))
          : (c <= 12341 || (c < 42891
            ? (c < 19968
              ? (c < 12549
                ? (c < 12445
                  ? (c < 12353
                    ? (c >= 12344 && c <= 12348)
                    : c <= 12438)
                  : (c <= 12447 || (c < 12540
                    ? (c >= 12449 && c <= 12538)
                    : c <= 12543)))
                : (c <= 12591 || (c < 12784
                  ? (c < 12704
                    ? (c >= 12593 && c <= 12686)
                    : c <= 12735)
                  : (c <= 12799 || (c >= 13312 && c <= 19903)))))
              : (c <= 42124 || (c < 42560
                ? (c < 42512
                  ? (c < 42240
                    ? (c >= 42192 && c <= 42237)
                    : c <= 42508)
                  : (c <= 42527 || (c >= 42538 && c <= 42539)))
                : (c <= 42606 || (c < 42775
                  ? (c < 42656
                    ? (c >= 42623 && c <= 42653)
                    : c <= 42735)
                  : (c <= 42783 || (c >= 42786 && c <= 42888)))))))
            : (c <= 42954 || (c < 43250
              ? (c < 43011
                ? (c < 42965
                  ? (c < 42963
                    ? (c >= 42960 && c <= 42961)
                    : c <= 42963)
                  : (c <= 42969 || (c >= 42994 && c <= 43009)))
                : (c <= 43013 || (c < 43072
                  ? (c < 43020
                    ? (c >= 43015 && c <= 43018)
                    : c <= 43042)
                  : (c <= 43123 || (c >= 43138 && c <= 43187)))))
              : (c <= 43255 || (c < 43360
                ? (c < 43274
                  ? (c < 43261
                    ? c == 43259
                    : c <= 43262)
                  : (c <= 43301 || (c >= 43312 && c <= 43334)))
                : (c <= 43388 || (c < 43488
                  ? (c < 43471
                    ? (c >= 43396 && c <= 43442)
                    : c <= 43471)
                  : (c <= 43492 || (c >= 43494 && c <= 43503)))))))))))))))
    : (c <= 43518 || (c < 70727
      ? (c < 66956
        ? (c < 64914
          ? (c < 43868
            ? (c < 43714
              ? (c < 43646
                ? (c < 43588
                  ? (c < 43584
                    ? (c >= 43520 && c <= 43560)
                    : c <= 43586)
                  : (c <= 43595 || (c < 43642
                    ? (c >= 43616 && c <= 43638)
                    : c <= 43642)))
                : (c <= 43695 || (c < 43705
                  ? (c < 43701
                    ? c == 43697
                    : c <= 43702)
                  : (c <= 43709 || c == 43712))))
              : (c <= 43714 || (c < 43785
                ? (c < 43762
                  ? (c < 43744
                    ? (c >= 43739 && c <= 43741)
                    : c <= 43754)
                  : (c <= 43764 || (c >= 43777 && c <= 43782)))
                : (c <= 43790 || (c < 43816
                  ? (c < 43808
                    ? (c >= 43793 && c <= 43798)
                    : c <= 43814)
                  : (c <= 43822 || (c >= 43824 && c <= 43866)))))))
            : (c <= 43881 || (c < 64287
              ? (c < 63744
                ? (c < 55216
                  ? (c < 44032
                    ? (c >= 43888 && c <= 44002)
                    : c <= 55203)
                  : (c <= 55238 || (c >= 55243 && c <= 55291)))
                : (c <= 64109 || (c < 64275
                  ? (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)
                  : (c <= 64279 || c == 64285))))
              : (c <= 64296 || (c < 64323
                ? (c < 64318
                  ? (c < 64312
                    ? (c >= 64298 && c <= 64310)
                    : c <= 64316)
                  : (c <= 64318 || (c >= 64320 && c <= 64321)))
                : (c <= 64324 || (c < 64612
                  ? (c < 64467
                    ? (c >= 64326 && c <= 64433)
                    : c <= 64605)
                  : (c <= 64829 || (c >= 64848 && c <= 64911)))))))))
          : (c <= 64967 || (c < 65599
            ? (c < 65382
              ? (c < 65147
                ? (c < 65139
                  ? (c < 65137
                    ? (c >= 65008 && c <= 65017)
                    : c <= 65137)
                  : (c <= 65139 || (c < 65145
                    ? c == 65143
                    : c <= 65145)))
                : (c <= 65147 || (c < 65313
                  ? (c < 65151
                    ? c == 65149
                    : c <= 65276)
                  : (c <= 65338 || (c >= 65345 && c <= 65370)))))
              : (c <= 65437 || (c < 65498
                ? (c < 65482
                  ? (c < 65474
                    ? (c >= 65440 && c <= 65470)
                    : c <= 65479)
                  : (c <= 65487 || (c >= 65490 && c <= 65495)))
                : (c <= 65500 || (c < 65576
                  ? (c < 65549
                    ? (c >= 65536 && c <= 65547)
                    : c <= 65574)
                  : (c <= 65594 || (c >= 65596 && c <= 65597)))))))
            : (c <= 65613 || (c < 66464
              ? (c < 66208
                ? (c < 65856
                  ? (c < 65664
                    ? (c >= 65616 && c <= 65629)
                    : c <= 65786)
                  : (c <= 65908 || (c >= 66176 && c <= 66204)))
                : (c <= 66256 || (c < 66384
                  ? (c < 66349
                    ? (c >= 66304 && c <= 66335)
                    : c <= 66378)
                  : (c <= 66421 || (c >= 66432 && c <= 66461)))))
              : (c <= 66499 || (c < 66776
                ? (c < 66560
                  ? (c < 66513
                    ? (c >= 66504 && c <= 66511)
                    : c <= 66517)
                  : (c <= 66717 || (c >= 66736 && c <= 66771)))
                : (c <= 66811 || (c < 66928
                  ? (c < 66864
                    ? (c >= 66816 && c <= 66855)
                    : c <= 66915)
                  : (c <= 66938 || (c >= 66940 && c <= 66954)))))))))))
        : (c <= 66962 || (c < 68864
          ? (c < 67828
            ? (c < 67506
              ? (c < 67072
                ? (c < 66979
                  ? (c < 66967
                    ? (c >= 66964 && c <= 66965)
                    : c <= 66977)
                  : (c <= 66993 || (c < 67003
                    ? (c >= 66995 && c <= 67001)
                    : c <= 67004)))
                : (c <= 67382 || (c < 67456
                  ? (c < 67424
                    ? (c >= 67392 && c <= 67413)
                    : c <= 67431)
                  : (c <= 67461 || (c >= 67463 && c <= 67504)))))
              : (c <= 67514 || (c < 67644
                ? (c < 67594
                  ? (c < 67592
                    ? (c >= 67584 && c <= 67589)
                    : c <= 67592)
                  : (c <= 67637 || (c >= 67639 && c <= 67640)))
                : (c <= 67644 || (c < 67712
                  ? (c < 67680
                    ? (c >= 67647 && c <= 67669)
                    : c <= 67702)
                  : (c <= 67742 || (c >= 67808 && c <= 67826)))))))
            : (c <= 67829 || (c < 68224
              ? (c < 68096
                ? (c < 67968
                  ? (c < 67872
                    ? (c >= 67840 && c <= 67861)
                    : c <= 67897)
                  : (c <= 68023 || (c >= 68030 && c <= 68031)))
                : (c <= 68096 || (c < 68121
                  ? (c < 68117
                    ? (c >= 68112 && c <= 68115)
                    : c <= 68119)
                  : (c <= 68149 || (c >= 68192 && c <= 68220)))))
              : (c <= 68252 || (c < 68448
                ? (c < 68352
                  ? (c < 68297
                    ? (c >= 68288 && c <= 68295)
                    : c <= 68324)
                  : (c <= 68405 || (c >= 68416 && c <= 68437)))
                : (c <= 68466 || (c < 68736
                  ? (c < 68608
                    ? (c >= 68480 && c <= 68497)
                    : c <= 68680)
                  : (c <= 68786 || (c >= 68800 && c <= 68850)))))))))
          : (c <= 68899 || (c < 70106
            ? (c < 69749
              ? (c < 69488
                ? (c < 69376
                  ? (c < 69296
                    ? (c >= 69248 && c <= 69289)
                    : c <= 69297)
                  : (c <= 69404 || (c < 69424
                    ? c == 69415
                    : c <= 69445)))
                : (c <= 69505 || (c < 69635
                  ? (c < 69600
                    ? (c >= 69552 && c <= 69572)
                    : c <= 69622)
                  : (c <= 69687 || (c >= 69745 && c <= 69746)))))
              : (c <= 69749 || (c < 69959
                ? (c < 69891
                  ? (c < 69840
                    ? (c >= 69763 && c <= 69807)
                    : c <= 69864)
                  : (c <= 69926 || c == 69956))
                : (c <= 69959 || (c < 70019
                  ? (c < 70006
                    ? (c >= 69968 && c <= 70002)
                    : c <= 70006)
                  : (c <= 70066 || (c >= 70081 && c <= 70084)))))))
            : (c <= 70106 || (c < 70405
              ? (c < 70280
                ? (c < 70163
                  ? (c < 70144
                    ? c == 70108
                    : c <= 70161)
                  : (c <= 70187 || (c >= 70272 && c <= 70278)))
                : (c <= 70280 || (c < 70303
                  ? (c < 70287
                    ? (c >= 70282 && c <= 70285)
                    : c <= 70301)
                  : (c <= 70312 || (c >= 70320 && c <= 70366)))))
              : (c <= 70412 || (c < 70453
                ? (c < 70442
                  ? (c < 70419
                    ? (c >= 70415 && c <= 70416)
                    : c <= 70440)
                  : (c <= 70448 || (c >= 70450 && c <= 70451)))
                : (c <= 70457 || (c < 70493
                  ? (c < 70480
                    ? c == 70461
                    : c <= 70480)
                  : (c <= 70497 || (c >= 70656 && c <= 70708)))))))))))))
      : (c <= 70730 || (c < 119894
        ? (c < 73056
          ? (c < 72001
            ? (c < 71424
              ? (c < 71128
                ? (c < 70852
                  ? (c < 70784
                    ? (c >= 70751 && c <= 70753)
                    : c <= 70831)
                  : (c <= 70853 || (c < 71040
                    ? c == 70855
                    : c <= 71086)))
                : (c <= 71131 || (c < 71296
                  ? (c < 71236
                    ? (c >= 71168 && c <= 71215)
                    : c <= 71236)
                  : (c <= 71338 || c == 71352))))
              : (c <= 71450 || (c < 71945
                ? (c < 71840
                  ? (c < 71680
                    ? (c >= 71488 && c <= 71494)
                    : c <= 71723)
                  : (c <= 71903 || (c >= 71935 && c <= 71942)))
                : (c <= 71945 || (c < 71960
                  ? (c < 71957
                    ? (c >= 71948 && c <= 71955)
                    : c <= 71958)
                  : (c <= 71983 || c == 71999))))))
            : (c <= 72001 || (c < 72349
              ? (c < 72192
                ? (c < 72161
                  ? (c < 72106
                    ? (c >= 72096 && c <= 72103)
                    : c <= 72144)
                  : (c <= 72161 || c == 72163))
                : (c <= 72192 || (c < 72272
                  ? (c < 72250
                    ? (c >= 72203 && c <= 72242)
                    : c <= 72250)
                  : (c <= 72272 || (c >= 72284 && c <= 72329)))))
              : (c <= 72349 || (c < 72818
                ? (c < 72714
                  ? (c < 72704
                    ? (c >= 72368 && c <= 72440)
                    : c <= 72712)
                  : (c <= 72750 || c == 72768))
                : (c <= 72847 || (c < 72971
                  ? (c < 72968
                    ? (c >= 72960 && c <= 72966)
                    : c <= 72969)
                  : (c <= 73008 || c == 73030))))))))
          : (c <= 73061 || (c < 93952
            ? (c < 82944
              ? (c < 73728
                ? (c < 73112
                  ? (c < 73066
                    ? (c >= 73063 && c <= 73064)
                    : c <= 73097)
                  : (c <= 73112 || (c < 73648
                    ? (c >= 73440 && c <= 73458)
                    : c <= 73648)))
                : (c <= 74649 || (c < 77712
                  ? (c < 74880
                    ? (c >= 74752 && c <= 74862)
                    : c <= 75075)
                  : (c <= 77808 || (c >= 77824 && c <= 78894)))))
              : (c <= 83526 || (c < 92928
                ? (c < 92784
                  ? (c < 92736
                    ? (c >= 92160 && c <= 92728)
                    : c <= 92766)
                  : (c <= 92862 || (c >= 92880 && c <= 92909)))
                : (c <= 92975 || (c < 93053
                  ? (c < 93027
                    ? (c >= 92992 && c <= 92995)
                    : c <= 93047)
                  : (c <= 93071 || (c >= 93760 && c <= 93823)))))))
            : (c <= 94026 || (c < 110589
              ? (c < 94208
                ? (c < 94176
                  ? (c < 94099
                    ? c == 94032
                    : c <= 94111)
                  : (c <= 94177 || c == 94179))
                : (c <= 100343 || (c < 110576
                  ? (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)
                  : (c <= 110579 || (c >= 110581 && c <= 110587)))))
              : (c <= 110590 || (c < 113664
                ? (c < 110948
                  ? (c < 110928
                    ? (c >= 110592 && c <= 110882)
                    : c <= 110930)
                  : (c <= 110951 || (c >= 110960 && c <= 111355)))
                : (c <= 113770 || (c < 113808
                  ? (c < 113792
                    ? (c >= 113776 && c <= 113788)
                    : c <= 113800)
                  : (c <= 113817 || (c >= 119808 && c <= 119892)))))))))))
        : (c <= 119964 || (c < 125259
          ? (c < 120572
            ? (c < 120086
              ? (c < 119995
                ? (c < 119973
                  ? (c < 119970
                    ? (c >= 119966 && c <= 119967)
                    : c <= 119970)
                  : (c <= 119974 || (c < 119982
                    ? (c >= 119977 && c <= 119980)
                    : c <= 119993)))
                : (c <= 119995 || (c < 120071
                  ? (c < 120005
                    ? (c >= 119997 && c <= 120003)
                    : c <= 120069)
                  : (c <= 120074 || (c >= 120077 && c <= 120084)))))
              : (c <= 120092 || (c < 120138
                ? (c < 120128
                  ? (c < 120123
                    ? (c >= 120094 && c <= 120121)
                    : c <= 120126)
                  : (c <= 120132 || c == 120134))
                : (c <= 120144 || (c < 120514
                  ? (c < 120488
                    ? (c >= 120146 && c <= 120485)
                    : c <= 120512)
                  : (c <= 120538 || (c >= 120540 && c <= 120570)))))))
            : (c <= 120596 || (c < 123191
              ? (c < 120714
                ? (c < 120656
                  ? (c < 120630
                    ? (c >= 120598 && c <= 120628)
                    : c <= 120654)
                  : (c <= 120686 || (c >= 120688 && c <= 120712)))
                : (c <= 120744 || (c < 122624
                  ? (c < 120772
                    ? (c >= 120746 && c <= 120770)
                    : c <= 120779)
                  : (c <= 122654 || (c >= 123136 && c <= 123180)))))
              : (c <= 123197 || (c < 124904
                ? (c < 123584
                  ? (c < 123536
                    ? c == 123214
                    : c <= 123565)
                  : (c <= 123627 || (c >= 124896 && c <= 124902)))
                : (c <= 124907 || (c < 124928
                  ? (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)
                  : (c <= 125124 || (c >= 125184 && c <= 125251)))))))))
          : (c <= 125259 || (c < 126559
            ? (c < 126535
              ? (c < 126505
                ? (c < 126497
                  ? (c < 126469
                    ? (c >= 126464 && c <= 126467)
                    : c <= 126495)
                  : (c <= 126498 || (c < 126503
                    ? c == 126500
                    : c <= 126503)))
                : (c <= 126514 || (c < 126523
                  ? (c < 126521
                    ? (c >= 126516 && c <= 126519)
                    : c <= 126521)
                  : (c <= 126523 || c == 126530))))
              : (c <= 126535 || (c < 126548
                ? (c < 126541
                  ? (c < 126539
                    ? c == 126537
                    : c <= 126539)
                  : (c <= 126543 || (c >= 126545 && c <= 126546)))
                : (c <= 126548 || (c < 126555
                  ? (c < 126553
                    ? c == 126551
                    : c <= 126553)
                  : (c <= 126555 || c == 126557))))))
            : (c <= 126559 || (c < 126625
              ? (c < 126580
                ? (c < 126567
                  ? (c < 126564
                    ? (c >= 126561 && c <= 126562)
                    : c <= 126564)
                  : (c <= 126570 || (c >= 126572 && c <= 126578)))
                : (c <= 126583 || (c < 126592
                  ? (c < 126590
                    ? (c >= 126585 && c <= 126588)
                    : c <= 126590)
                  : (c <= 126601 || (c >= 126603 && c <= 126619)))))
              : (c <= 126627 || (c < 177984
                ? (c < 131072
                  ? (c < 126635
                    ? (c >= 126629 && c <= 126633)
                    : c <= 126651)
                  : (c <= 173791 || (c >= 173824 && c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static inline bool sym__name_character_set_2(int32_t c) {
  return (c < 43616
    ? (c < 3782
      ? (c < 2748
        ? (c < 2045
          ? (c < 1015
            ? (c < 710
              ? (c < 181
                ? (c < '_'
                  ? (c < 'A'
                    ? (c >= '0' && c <= '9')
                    : c <= 'Z')
                  : (c <= '_' || (c < 170
                    ? (c >= 'a' && c <= 'z')
                    : c <= 170)))
                : (c <= 181 || (c < 192
                  ? (c < 186
                    ? c == 183
                    : c <= 186)
                  : (c <= 214 || (c < 248
                    ? (c >= 216 && c <= 246)
                    : c <= 705)))))
              : (c <= 721 || (c < 891
                ? (c < 750
                  ? (c < 748
                    ? (c >= 736 && c <= 740)
                    : c <= 748)
                  : (c <= 750 || (c < 886
                    ? (c >= 768 && c <= 884)
                    : c <= 887)))
                : (c <= 893 || (c < 908
                  ? (c < 902
                    ? c == 895
                    : c <= 906)
                  : (c <= 908 || (c < 931
                    ? (c >= 910 && c <= 929)
                    : c <= 1013)))))))
            : (c <= 1153 || (c < 1519
              ? (c < 1425
                ? (c < 1329
                  ? (c < 1162
                    ? (c >= 1155 && c <= 1159)
                    : c <= 1327)
                  : (c <= 1366 || (c < 1376
                    ? c == 1369
                    : c <= 1416)))
                : (c <= 1469 || (c < 1476
                  ? (c < 1473
                    ? c == 1471
                    : c <= 1474)
                  : (c <= 1477 || (c < 1488
                    ? c == 1479
                    : c <= 1514)))))
              : (c <= 1522 || (c < 1770
                ? (c < 1646
                  ? (c < 1568
                    ? (c >= 1552 && c <= 1562)
                    : c <= 1641)
                  : (c <= 1747 || (c < 1759
                    ? (c >= 1749 && c <= 1756)
                    : c <= 1768)))
                : (c <= 1788 || (c < 1869
                  ? (c < 1808
                    ? c == 1791
                    : c <= 1866)
                  : (c <= 1969 || (c < 2042
                    ? (c >= 1984 && c <= 2037)
                    : c <= 2042)))))))))
          : (c <= 2045 || (c < 2558
            ? (c < 2451
              ? (c < 2200
                ? (c < 2144
                  ? (c < 2112
                    ? (c >= 2048 && c <= 2093)
                    : c <= 2139)
                  : (c <= 2154 || (c < 2185
                    ? (c >= 2160 && c <= 2183)
                    : c <= 2190)))
                : (c <= 2273 || (c < 2417
                  ? (c < 2406
                    ? (c >= 2275 && c <= 2403)
                    : c <= 2415)
                  : (c <= 2435 || (c < 2447
                    ? (c >= 2437 && c <= 2444)
                    : c <= 2448)))))
              : (c <= 2472 || (c < 2507
                ? (c < 2486
                  ? (c < 2482
                    ? (c >= 2474 && c <= 2480)
                    : c <= 2482)
                  : (c <= 2489 || (c < 2503
                    ? (c >= 2492 && c <= 2500)
                    : c <= 2504)))
                : (c <= 2510 || (c < 2527
                  ? (c < 2524
                    ? c == 2519
                    : c <= 2525)
                  : (c <= 2531 || (c < 2556
                    ? (c >= 2534 && c <= 2545)
                    : c <= 2556)))))))
            : (c <= 2558 || (c < 2635
              ? (c < 2610
                ? (c < 2575
                  ? (c < 2565
                    ? (c >= 2561 && c <= 2563)
                    : c <= 2570)
                  : (c <= 2576 || (c < 2602
                    ? (c >= 2579 && c <= 2600)
                    : c <= 2608)))
                : (c <= 2611 || (c < 2620
                  ? (c < 2616
                    ? (c >= 2613 && c <= 2614)
                    : c <= 2617)
                  : (c <= 2620 || (c < 2631
                    ? (c >= 2622 && c <= 2626)
                    : c <= 2632)))))
              : (c <= 2637 || (c < 2693
                ? (c < 2654
                  ? (c < 2649
                    ? c == 2641
                    : c <= 2652)
                  : (c <= 2654 || (c < 2689
                    ? (c >= 2662 && c <= 2677)
                    : c <= 2691)))
                : (c <= 2701 || (c < 2730
                  ? (c < 2707
                    ? (c >= 2703 && c <= 2705)
                    : c <= 2728)
                  : (c <= 2736 || (c < 2741
                    ? (c >= 2738 && c <= 2739)
                    : c <= 2745)))))))))))
        : (c <= 2757 || (c < 3168
          ? (c < 2958
            ? (c < 2866
              ? (c < 2809
                ? (c < 2768
                  ? (c < 2763
                    ? (c >= 2759 && c <= 2761)
                    : c <= 2765)
                  : (c <= 2768 || (c < 2790
                    ? (c >= 2784 && c <= 2787)
                    : c <= 2799)))
                : (c <= 2815 || (c < 2831
                  ? (c < 2821
                    ? (c >= 2817 && c <= 2819)
                    : c <= 2828)
                  : (c <= 2832 || (c < 2858
                    ? (c >= 2835 && c <= 2856)
                    : c <= 2864)))))
              : (c <= 2867 || (c < 2908
                ? (c < 2887
                  ? (c < 2876
                    ? (c >= 2869 && c <= 2873)
                    : c <= 2884)
                  : (c <= 2888 || (c < 2901
                    ? (c >= 2891 && c <= 2893)
                    : c <= 2903)))
                : (c <= 2909 || (c < 2929
                  ? (c < 2918
                    ? (c >= 2911 && c <= 2915)
                    : c <= 2927)
                  : (c <= 2929 || (c < 2949
                    ? (c >= 2946 && c <= 2947)
                    : c <= 2954)))))))
            : (c <= 2960 || (c < 3031
              ? (c < 2984
                ? (c < 2972
                  ? (c < 2969
                    ? (c >= 2962 && c <= 2965)
                    : c <= 2970)
                  : (c <= 2972 || (c < 2979
                    ? (c >= 2974 && c <= 2975)
                    : c <= 2980)))
                : (c <= 2986 || (c < 3014
                  ? (c < 3006
                    ? (c >= 2990 && c <= 3001)
                    : c <= 3010)
                  : (c <= 3016 || (c < 3024
                    ? (c >= 3018 && c <= 3021)
                    : c <= 3024)))))
              : (c <= 3031 || (c < 3132
                ? (c < 3086
                  ? (c < 3072
                    ? (c >= 3046 && c <= 3055)
                    : c <= 3084)
                  : (c <= 3088 || (c < 3114
                    ? (c >= 3090 && c <= 3112)
                    : c <= 3129)))
                : (c <= 3140 || (c < 3157
                  ? (c < 3146
                    ? (c >= 3142 && c <= 3144)
                    : c <= 3149)
                  : (c <= 3158 || (c < 3165
                    ? (c >= 3160 && c <= 3162)
                    : c <= 3165)))))))))
          : (c <= 3171 || (c < 3450
            ? (c < 3293
              ? (c < 3242
                ? (c < 3205
                  ? (c < 3200
                    ? (c >= 3174 && c <= 3183)
                    : c <= 3203)
                  : (c <= 3212 || (c < 3218
                    ? (c >= 3214 && c <= 3216)
                    : c <= 3240)))
                : (c <= 3251 || (c < 3270
                  ? (c < 3260
                    ? (c >= 3253 && c <= 3257)
                    : c <= 3268)
                  : (c <= 3272 || (c < 3285
                    ? (c >= 3274 && c <= 3277)
                    : c <= 3286)))))
              : (c <= 3294 || (c < 3346
                ? (c < 3313
                  ? (c < 3302
                    ? (c >= 3296 && c <= 3299)
                    : c <= 3311)
                  : (c <= 3314 || (c < 3342
                    ? (c >= 3328 && c <= 3340)
                    : c <= 3344)))
                : (c <= 3396 || (c < 3412
                  ? (c < 3402
                    ? (c >= 3398 && c <= 3400)
                    : c <= 3406)
                  : (c <= 3415 || (c < 3430
                    ? (c >= 3423 && c <= 3427)
                    : c <= 3439)))))))
            : (c <= 3455 || (c < 3570
              ? (c < 3520
                ? (c < 3482
                  ? (c < 3461
                    ? (c >= 3457 && c <= 3459)
                    : c <= 3478)
                  : (c <= 3505 || (c < 3517
                    ? (c >= 3507 && c <= 3515)
                    : c <= 3517)))
                : (c <= 3526 || (c < 3542
                  ? (c < 3535
                    ? c == 3530
                    : c <= 3540)
                  : (c <= 3542 || (c < 3558
                    ? (c >= 3544 && c <= 3551)
                    : c <= 3567)))))
              : (c <= 3571 || (c < 3718
                ? (c < 3664
                  ? (c < 3648
                    ? (c >= 3585 && c <= 3642)
                    : c <= 3662)
                  : (c <= 3673 || (c < 3716
                    ? (c >= 3713 && c <= 3714)
                    : c <= 3716)))
                : (c <= 3722 || (c < 3751
                  ? (c < 3749
                    ? (c >= 3724 && c <= 3747)
                    : c <= 3749)
                  : (c <= 3773 || (c >= 3776 && c <= 3780)))))))))))))
      : (c <= 3782 || (c < 8025
        ? (c < 5888
          ? (c < 4688
            ? (c < 3953
              ? (c < 3872
                ? (c < 3804
                  ? (c < 3792
                    ? (c >= 3784 && c <= 3789)
                    : c <= 3801)
                  : (c <= 3807 || (c < 3864
                    ? c == 3840
                    : c <= 3865)))
                : (c <= 3881 || (c < 3897
                  ? (c < 3895
                    ? c == 3893
                    : c <= 3895)
                  : (c <= 3897 || (c < 3913
                    ? (c >= 3902 && c <= 3911)
                    : c <= 3948)))))
              : (c <= 3972 || (c < 4256
                ? (c < 4038
                  ? (c < 3993
                    ? (c >= 3974 && c <= 3991)
                    : c <= 4028)
                  : (c <= 4038 || (c < 4176
                    ? (c >= 4096 && c <= 4169)
                    : c <= 4253)))
                : (c <= 4293 || (c < 4304
                  ? (c < 4301
                    ? c == 4295
                    : c <= 4301)
                  : (c <= 4346 || (c < 4682
                    ? (c >= 4348 && c <= 4680)
                    : c <= 4685)))))))
            : (c <= 4694 || (c < 4882
              ? (c < 4786
                ? (c < 4704
                  ? (c < 4698
                    ? c == 4696
                    : c <= 4701)
                  : (c <= 4744 || (c < 4752
                    ? (c >= 4746 && c <= 4749)
                    : c <= 4784)))
                : (c <= 4789 || (c < 4802
                  ? (c < 4800
                    ? (c >= 4792 && c <= 4798)
                    : c <= 4800)
                  : (c <= 4805 || (c < 4824
                    ? (c >= 4808 && c <= 4822)
                    : c <= 4880)))))
              : (c <= 4885 || (c < 5112
                ? (c < 4969
                  ? (c < 4957
                    ? (c >= 4888 && c <= 4954)
                    : c <= 4959)
                  : (c <= 4977 || (c < 5024
                    ? (c >= 4992 && c <= 5007)
                    : c <= 5109)))
                : (c <= 5117 || (c < 5761
                  ? (c < 5743
                    ? (c >= 5121 && c <= 5740)
                    : c <= 5759)
                  : (c <= 5786 || (c < 5870
                    ? (c >= 5792 && c <= 5866)
                    : c <= 5880)))))))))
          : (c <= 5909 || (c < 6688
            ? (c < 6176
              ? (c < 6016
                ? (c < 5984
                  ? (c < 5952
                    ? (c >= 5919 && c <= 5940)
                    : c <= 5971)
                  : (c <= 5996 || (c < 6002
                    ? (c >= 5998 && c <= 6000)
                    : c <= 6003)))
                : (c <= 6099 || (c < 6112
                  ? (c < 6108
                    ? c == 6103
                    : c <= 6109)
                  : (c <= 6121 || (c < 6159
                    ? (c >= 6155 && c <= 6157)
                    : c <= 6169)))))
              : (c <= 6264 || (c < 6470
                ? (c < 6400
                  ? (c < 6320
                    ? (c >= 6272 && c <= 6314)
                    : c <= 6389)
                  : (c <= 6430 || (c < 6448
                    ? (c >= 6432 && c <= 6443)
                    : c <= 6459)))
                : (c <= 6509 || (c < 6576
                  ? (c < 6528
                    ? (c >= 6512 && c <= 6516)
                    : c <= 6571)
                  : (c <= 6601 || (c < 6656
                    ? (c >= 6608 && c <= 6618)
                    : c <= 6683)))))))
            : (c <= 6750 || (c < 7232
              ? (c < 6847
                ? (c < 6800
                  ? (c < 6783
                    ? (c >= 6752 && c <= 6780)
                    : c <= 6793)
                  : (c <= 6809 || (c < 6832
                    ? c == 6823
                    : c <= 6845)))
                : (c <= 6862 || (c < 7019
                  ? (c < 6992
                    ? (c >= 6912 && c <= 6988)
                    : c <= 7001)
                  : (c <= 7027 || (c < 7168
                    ? (c >= 7040 && c <= 7155)
                    : c <= 7223)))))
              : (c <= 7241 || (c < 7380
                ? (c < 7312
                  ? (c < 7296
                    ? (c >= 7245 && c <= 7293)
                    : c <= 7304)
                  : (c <= 7354 || (c < 7376
                    ? (c >= 7357 && c <= 7359)
                    : c <= 7378)))
                : (c <= 7418 || (c < 7968
                  ? (c < 7960
                    ? (c >= 7424 && c <= 7957)
                    : c <= 7965)
                  : (c <= 8005 || (c < 8016
                    ? (c >= 8008 && c <= 8013)
                    : c <= 8023)))))))))))
        : (c <= 8025 || (c < 11720
          ? (c < 8458
            ? (c < 8178
              ? (c < 8126
                ? (c < 8031
                  ? (c < 8029
                    ? c == 8027
                    : c <= 8029)
                  : (c <= 8061 || (c < 8118
                    ? (c >= 8064 && c <= 8116)
                    : c <= 8124)))
                : (c <= 8126 || (c < 8144
                  ? (c < 8134
                    ? (c >= 8130 && c <= 8132)
                    : c <= 8140)
                  : (c <= 8147 || (c < 8160
                    ? (c >= 8150 && c <= 8155)
                    : c <= 8172)))))
              : (c <= 8180 || (c < 8336
                ? (c < 8276
                  ? (c < 8255
                    ? (c >= 8182 && c <= 8188)
                    : c <= 8256)
                  : (c <= 8276 || (c < 8319
                    ? c == 8305
                    : c <= 8319)))
                : (c <= 8348 || (c < 8421
                  ? (c < 8417
                    ? (c >= 8400 && c <= 8412)
                    : c <= 8417)
                  : (c <= 8432 || (c < 8455
                    ? c == 8450
                    : c <= 8455)))))))
            : (c <= 8467 || (c < 11499
              ? (c < 8490
                ? (c < 8484
                  ? (c < 8472
                    ? c == 8469
                    : c <= 8477)
                  : (c <= 8484 || (c < 8488
                    ? c == 8486
                    : c <= 8488)))
                : (c <= 8505 || (c < 8526
                  ? (c < 8517
                    ? (c >= 8508 && c <= 8511)
                    : c <= 8521)
                  : (c <= 8526 || (c < 11264
                    ? (c >= 8544 && c <= 8584)
                    : c <= 11492)))))
              : (c <= 11507 || (c < 11647
                ? (c < 11565
                  ? (c < 11559
                    ? (c >= 11520 && c <= 11557)
                    : c <= 11559)
                  : (c <= 11565 || (c < 11631
                    ? (c >= 11568 && c <= 11623)
                    : c <= 11631)))
                : (c <= 11670 || (c < 11696
                  ? (c < 11688
                    ? (c >= 11680 && c <= 11686)
                    : c <= 11694)
                  : (c <= 11702 || (c < 11712
                    ? (c >= 11704 && c <= 11710)
                    : c <= 11718)))))))))
          : (c <= 11726 || (c < 42623
            ? (c < 12540
              ? (c < 12337
                ? (c < 11744
                  ? (c < 11736
                    ? (c >= 11728 && c <= 11734)
                    : c <= 11742)
                  : (c <= 11775 || (c < 12321
                    ? (c >= 12293 && c <= 12295)
                    : c <= 12335)))
                : (c <= 12341 || (c < 12441
                  ? (c < 12353
                    ? (c >= 12344 && c <= 12348)
                    : c <= 12438)
                  : (c <= 12442 || (c < 12449
                    ? (c >= 12445 && c <= 12447)
                    : c <= 12538)))))
              : (c <= 12543 || (c < 19968
                ? (c < 12704
                  ? (c < 12593
                    ? (c >= 12549 && c <= 12591)
                    : c <= 12686)
                  : (c <= 12735 || (c < 13312
                    ? (c >= 12784 && c <= 12799)
                    : c <= 19903)))
                : (c <= 42124 || (c < 42512
                  ? (c < 42240
                    ? (c >= 42192 && c <= 42237)
                    : c <= 42508)
                  : (c <= 42539 || (c < 42612
                    ? (c >= 42560 && c <= 42607)
                    : c <= 42621)))))))
            : (c <= 42737 || (c < 43232
              ? (c < 42965
                ? (c < 42891
                  ? (c < 42786
                    ? (c >= 42775 && c <= 42783)
                    : c <= 42888)
                  : (c <= 42954 || (c < 42963
                    ? (c >= 42960 && c <= 42961)
                    : c <= 42963)))
                : (c <= 42969 || (c < 43072
                  ? (c < 43052
                    ? (c >= 42994 && c <= 43047)
                    : c <= 43052)
                  : (c <= 43123 || (c < 43216
                    ? (c >= 43136 && c <= 43205)
                    : c <= 43225)))))
              : (c <= 43255 || (c < 43471
                ? (c < 43312
                  ? (c < 43261
                    ? c == 43259
                    : c <= 43309)
                  : (c <= 43347 || (c < 43392
                    ? (c >= 43360 && c <= 43388)
                    : c <= 43456)))
                : (c <= 43481 || (c < 43584
                  ? (c < 43520
                    ? (c >= 43488 && c <= 43518)
                    : c <= 43574)
                  : (c <= 43597 || (c >= 43600 && c <= 43609)))))))))))))))
    : (c <= 43638 || (c < 71453
      ? (c < 67639
        ? (c < 65345
          ? (c < 64312
            ? (c < 43888
              ? (c < 43785
                ? (c < 43744
                  ? (c < 43739
                    ? (c >= 43642 && c <= 43714)
                    : c <= 43741)
                  : (c <= 43759 || (c < 43777
                    ? (c >= 43762 && c <= 43766)
                    : c <= 43782)))
                : (c <= 43790 || (c < 43816
                  ? (c < 43808
                    ? (c >= 43793 && c <= 43798)
                    : c <= 43814)
                  : (c <= 43822 || (c < 43868
                    ? (c >= 43824 && c <= 43866)
                    : c <= 43881)))))
              : (c <= 44010 || (c < 63744
                ? (c < 44032
                  ? (c < 44016
                    ? (c >= 44012 && c <= 44013)
                    : c <= 44025)
                  : (c <= 55203 || (c < 55243
                    ? (c >= 55216 && c <= 55238)
                    : c <= 55291)))
                : (c <= 64109 || (c < 64275
                  ? (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)
                  : (c <= 64279 || (c < 64298
                    ? (c >= 64285 && c <= 64296)
                    : c <= 64310)))))))
            : (c <= 64316 || (c < 65075
              ? (c < 64612
                ? (c < 64323
                  ? (c < 64320
                    ? c == 64318
                    : c <= 64321)
                  : (c <= 64324 || (c < 64467
                    ? (c >= 64326 && c <= 64433)
                    : c <= 64605)))
                : (c <= 64829 || (c < 65008
                  ? (c < 64914
                    ? (c >= 64848 && c <= 64911)
                    : c <= 64967)
                  : (c <= 65017 || (c < 65056
                    ? (c >= 65024 && c <= 65039)
                    : c <= 65071)))))
              : (c <= 65076 || (c < 65147
                ? (c < 65139
                  ? (c < 65137
                    ? (c >= 65101 && c <= 65103)
                    : c <= 65137)
                  : (c <= 65139 || (c < 65145
                    ? c == 65143
                    : c <= 65145)))
                : (c <= 65147 || (c < 65296
                  ? (c < 65151
                    ? c == 65149
                    : c <= 65276)
                  : (c <= 65305 || (c < 65343
                    ? (c >= 65313 && c <= 65338)
                    : c <= 65343)))))))))
          : (c <= 65370 || (c < 66513
            ? (c < 65664
              ? (c < 65536
                ? (c < 65482
                  ? (c < 65474
                    ? (c >= 65382 && c <= 65470)
                    : c <= 65479)
                  : (c <= 65487 || (c < 65498
                    ? (c >= 65490 && c <= 65495)
                    : c <= 65500)))
                : (c <= 65547 || (c < 65596
                  ? (c < 65576
                    ? (c >= 65549 && c <= 65574)
                    : c <= 65594)
                  : (c <= 65597 || (c < 65616
                    ? (c >= 65599 && c <= 65613)
                    : c <= 65629)))))
              : (c <= 65786 || (c < 66304
                ? (c < 66176
                  ? (c < 66045
                    ? (c >= 65856 && c <= 65908)
                    : c <= 66045)
                  : (c <= 66204 || (c < 66272
                    ? (c >= 66208 && c <= 66256)
                    : c <= 66272)))
                : (c <= 66335 || (c < 66432
                  ? (c < 66384
                    ? (c >= 66349 && c <= 66378)
                    : c <= 66426)
                  : (c <= 66461 || (c < 66504
                    ? (c >= 66464 && c <= 66499)
                    : c <= 66511)))))))
            : (c <= 66517 || (c < 66979
              ? (c < 66864
                ? (c < 66736
                  ? (c < 66720
                    ? (c >= 66560 && c <= 66717)
                    : c <= 66729)
                  : (c <= 66771 || (c < 66816
                    ? (c >= 66776 && c <= 66811)
                    : c <= 66855)))
                : (c <= 66915 || (c < 66956
                  ? (c < 66940
                    ? (c >= 66928 && c <= 66938)
                    : c <= 66954)
                  : (c <= 66962 || (c < 66967
                    ? (c >= 66964 && c <= 66965)
                    : c <= 66977)))))
              : (c <= 66993 || (c < 67456
                ? (c < 67072
                  ? (c < 67003
                    ? (c >= 66995 && c <= 67001)
                    : c <= 67004)
                  : (c <= 67382 || (c < 67424
                    ? (c >= 67392 && c <= 67413)
                    : c <= 67431)))
                : (c <= 67461 || (c < 67584
                  ? (c < 67506
                    ? (c >= 67463 && c <= 67504)
                    : c <= 67514)
                  : (c <= 67589 || (c < 67594
                    ? c == 67592
                    : c <= 67637)))))))))))
        : (c <= 67640 || (c < 69956
          ? (c < 68448
            ? (c < 68101
              ? (c < 67828
                ? (c < 67680
                  ? (c < 67647
                    ? c == 67644
                    : c <= 67669)
                  : (c <= 67702 || (c < 67808
                    ? (c >= 67712 && c <= 67742)
                    : c <= 67826)))
                : (c <= 67829 || (c < 67968
                  ? (c < 67872
                    ? (c >= 67840 && c <= 67861)
                    : c <= 67897)
                  : (c <= 68023 || (c < 68096
                    ? (c >= 68030 && c <= 68031)
                    : c <= 68099)))))
              : (c <= 68102 || (c < 68192
                ? (c < 68121
                  ? (c < 68117
                    ? (c >= 68108 && c <= 68115)
                    : c <= 68119)
                  : (c <= 68149 || (c < 68159
                    ? (c >= 68152 && c <= 68154)
                    : c <= 68159)))
                : (c <= 68220 || (c < 68297
                  ? (c < 68288
                    ? (c >= 68224 && c <= 68252)
                    : c <= 68295)
                  : (c <= 68326 || (c < 68416
                    ? (c >= 68352 && c <= 68405)
                    : c <= 68437)))))))
            : (c <= 68466 || (c < 69424
              ? (c < 68912
                ? (c < 68736
                  ? (c < 68608
                    ? (c >= 68480 && c <= 68497)
                    : c <= 68680)
                  : (c <= 68786 || (c < 68864
                    ? (c >= 68800 && c <= 68850)
                    : c <= 68903)))
                : (c <= 68921 || (c < 69296
                  ? (c < 69291
                    ? (c >= 69248 && c <= 69289)
                    : c <= 69292)
                  : (c <= 69297 || (c < 69415
                    ? (c >= 69376 && c <= 69404)
                    : c <= 69415)))))
              : (c <= 69456 || (c < 69759
                ? (c < 69600
                  ? (c < 69552
                    ? (c >= 69488 && c <= 69509)
                    : c <= 69572)
                  : (c <= 69622 || (c < 69734
                    ? (c >= 69632 && c <= 69702)
                    : c <= 69749)))
                : (c <= 69818 || (c < 69872
                  ? (c < 69840
                    ? c == 69826
                    : c <= 69864)
                  : (c <= 69881 || (c < 69942
                    ? (c >= 69888 && c <= 69940)
                    : c <= 69951)))))))))
          : (c <= 69959 || (c < 70459
            ? (c < 70282
              ? (c < 70108
                ? (c < 70016
                  ? (c < 70006
                    ? (c >= 69968 && c <= 70003)
                    : c <= 70006)
                  : (c <= 70084 || (c < 70094
                    ? (c >= 70089 && c <= 70092)
                    : c <= 70106)))
                : (c <= 70108 || (c < 70206
                  ? (c < 70163
                    ? (c >= 70144 && c <= 70161)
                    : c <= 70199)
                  : (c <= 70206 || (c < 70280
                    ? (c >= 70272 && c <= 70278)
                    : c <= 70280)))))
              : (c <= 70285 || (c < 70405
                ? (c < 70320
                  ? (c < 70303
                    ? (c >= 70287 && c <= 70301)
                    : c <= 70312)
                  : (c <= 70378 || (c < 70400
                    ? (c >= 70384 && c <= 70393)
                    : c <= 70403)))
                : (c <= 70412 || (c < 70442
                  ? (c < 70419
                    ? (c >= 70415 && c <= 70416)
                    : c <= 70440)
                  : (c <= 70448 || (c < 70453
                    ? (c >= 70450 && c <= 70451)
                    : c <= 70457)))))))
            : (c <= 70468 || (c < 70855
              ? (c < 70502
                ? (c < 70480
                  ? (c < 70475
                    ? (c >= 70471 && c <= 70472)
                    : c <= 70477)
                  : (c <= 70480 || (c < 70493
                    ? c == 70487
                    : c <= 70499)))
                : (c <= 70508 || (c < 70736
                  ? (c < 70656
                    ? (c >= 70512 && c <= 70516)
                    : c <= 70730)
                  : (c <= 70745 || (c < 70784
                    ? (c >= 70750 && c <= 70753)
                    : c <= 70853)))))
              : (c <= 70855 || (c < 71236
                ? (c < 71096
                  ? (c < 71040
                    ? (c >= 70864 && c <= 70873)
                    : c <= 71093)
                  : (c <= 71104 || (c < 71168
                    ? (c >= 71128 && c <= 71133)
                    : c <= 71232)))
                : (c <= 71236 || (c < 71360
                  ? (c < 71296
                    ? (c >= 71248 && c <= 71257)
                    : c <= 71352)
                  : (c <= 71369 || (c >= 71424 && c <= 71450)))))))))))))
      : (c <= 71467 || (c < 119973
        ? (c < 77824
          ? (c < 72760
            ? (c < 72016
              ? (c < 71945
                ? (c < 71680
                  ? (c < 71488
                    ? (c >= 71472 && c <= 71481)
                    : c <= 71494)
                  : (c <= 71738 || (c < 71935
                    ? (c >= 71840 && c <= 71913)
                    : c <= 71942)))
                : (c <= 71945 || (c < 71960
                  ? (c < 71957
                    ? (c >= 71948 && c <= 71955)
                    : c <= 71958)
                  : (c <= 71989 || (c < 71995
                    ? (c >= 71991 && c <= 71992)
                    : c <= 72003)))))
              : (c <= 72025 || (c < 72263
                ? (c < 72154
                  ? (c < 72106
                    ? (c >= 72096 && c <= 72103)
                    : c <= 72151)
                  : (c <= 72161 || (c < 72192
                    ? (c >= 72163 && c <= 72164)
                    : c <= 72254)))
                : (c <= 72263 || (c < 72368
                  ? (c < 72349
                    ? (c >= 72272 && c <= 72345)
                    : c <= 72349)
                  : (c <= 72440 || (c < 72714
                    ? (c >= 72704 && c <= 72712)
                    : c <= 72758)))))))
            : (c <= 72768 || (c < 73056
              ? (c < 72968
                ? (c < 72850
                  ? (c < 72818
                    ? (c >= 72784 && c <= 72793)
                    : c <= 72847)
                  : (c <= 72871 || (c < 72960
                    ? (c >= 72873 && c <= 72886)
                    : c <= 72966)))
                : (c <= 72969 || (c < 73020
                  ? (c < 73018
                    ? (c >= 72971 && c <= 73014)
                    : c <= 73018)
                  : (c <= 73021 || (c < 73040
                    ? (c >= 73023 && c <= 73031)
                    : c <= 73049)))))
              : (c <= 73061 || (c < 73440
                ? (c < 73104
                  ? (c < 73066
                    ? (c >= 73063 && c <= 73064)
                    : c <= 73102)
                  : (c <= 73105 || (c < 73120
                    ? (c >= 73107 && c <= 73112)
                    : c <= 73129)))
                : (c <= 73462 || (c < 74752
                  ? (c < 73728
                    ? c == 73648
                    : c <= 74649)
                  : (c <= 74862 || (c < 77712
                    ? (c >= 74880 && c <= 75075)
                    : c <= 77808)))))))))
          : (c <= 78894 || (c < 110576
            ? (c < 93027
              ? (c < 92864
                ? (c < 92736
                  ? (c < 92160
                    ? (c >= 82944 && c <= 83526)
                    : c <= 92728)
                  : (c <= 92766 || (c < 92784
                    ? (c >= 92768 && c <= 92777)
                    : c <= 92862)))
                : (c <= 92873 || (c < 92928
                  ? (c < 92912
                    ? (c >= 92880 && c <= 92909)
                    : c <= 92916)
                  : (c <= 92982 || (c < 93008
                    ? (c >= 92992 && c <= 92995)
                    : c <= 93017)))))
              : (c <= 93047 || (c < 94176
                ? (c < 93952
                  ? (c < 93760
                    ? (c >= 93053 && c <= 93071)
                    : c <= 93823)
                  : (c <= 94026 || (c < 94095
                    ? (c >= 94031 && c <= 94087)
                    : c <= 94111)))
                : (c <= 94177 || (c < 94208
                  ? (c < 94192
                    ? (c >= 94179 && c <= 94180)
                    : c <= 94193)
                  : (c <= 100343 || (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)))))))
            : (c <= 110579 || (c < 118528
              ? (c < 110960
                ? (c < 110592
                  ? (c < 110589
                    ? (c >= 110581 && c <= 110587)
                    : c <= 110590)
                  : (c <= 110882 || (c < 110948
                    ? (c >= 110928 && c <= 110930)
                    : c <= 110951)))
                : (c <= 111355 || (c < 113792
                  ? (c < 113776
                    ? (c >= 113664 && c <= 113770)
                    : c <= 113788)
                  : (c <= 113800 || (c < 113821
                    ? (c >= 113808 && c <= 113817)
                    : c <= 113822)))))
              : (c <= 118573 || (c < 119210
                ? (c < 119149
                  ? (c < 119141
                    ? (c >= 118576 && c <= 118598)
                    : c <= 119145)
                  : (c <= 119154 || (c < 119173
                    ? (c >= 119163 && c <= 119170)
                    : c <= 119179)))
                : (c <= 119213 || (c < 119894
                  ? (c < 119808
                    ? (c >= 119362 && c <= 119364)
                    : c <= 119892)
                  : (c <= 119964 || (c < 119970
                    ? (c >= 119966 && c <= 119967)
                    : c <= 119970)))))))))))
        : (c <= 119974 || (c < 124912
          ? (c < 120746
            ? (c < 120134
              ? (c < 120071
                ? (c < 119995
                  ? (c < 119982
                    ? (c >= 119977 && c <= 119980)
                    : c <= 119993)
                  : (c <= 119995 || (c < 120005
                    ? (c >= 119997 && c <= 120003)
                    : c <= 120069)))
                : (c <= 120074 || (c < 120094
                  ? (c < 120086
                    ? (c >= 120077 && c <= 120084)
                    : c <= 120092)
                  : (c <= 120121 || (c < 120128
                    ? (c >= 120123 && c <= 120126)
                    : c <= 120132)))))
              : (c <= 120134 || (c < 120572
                ? (c < 120488
                  ? (c < 120146
                    ? (c >= 120138 && c <= 120144)
                    : c <= 120485)
                  : (c <= 120512 || (c < 120540
                    ? (c >= 120514 && c <= 120538)
                    : c <= 120570)))
                : (c <= 120596 || (c < 120656
                  ? (c < 120630
                    ? (c >= 120598 && c <= 120628)
                    : c <= 120654)
                  : (c <= 120686 || (c < 120714
                    ? (c >= 120688 && c <= 120712)
                    : c <= 120744)))))))
            : (c <= 120770 || (c < 122907
              ? (c < 121476
                ? (c < 121344
                  ? (c < 120782
                    ? (c >= 120772 && c <= 120779)
                    : c <= 120831)
                  : (c <= 121398 || (c < 121461
                    ? (c >= 121403 && c <= 121452)
                    : c <= 121461)))
                : (c <= 121476 || (c < 122624
                  ? (c < 121505
                    ? (c >= 121499 && c <= 121503)
                    : c <= 121519)
                  : (c <= 122654 || (c < 122888
                    ? (c >= 122880 && c <= 122886)
                    : c <= 122904)))))
              : (c <= 122913 || (c < 123214
                ? (c < 123136
                  ? (c < 122918
                    ? (c >= 122915 && c <= 122916)
                    : c <= 122922)
                  : (c <= 123180 || (c < 123200
                    ? (c >= 123184 && c <= 123197)
                    : c <= 123209)))
                : (c <= 123214 || (c < 124896
                  ? (c < 123584
                    ? (c >= 123536 && c <= 123566)
                    : c <= 123641)
                  : (c <= 124902 || (c < 124909
                    ? (c >= 124904 && c <= 124907)
                    : c <= 124910)))))))))
          : (c <= 124926 || (c < 126557
            ? (c < 126521
              ? (c < 126469
                ? (c < 125184
                  ? (c < 125136
                    ? (c >= 124928 && c <= 125124)
                    : c <= 125142)
                  : (c <= 125259 || (c < 126464
                    ? (c >= 125264 && c <= 125273)
                    : c <= 126467)))
                : (c <= 126495 || (c < 126503
                  ? (c < 126500
                    ? (c >= 126497 && c <= 126498)
                    : c <= 126500)
                  : (c <= 126503 || (c < 126516
                    ? (c >= 126505 && c <= 126514)
                    : c <= 126519)))))
              : (c <= 126521 || (c < 126541
                ? (c < 126535
                  ? (c < 126530
                    ? c == 126523
                    : c <= 126530)
                  : (c <= 126535 || (c < 126539
                    ? c == 126537
                    : c <= 126539)))
                : (c <= 126543 || (c < 126551
                  ? (c < 126548
                    ? (c >= 126545 && c <= 126546)
                    : c <= 126548)
                  : (c <= 126551 || (c < 126555
                    ? c == 126553
                    : c <= 126555)))))))
            : (c <= 126557 || (c < 126629
              ? (c < 126580
                ? (c < 126564
                  ? (c < 126561
                    ? c == 126559
                    : c <= 126562)
                  : (c <= 126564 || (c < 126572
                    ? (c >= 126567 && c <= 126570)
                    : c <= 126578)))
                : (c <= 126583 || (c < 126592
                  ? (c < 126590
                    ? (c >= 126585 && c <= 126588)
                    : c <= 126590)
                  : (c <= 126601 || (c < 126625
                    ? (c >= 126603 && c <= 126619)
                    : c <= 126627)))))
              : (c <= 126633 || (c < 178208
                ? (c < 131072
                  ? (c < 130032
                    ? (c >= 126635 && c <= 126651)
                    : c <= 130041)
                  : (c <= 173791 || (c < 177984
                    ? (c >= 173824 && c <= 177976)
                    : c <= 178205)))
                : (c <= 183969 || (c < 196608
                  ? (c < 194560
                    ? (c >= 183984 && c <= 191456)
                    : c <= 195101)
                  : (c <= 201546 || (c >= 917760 && c <= 917999)))))))))))))))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(34);
      if (lookahead == '#') ADVANCE(4);
      if (lookahead == '&') ADVANCE(78);
      if (lookahead == '(') ADVANCE(38);
      if (lookahead == ')') ADVANCE(36);
      if (lookahead == '*') ADVANCE(58);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '<') ADVANCE(62);
      if (lookahead == '=') ADVANCE(66);
      if (lookahead == '>') ADVANCE(54);
      if (lookahead == '@') ADVANCE(53);
      if (lookahead == '[') ADVANCE(67);
      if (lookahead == ']') ADVANCE(69);
      if (lookahead == '^') ADVANCE(57);
      if (lookahead == 'o') ADVANCE(71);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (lookahead == '|') ADVANCE(122);
      if (lookahead == '~') ADVANCE(41);
      if (lookahead == 176) ADVANCE(70);
      if (lookahead == 8776) ADVANCE(65);
      if (lookahead == 9753) ADVANCE(84);
      if (lookahead == 9825) ADVANCE(80);
      if (lookahead == 9829) ADVANCE(85);
      if (lookahead == 10083) ADVANCE(86);
      if (lookahead == 10084) ADVANCE(87);
      if (lookahead == 10085) ADVANCE(88);
      if (lookahead == 10086) ADVANCE(89);
      if (lookahead == 10087) ADVANCE(90);
      if (lookahead == 127892) ADVANCE(91);
      if (lookahead == 127977) ADVANCE(121);
      if (lookahead == 128140) ADVANCE(112);
      if (lookahead == 128147) ADVANCE(105);
      if (lookahead == 128148) ADVANCE(82);
      if (lookahead == 128149) ADVANCE(106);
      if (lookahead == 128150) ADVANCE(107);
      if (lookahead == 128151) ADVANCE(108);
      if (lookahead == 128152) ADVANCE(109);
      if (lookahead == 128153) ADVANCE(94);
      if (lookahead == 128154) ADVANCE(97);
      if (lookahead == 128155) ADVANCE(98);
      if (lookahead == 128156) ADVANCE(99);
      if (lookahead == 128157) ADVANCE(110);
      if (lookahead == 128158) ADVANCE(113);
      if (lookahead == 128159) ADVANCE(114);
      if (lookahead == 128420) ADVANCE(93);
      if (lookahead == 129293) ADVANCE(101);
      if (lookahead == 129294) ADVANCE(102);
      if (lookahead == 129425) ADVANCE(43);
      if (lookahead == 129505) ADVANCE(100);
      if (lookahead == 129653) ADVANCE(96);
      if (lookahead == 129654) ADVANCE(103);
      if (lookahead == 129655) ADVANCE(95);
      if (lookahead == 129728) ADVANCE(92);
      if (lookahead == 129782) ADVANCE(115);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(32)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 1:
      if (lookahead == '#') ADVANCE(4);
      if (lookahead == '(') ADVANCE(75);
      if (lookahead == ')') ADVANCE(74);
      if (lookahead == '>') ADVANCE(22);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 2:
      if (lookahead == '#') ADVANCE(4);
      if (lookahead == '(' ||
          lookahead == ')') ADVANCE(74);
      if (lookahead == '>') ADVANCE(22);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 3:
      if (lookahead == '#') ADVANCE(59);
      END_STATE();
    case 4:
      if (lookahead == '#') ADVANCE(3);
      END_STATE();
    case 5:
      if (lookahead == '&') ADVANCE(78);
      if (lookahead == '(') ADVANCE(38);
      if (lookahead == ')') ADVANCE(36);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '<') ADVANCE(61);
      if (lookahead == '=') ADVANCE(66);
      if (lookahead == '>') ADVANCE(7);
      if (lookahead == '[') ADVANCE(67);
      if (lookahead == ']') ADVANCE(69);
      if (lookahead == '^') ADVANCE(57);
      if (lookahead == 'o') ADVANCE(12);
      if (lookahead == '|') ADVANCE(122);
      if (lookahead == '~') ADVANCE(41);
      if (lookahead == 8776) ADVANCE(65);
      if (lookahead == 9753) ADVANCE(84);
      if (lookahead == 9825) ADVANCE(80);
      if (lookahead == 9829) ADVANCE(85);
      if (lookahead == 10083) ADVANCE(86);
      if (lookahead == 10084) ADVANCE(87);
      if (lookahead == 10085) ADVANCE(88);
      if (lookahead == 10086) ADVANCE(89);
      if (lookahead == 10087) ADVANCE(90);
      if (lookahead == 127892) ADVANCE(91);
      if (lookahead == 127977) ADVANCE(121);
      if (lookahead == 128140) ADVANCE(112);
      if (lookahead == 128147) ADVANCE(105);
      if (lookahead == 128148) ADVANCE(82);
      if (lookahead == 128149) ADVANCE(106);
      if (lookahead == 128150) ADVANCE(107);
      if (lookahead == 128151) ADVANCE(108);
      if (lookahead == 128152) ADVANCE(109);
      if (lookahead == 128153) ADVANCE(94);
      if (lookahead == 128154) ADVANCE(97);
      if (lookahead == 128155) ADVANCE(98);
      if (lookahead == 128156) ADVANCE(99);
      if (lookahead == 128157) ADVANCE(110);
      if (lookahead == 128158) ADVANCE(113);
      if (lookahead == 128159) ADVANCE(114);
      if (lookahead == 128420) ADVANCE(93);
      if (lookahead == 129293) ADVANCE(101);
      if (lookahead == 129294) ADVANCE(102);
      if (lookahead == 129505) ADVANCE(100);
      if (lookahead == 129653) ADVANCE(96);
      if (lookahead == 129654) ADVANCE(103);
      if (lookahead == 129655) ADVANCE(95);
      if (lookahead == 129728) ADVANCE(92);
      if (lookahead == 129782) ADVANCE(115);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5)
      END_STATE();
    case 6:
      if (lookahead == '(') ADVANCE(38);
      if (lookahead == '<') ADVANCE(63);
      if (lookahead == '>') ADVANCE(55);
      if (lookahead == '[') ADVANCE(67);
      if (lookahead == 'o') ADVANCE(11);
      if (lookahead == 129425) ADVANCE(43);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6)
      END_STATE();
    case 7:
      if (lookahead == '(') ADVANCE(35);
      if (lookahead == '<') ADVANCE(50);
      if (lookahead == '>') ADVANCE(77);
      END_STATE();
    case 8:
      if (lookahead == '(') ADVANCE(37);
      if (lookahead == '<') ADVANCE(60);
      if (lookahead == '>') ADVANCE(21);
      if (lookahead == '[') ADVANCE(67);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(8)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 9:
      if (lookahead == '(') ADVANCE(52);
      END_STATE();
    case 10:
      if (lookahead == ')') ADVANCE(49);
      END_STATE();
    case 11:
      if (lookahead == '+') ADVANCE(10);
      END_STATE();
    case 12:
      if (lookahead == '+') ADVANCE(10);
      if (lookahead == '=') ADVANCE(135);
      if (lookahead == '~') ADVANCE(127);
      if (lookahead == 8776) ADVANCE(133);
      END_STATE();
    case 13:
      if (lookahead == '/') ADVANCE(25);
      END_STATE();
    case 14:
      if (lookahead == '/') ADVANCE(23);
      END_STATE();
    case 15:
      if (lookahead == '/') ADVANCE(24);
      END_STATE();
    case 16:
      if (lookahead == '/') ADVANCE(14);
      END_STATE();
    case 17:
      if (lookahead == '3') ADVANCE(81);
      END_STATE();
    case 18:
      if (lookahead == '<') ADVANCE(47);
      END_STATE();
    case 19:
      if (lookahead == '<') ADVANCE(45);
      END_STATE();
    case 20:
      if (lookahead == '<') ADVANCE(39);
      END_STATE();
    case 21:
      if (lookahead == '<') ADVANCE(50);
      END_STATE();
    case 22:
      if (lookahead == '<') ADVANCE(16);
      END_STATE();
    case 23:
      if (lookahead == '>') ADVANCE(139);
      END_STATE();
    case 24:
      if (lookahead == '>') ADVANCE(44);
      END_STATE();
    case 25:
      if (lookahead == '>') ADVANCE(19);
      END_STATE();
    case 26:
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 27:
      if (lookahead == 129657) ADVANCE(83);
      END_STATE();
    case 28:
      if (lookahead == '(' ||
          lookahead == ')') ADVANCE(74);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '>') ADVANCE(56);
      if (lookahead == 'o' ||
          lookahead == 176) ADVANCE(70);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(29)
      END_STATE();
    case 29:
      if (lookahead == '(' ||
          lookahead == ')') ADVANCE(74);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '>') ADVANCE(56);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(29)
      END_STATE();
    case 30:
      if (lookahead == '(' ||
          lookahead == ')') ADVANCE(74);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '>') ADVANCE(21);
      if (lookahead == 'o') ADVANCE(72);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (lookahead == 176) ADVANCE(70);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(31)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 31:
      if (lookahead == '(' ||
          lookahead == ')') ADVANCE(74);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '>') ADVANCE(21);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(31)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 32:
      if (eof) ADVANCE(34);
      if (lookahead == '#') ADVANCE(4);
      if (lookahead == '&') ADVANCE(78);
      if (lookahead == '(') ADVANCE(38);
      if (lookahead == ')') ADVANCE(36);
      if (lookahead == '*') ADVANCE(58);
      if (lookahead == '-') ADVANCE(68);
      if (lookahead == '<') ADVANCE(62);
      if (lookahead == '=') ADVANCE(66);
      if (lookahead == '>') ADVANCE(54);
      if (lookahead == '@') ADVANCE(53);
      if (lookahead == '[') ADVANCE(67);
      if (lookahead == ']') ADVANCE(69);
      if (lookahead == '^') ADVANCE(57);
      if (lookahead == 'o') ADVANCE(137);
      if (lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (lookahead == '|') ADVANCE(122);
      if (lookahead == '~') ADVANCE(41);
      if (lookahead == 8776) ADVANCE(65);
      if (lookahead == 9753) ADVANCE(84);
      if (lookahead == 9825) ADVANCE(80);
      if (lookahead == 9829) ADVANCE(85);
      if (lookahead == 10083) ADVANCE(86);
      if (lookahead == 10084) ADVANCE(87);
      if (lookahead == 10085) ADVANCE(88);
      if (lookahead == 10086) ADVANCE(89);
      if (lookahead == 10087) ADVANCE(90);
      if (lookahead == 127892) ADVANCE(91);
      if (lookahead == 127977) ADVANCE(121);
      if (lookahead == 128140) ADVANCE(112);
      if (lookahead == 128147) ADVANCE(105);
      if (lookahead == 128148) ADVANCE(82);
      if (lookahead == 128149) ADVANCE(106);
      if (lookahead == 128150) ADVANCE(107);
      if (lookahead == 128151) ADVANCE(108);
      if (lookahead == 128152) ADVANCE(109);
      if (lookahead == 128153) ADVANCE(94);
      if (lookahead == 128154) ADVANCE(97);
      if (lookahead == 128155) ADVANCE(98);
      if (lookahead == 128156) ADVANCE(99);
      if (lookahead == 128157) ADVANCE(110);
      if (lookahead == 128158) ADVANCE(113);
      if (lookahead == 128159) ADVANCE(114);
      if (lookahead == 128420) ADVANCE(93);
      if (lookahead == 129293) ADVANCE(101);
      if (lookahead == 129294) ADVANCE(102);
      if (lookahead == 129425) ADVANCE(43);
      if (lookahead == 129505) ADVANCE(100);
      if (lookahead == 129653) ADVANCE(96);
      if (lookahead == 129654) ADVANCE(103);
      if (lookahead == 129655) ADVANCE(95);
      if (lookahead == 129728) ADVANCE(92);
      if (lookahead == 129782) ADVANCE(115);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(32)
      if (sym__name_character_set_1(lookahead)) ADVANCE(138);
      END_STATE();
    case 33:
      if (eof) ADVANCE(34);
      if (lookahead == '(') ADVANCE(38);
      if (lookahead == ')') ADVANCE(20);
      if (lookahead == '<') ADVANCE(64);
      if (lookahead == '>') ADVANCE(54);
      if (lookahead == '[') ADVANCE(67);
      if (lookahead == 'o') ADVANCE(11);
      if (lookahead == '~') ADVANCE(40);
      if (lookahead == 129425) ADVANCE(43);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(33)
      END_STATE();
    case 34:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_GT_LPAREN);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead == '+') ADVANCE(26);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_RPAREN_LT);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_TILDE);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_TILDE);
      if (lookahead == '=') ADVANCE(125);
      if (lookahead == 'o') ADVANCE(128);
      if (lookahead == 8776) ADVANCE(126);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_LT_TILDE);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_U0001f991);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_GT_LT_BSLASH_SLASH_GT);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_LT_BSLASH_SLASH_GT_LT);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_GT_LT_GT);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_LT_GT_LT);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_LPAREN_PLUSo);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_o_PLUS_RPAREN);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_GT_LT);
      if (lookahead == '/') ADVANCE(14);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_GT_LT);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == '>') ADVANCE(46);
      if (lookahead == '\\') ADVANCE(15);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_LPAREN_LPAREN_LPAREN);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '(') ADVANCE(35);
      if (lookahead == '<') ADVANCE(51);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '<') ADVANCE(51);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '<') ADVANCE(16);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_CARET);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(anon_sym_POUND_POUND_POUND);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '/') ADVANCE(17);
      if (lookahead == '3') ADVANCE(79);
      if (lookahead == '<') ADVANCE(76);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '/') ADVANCE(17);
      if (lookahead == '3') ADVANCE(79);
      if (lookahead == '<') ADVANCE(76);
      if (lookahead == '>') ADVANCE(18);
      if (lookahead == '\\') ADVANCE(13);
      if (lookahead == '~') ADVANCE(42);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '>') ADVANCE(18);
      if (lookahead == '\\') ADVANCE(13);
      if (lookahead == '~') ADVANCE(42);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '\\') ADVANCE(13);
      if (lookahead == '~') ADVANCE(42);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_u2248);
      if (lookahead == 'o') ADVANCE(134);
      if (lookahead == 8776) ADVANCE(124);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(123);
      if (lookahead == 'o') ADVANCE(136);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(aux_sym_positive_scales_token1);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(aux_sym_positive_scales_token1);
      if (lookahead == '+') ADVANCE(10);
      if (lookahead == '=') ADVANCE(135);
      if (lookahead == '~') ADVANCE(127);
      if (lookahead == 8776) ADVANCE(133);
      if (sym__name_character_set_2(lookahead)) ADVANCE(138);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(aux_sym_positive_scales_token1);
      if (sym__name_character_set_2(lookahead)) ADVANCE(138);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_one);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_zero);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_zero);
      if (lookahead == '(') ADVANCE(9);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_LT_LT);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_GT_GT);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_AMP);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_LT3);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_u2661);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_LT_SLASH3);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_U0001f494);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_u2764ufe0fu200dU0001fa79);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(anon_sym_u2619);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(anon_sym_u2665);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(anon_sym_u2763);
      if (lookahead == 65039) ADVANCE(111);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(anon_sym_u2764);
      if (lookahead == 65039) ADVANCE(104);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_u2765);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(anon_sym_u2766);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(anon_sym_u2767);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(anon_sym_U0001f394);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_U0001fac0);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(anon_sym_U0001f5a4);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(anon_sym_U0001f499);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(anon_sym_U0001fa77);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_U0001fa75);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_U0001f49a);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_U0001f49b);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_U0001f49c);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(anon_sym_U0001f9e1);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(anon_sym_U0001f90d);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(anon_sym_U0001f90e);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_U0001fa76);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_u2764ufe0f);
      if (lookahead == 8205) ADVANCE(27);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(anon_sym_U0001f493);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(anon_sym_U0001f495);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(anon_sym_U0001f496);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_U0001f497);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_U0001f498);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_U0001f49d);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_u2763ufe0f);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(anon_sym_U0001f48c);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(anon_sym_U0001f49e);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_U0001f49f);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(anon_sym_U0001faf6);
      if (lookahead == 127995) ADVANCE(116);
      if (lookahead == 127996) ADVANCE(117);
      if (lookahead == 127997) ADVANCE(118);
      if (lookahead == 127998) ADVANCE(119);
      if (lookahead == 127999) ADVANCE(120);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(anon_sym_U0001faf6U0001f3fb);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_U0001faf6U0001f3fc);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_U0001faf6U0001f3fd);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_U0001faf6U0001f3fe);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_U0001faf6U0001f3ff);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_U0001f3e9);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_PIPE);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_u2248u2248);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_TILDE_EQ);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_TILDEu2248);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_o_TILDE);
      if (lookahead == '=') ADVANCE(129);
      if (lookahead == 8776) ADVANCE(130);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_TILDEo);
      if (lookahead == '=') ADVANCE(131);
      if (lookahead == 8776) ADVANCE(132);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_o_TILDE_EQ);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_o_TILDEu2248);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(anon_sym_TILDEo_EQ);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(anon_sym_TILDEou2248);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(anon_sym_ou2248);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(anon_sym_u2248o);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(anon_sym_o_EQ);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(anon_sym_EQo);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(sym__name);
      if (lookahead == '+') ADVANCE(10);
      if (lookahead == '=') ADVANCE(135);
      if (lookahead == '~') ADVANCE(127);
      if (lookahead == 8776) ADVANCE(133);
      if (sym__name_character_set_2(lookahead)) ADVANCE(138);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(sym__name);
      if (sym__name_character_set_2(lookahead)) ADVANCE(138);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(139);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 33, .external_lex_state = 1},
  [2] = {.lex_state = 5, .external_lex_state = 1},
  [3] = {.lex_state = 5, .external_lex_state = 1},
  [4] = {.lex_state = 5, .external_lex_state = 1},
  [5] = {.lex_state = 5, .external_lex_state = 1},
  [6] = {.lex_state = 5, .external_lex_state = 1},
  [7] = {.lex_state = 5, .external_lex_state = 1},
  [8] = {.lex_state = 5, .external_lex_state = 1},
  [9] = {.lex_state = 5, .external_lex_state = 1},
  [10] = {.lex_state = 5, .external_lex_state = 1},
  [11] = {.lex_state = 5, .external_lex_state = 1},
  [12] = {.lex_state = 5, .external_lex_state = 1},
  [13] = {.lex_state = 5, .external_lex_state = 1},
  [14] = {.lex_state = 5, .external_lex_state = 1},
  [15] = {.lex_state = 5, .external_lex_state = 1},
  [16] = {.lex_state = 5, .external_lex_state = 1},
  [17] = {.lex_state = 5, .external_lex_state = 1},
  [18] = {.lex_state = 5, .external_lex_state = 1},
  [19] = {.lex_state = 5, .external_lex_state = 1},
  [20] = {.lex_state = 5, .external_lex_state = 1},
  [21] = {.lex_state = 5, .external_lex_state = 1},
  [22] = {.lex_state = 5, .external_lex_state = 1},
  [23] = {.lex_state = 5, .external_lex_state = 1},
  [24] = {.lex_state = 5, .external_lex_state = 1},
  [25] = {.lex_state = 5, .external_lex_state = 1},
  [26] = {.lex_state = 5, .external_lex_state = 1},
  [27] = {.lex_state = 5, .external_lex_state = 1},
  [28] = {.lex_state = 5, .external_lex_state = 1},
  [29] = {.lex_state = 5, .external_lex_state = 1},
  [30] = {.lex_state = 5, .external_lex_state = 1},
  [31] = {.lex_state = 5, .external_lex_state = 1},
  [32] = {.lex_state = 5, .external_lex_state = 1},
  [33] = {.lex_state = 5, .external_lex_state = 1},
  [34] = {.lex_state = 5, .external_lex_state = 1},
  [35] = {.lex_state = 5, .external_lex_state = 1},
  [36] = {.lex_state = 5, .external_lex_state = 1},
  [37] = {.lex_state = 33, .external_lex_state = 1},
  [38] = {.lex_state = 33, .external_lex_state = 1},
  [39] = {.lex_state = 6, .external_lex_state = 1},
  [40] = {.lex_state = 6, .external_lex_state = 1},
  [41] = {.lex_state = 6, .external_lex_state = 1},
  [42] = {.lex_state = 6, .external_lex_state = 1},
  [43] = {.lex_state = 6, .external_lex_state = 1},
  [44] = {.lex_state = 5, .external_lex_state = 1},
  [45] = {.lex_state = 5, .external_lex_state = 1},
  [46] = {.lex_state = 5, .external_lex_state = 1},
  [47] = {.lex_state = 5, .external_lex_state = 1},
  [48] = {.lex_state = 5, .external_lex_state = 1},
  [49] = {.lex_state = 5, .external_lex_state = 1},
  [50] = {.lex_state = 5, .external_lex_state = 1},
  [51] = {.lex_state = 8, .external_lex_state = 1},
  [52] = {.lex_state = 5, .external_lex_state = 1},
  [53] = {.lex_state = 5, .external_lex_state = 1},
  [54] = {.lex_state = 5, .external_lex_state = 1},
  [55] = {.lex_state = 5, .external_lex_state = 1},
  [56] = {.lex_state = 5, .external_lex_state = 1},
  [57] = {.lex_state = 5, .external_lex_state = 1},
  [58] = {.lex_state = 5, .external_lex_state = 1},
  [59] = {.lex_state = 5, .external_lex_state = 1},
  [60] = {.lex_state = 5, .external_lex_state = 1},
  [61] = {.lex_state = 5, .external_lex_state = 1},
  [62] = {.lex_state = 33, .external_lex_state = 1},
  [63] = {.lex_state = 33, .external_lex_state = 1},
  [64] = {.lex_state = 33, .external_lex_state = 1},
  [65] = {.lex_state = 33, .external_lex_state = 1},
  [66] = {.lex_state = 6, .external_lex_state = 1},
  [67] = {.lex_state = 33, .external_lex_state = 1},
  [68] = {.lex_state = 33, .external_lex_state = 1},
  [69] = {.lex_state = 33, .external_lex_state = 1},
  [70] = {.lex_state = 33, .external_lex_state = 1},
  [71] = {.lex_state = 6, .external_lex_state = 1},
  [72] = {.lex_state = 6, .external_lex_state = 1},
  [73] = {.lex_state = 6, .external_lex_state = 1},
  [74] = {.lex_state = 6, .external_lex_state = 1},
  [75] = {.lex_state = 6, .external_lex_state = 1},
  [76] = {.lex_state = 28, .external_lex_state = 1},
  [77] = {.lex_state = 1, .external_lex_state = 1},
  [78] = {.lex_state = 28, .external_lex_state = 1},
  [79] = {.lex_state = 30, .external_lex_state = 1},
  [80] = {.lex_state = 28, .external_lex_state = 1},
  [81] = {.lex_state = 30, .external_lex_state = 1},
  [82] = {.lex_state = 28, .external_lex_state = 1},
  [83] = {.lex_state = 28, .external_lex_state = 1},
  [84] = {.lex_state = 30, .external_lex_state = 1},
  [85] = {.lex_state = 28, .external_lex_state = 1},
  [86] = {.lex_state = 30, .external_lex_state = 1},
  [87] = {.lex_state = 28, .external_lex_state = 1},
  [88] = {.lex_state = 2, .external_lex_state = 1},
  [89] = {.lex_state = 30, .external_lex_state = 1},
  [90] = {.lex_state = 0, .external_lex_state = 1},
  [91] = {.lex_state = 0, .external_lex_state = 1},
  [92] = {.lex_state = 0, .external_lex_state = 1},
  [93] = {.lex_state = 28, .external_lex_state = 1},
  [94] = {.lex_state = 28, .external_lex_state = 1},
  [95] = {.lex_state = 5, .external_lex_state = 1},
  [96] = {.lex_state = 28, .external_lex_state = 1},
  [97] = {.lex_state = 5, .external_lex_state = 1},
  [98] = {.lex_state = 30, .external_lex_state = 1},
  [99] = {.lex_state = 0, .external_lex_state = 1},
  [100] = {.lex_state = 30, .external_lex_state = 1},
  [101] = {.lex_state = 30, .external_lex_state = 1},
  [102] = {.lex_state = 30, .external_lex_state = 1},
  [103] = {.lex_state = 0, .external_lex_state = 1},
  [104] = {.lex_state = 28, .external_lex_state = 1},
  [105] = {.lex_state = 28, .external_lex_state = 1},
  [106] = {.lex_state = 28, .external_lex_state = 1},
  [107] = {.lex_state = 0, .external_lex_state = 1},
  [108] = {.lex_state = 5, .external_lex_state = 1},
  [109] = {.lex_state = 0, .external_lex_state = 1},
  [110] = {.lex_state = 5, .external_lex_state = 1},
  [111] = {.lex_state = 0, .external_lex_state = 1},
  [112] = {.lex_state = 0, .external_lex_state = 1},
  [113] = {.lex_state = 0, .external_lex_state = 1},
  [114] = {.lex_state = 0, .external_lex_state = 1},
  [115] = {.lex_state = 0, .external_lex_state = 1},
  [116] = {.lex_state = 0, .external_lex_state = 1},
  [117] = {.lex_state = 0, .external_lex_state = 1},
  [118] = {.lex_state = 0, .external_lex_state = 1},
  [119] = {.lex_state = 0, .external_lex_state = 1},
  [120] = {.lex_state = 0, .external_lex_state = 1},
  [121] = {.lex_state = 0, .external_lex_state = 1},
  [122] = {.lex_state = 0, .external_lex_state = 1},
  [123] = {.lex_state = 5, .external_lex_state = 1},
  [124] = {.lex_state = 8, .external_lex_state = 1},
  [125] = {.lex_state = 33, .external_lex_state = 1},
  [126] = {.lex_state = 0, .external_lex_state = 1},
  [127] = {.lex_state = 28, .external_lex_state = 1},
  [128] = {.lex_state = 0, .external_lex_state = 1},
  [129] = {.lex_state = 1, .external_lex_state = 1},
  [130] = {.lex_state = 8, .external_lex_state = 1},
  [131] = {.lex_state = 28, .external_lex_state = 1},
  [132] = {.lex_state = 28, .external_lex_state = 1},
  [133] = {.lex_state = 28, .external_lex_state = 1},
  [134] = {.lex_state = 5, .external_lex_state = 1},
  [135] = {.lex_state = 0, .external_lex_state = 1},
  [136] = {.lex_state = 8, .external_lex_state = 1},
  [137] = {.lex_state = 33, .external_lex_state = 1},
  [138] = {.lex_state = 5, .external_lex_state = 1},
  [139] = {.lex_state = 5, .external_lex_state = 1},
  [140] = {.lex_state = 1, .external_lex_state = 1},
  [141] = {.lex_state = 28, .external_lex_state = 1},
  [142] = {.lex_state = 28, .external_lex_state = 1},
  [143] = {.lex_state = 0, .external_lex_state = 1},
  [144] = {.lex_state = 0, .external_lex_state = 1},
  [145] = {.lex_state = 5, .external_lex_state = 1},
  [146] = {.lex_state = 33, .external_lex_state = 1},
  [147] = {.lex_state = 33, .external_lex_state = 1},
  [148] = {.lex_state = 5, .external_lex_state = 1},
  [149] = {.lex_state = 0, .external_lex_state = 1},
  [150] = {.lex_state = 28, .external_lex_state = 1},
  [151] = {.lex_state = 33, .external_lex_state = 1},
  [152] = {.lex_state = 33, .external_lex_state = 1},
  [153] = {.lex_state = 0, .external_lex_state = 1},
  [154] = {.lex_state = 8, .external_lex_state = 1},
  [155] = {.lex_state = 0, .external_lex_state = 1},
  [156] = {.lex_state = 5, .external_lex_state = 1},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym__name] = ACTIONS(1),
    [anon_sym_GT_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_TILDE] = ACTIONS(1),
    [anon_sym_LT_TILDE] = ACTIONS(1),
    [anon_sym_U0001f991] = ACTIONS(1),
    [anon_sym_GT_LT_BSLASH_SLASH_GT] = ACTIONS(1),
    [anon_sym_LT_BSLASH_SLASH_GT_LT] = ACTIONS(1),
    [anon_sym_GT_LT_GT] = ACTIONS(1),
    [anon_sym_LT_GT_LT] = ACTIONS(1),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(1),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(1),
    [anon_sym_GT_LT] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_CARET] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_POUND_POUND_POUND] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_u2248] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [aux_sym_positive_scales_token1] = ACTIONS(1),
    [sym_one] = ACTIONS(1),
    [sym_zero] = ACTIONS(1),
    [anon_sym_LT_LT] = ACTIONS(1),
    [anon_sym_AMP] = ACTIONS(1),
    [anon_sym_LT3] = ACTIONS(1),
    [anon_sym_u2661] = ACTIONS(1),
    [anon_sym_LT_SLASH3] = ACTIONS(1),
    [anon_sym_U0001f494] = ACTIONS(1),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(1),
    [anon_sym_u2619] = ACTIONS(1),
    [anon_sym_u2665] = ACTIONS(1),
    [anon_sym_u2763] = ACTIONS(1),
    [anon_sym_u2764] = ACTIONS(1),
    [anon_sym_u2765] = ACTIONS(1),
    [anon_sym_u2766] = ACTIONS(1),
    [anon_sym_u2767] = ACTIONS(1),
    [anon_sym_U0001f394] = ACTIONS(1),
    [anon_sym_U0001fac0] = ACTIONS(1),
    [anon_sym_U0001f5a4] = ACTIONS(1),
    [anon_sym_U0001f499] = ACTIONS(1),
    [anon_sym_U0001fa77] = ACTIONS(1),
    [anon_sym_U0001fa75] = ACTIONS(1),
    [anon_sym_U0001f49a] = ACTIONS(1),
    [anon_sym_U0001f49b] = ACTIONS(1),
    [anon_sym_U0001f49c] = ACTIONS(1),
    [anon_sym_U0001f9e1] = ACTIONS(1),
    [anon_sym_U0001f90d] = ACTIONS(1),
    [anon_sym_U0001f90e] = ACTIONS(1),
    [anon_sym_U0001fa76] = ACTIONS(1),
    [anon_sym_u2764ufe0f] = ACTIONS(1),
    [anon_sym_U0001f493] = ACTIONS(1),
    [anon_sym_U0001f495] = ACTIONS(1),
    [anon_sym_U0001f496] = ACTIONS(1),
    [anon_sym_U0001f497] = ACTIONS(1),
    [anon_sym_U0001f498] = ACTIONS(1),
    [anon_sym_U0001f49d] = ACTIONS(1),
    [anon_sym_u2763ufe0f] = ACTIONS(1),
    [anon_sym_U0001f48c] = ACTIONS(1),
    [anon_sym_U0001f49e] = ACTIONS(1),
    [anon_sym_U0001f49f] = ACTIONS(1),
    [anon_sym_U0001faf6] = ACTIONS(1),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(1),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(1),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(1),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(1),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(1),
    [anon_sym_U0001f3e9] = ACTIONS(1),
    [anon_sym_PIPE] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_u2248u2248] = ACTIONS(1),
    [anon_sym_TILDE_EQ] = ACTIONS(1),
    [anon_sym_TILDEu2248] = ACTIONS(1),
    [anon_sym_o_TILDE] = ACTIONS(1),
    [anon_sym_TILDEo] = ACTIONS(1),
    [anon_sym_o_TILDE_EQ] = ACTIONS(1),
    [anon_sym_o_TILDEu2248] = ACTIONS(1),
    [anon_sym_TILDEo_EQ] = ACTIONS(1),
    [anon_sym_TILDEou2248] = ACTIONS(1),
    [anon_sym_ou2248] = ACTIONS(1),
    [anon_sym_u2248o] = ACTIONS(1),
    [anon_sym_o_EQ] = ACTIONS(1),
    [anon_sym_EQo] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(135),
    [sym_subroutine] = STATE(37),
    [sym_right_sub] = STATE(99),
    [sym__statement] = STATE(37),
    [sym__simple_statement] = STATE(37),
    [sym_return_statement] = STATE(146),
    [sym_break_statement] = STATE(146),
    [sym_block] = STATE(37),
    [sym_anchor_statement] = STATE(146),
    [sym_loopy_fysh] = STATE(115),
    [sym_happy_fysh] = STATE(118),
    [sym_grilled_fysh] = STATE(10),
    [sym_loop_statement] = STATE(37),
    [sym_if_statement] = STATE(37),
    [sym_expression_statement] = STATE(146),
    [sym_inc_statement] = STATE(146),
    [sym_dec_statement] = STATE(146),
    [sym_assignment_statement] = STATE(146),
    [sym__expression] = STATE(10),
    [sym_aquarium] = STATE(10),
    [sym_fysh_bowl] = STATE(10),
    [sym_positive_ident] = STATE(35),
    [sym_positive_scales] = STATE(10),
    [sym_positive_bones] = STATE(10),
    [sym_negative_ident] = STATE(10),
    [sym_negative_scales] = STATE(10),
    [sym_negative_bones] = STATE(10),
    [sym_binary_expression] = STATE(10),
    [sym_call_expression] = STATE(10),
    [sym_addition] = STATE(24),
    [aux_sym_source_file_repeat1] = STATE(37),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_GT_LPAREN] = ACTIONS(7),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_LT_TILDE] = ACTIONS(11),
    [anon_sym_U0001f991] = ACTIONS(11),
    [anon_sym_GT_LT_BSLASH_SLASH_GT] = ACTIONS(13),
    [anon_sym_LT_BSLASH_SLASH_GT_LT] = ACTIONS(13),
    [anon_sym_GT_LT_GT] = ACTIONS(15),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(17),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(17),
    [anon_sym_GT_LT] = ACTIONS(19),
    [anon_sym_GT] = ACTIONS(21),
    [anon_sym_LT] = ACTIONS(23),
    [anon_sym_LBRACK] = ACTIONS(25),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [2] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_GT_LPAREN] = ACTIONS(27),
    [anon_sym_RPAREN] = ACTIONS(27),
    [anon_sym_LPAREN] = ACTIONS(29),
    [anon_sym_TILDE] = ACTIONS(29),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(27),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(27),
    [anon_sym_GT_LT] = ACTIONS(29),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(29),
    [anon_sym_LBRACK] = ACTIONS(27),
    [anon_sym_DASH] = ACTIONS(27),
    [anon_sym_RBRACK] = ACTIONS(27),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(27),
    [anon_sym_u2248u2248] = ACTIONS(27),
    [anon_sym_TILDE_EQ] = ACTIONS(27),
    [anon_sym_TILDEu2248] = ACTIONS(27),
    [anon_sym_o_TILDE] = ACTIONS(29),
    [anon_sym_TILDEo] = ACTIONS(29),
    [anon_sym_o_TILDE_EQ] = ACTIONS(27),
    [anon_sym_o_TILDEu2248] = ACTIONS(27),
    [anon_sym_TILDEo_EQ] = ACTIONS(27),
    [anon_sym_TILDEou2248] = ACTIONS(27),
    [anon_sym_ou2248] = ACTIONS(27),
    [anon_sym_u2248o] = ACTIONS(27),
    [anon_sym_o_EQ] = ACTIONS(27),
    [anon_sym_EQo] = ACTIONS(27),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [3] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_GT_LPAREN] = ACTIONS(27),
    [anon_sym_RPAREN] = ACTIONS(27),
    [anon_sym_LPAREN] = ACTIONS(29),
    [anon_sym_TILDE] = ACTIONS(29),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(27),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(27),
    [anon_sym_GT_LT] = ACTIONS(29),
    [anon_sym_CARET] = ACTIONS(27),
    [anon_sym_LT] = ACTIONS(29),
    [anon_sym_LBRACK] = ACTIONS(27),
    [anon_sym_DASH] = ACTIONS(27),
    [anon_sym_RBRACK] = ACTIONS(27),
    [anon_sym_LT_LT] = ACTIONS(27),
    [anon_sym_GT_GT] = ACTIONS(27),
    [anon_sym_AMP] = ACTIONS(27),
    [anon_sym_LT3] = ACTIONS(27),
    [anon_sym_u2661] = ACTIONS(27),
    [anon_sym_LT_SLASH3] = ACTIONS(27),
    [anon_sym_U0001f494] = ACTIONS(27),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(27),
    [anon_sym_u2619] = ACTIONS(27),
    [anon_sym_u2665] = ACTIONS(27),
    [anon_sym_u2763] = ACTIONS(29),
    [anon_sym_u2764] = ACTIONS(29),
    [anon_sym_u2765] = ACTIONS(27),
    [anon_sym_u2766] = ACTIONS(27),
    [anon_sym_u2767] = ACTIONS(27),
    [anon_sym_U0001f394] = ACTIONS(27),
    [anon_sym_U0001fac0] = ACTIONS(27),
    [anon_sym_U0001f5a4] = ACTIONS(27),
    [anon_sym_U0001f499] = ACTIONS(27),
    [anon_sym_U0001fa77] = ACTIONS(27),
    [anon_sym_U0001fa75] = ACTIONS(27),
    [anon_sym_U0001f49a] = ACTIONS(27),
    [anon_sym_U0001f49b] = ACTIONS(27),
    [anon_sym_U0001f49c] = ACTIONS(27),
    [anon_sym_U0001f9e1] = ACTIONS(27),
    [anon_sym_U0001f90d] = ACTIONS(27),
    [anon_sym_U0001f90e] = ACTIONS(27),
    [anon_sym_U0001fa76] = ACTIONS(27),
    [anon_sym_u2764ufe0f] = ACTIONS(29),
    [anon_sym_U0001f493] = ACTIONS(27),
    [anon_sym_U0001f495] = ACTIONS(27),
    [anon_sym_U0001f496] = ACTIONS(27),
    [anon_sym_U0001f497] = ACTIONS(27),
    [anon_sym_U0001f498] = ACTIONS(27),
    [anon_sym_U0001f49d] = ACTIONS(27),
    [anon_sym_u2763ufe0f] = ACTIONS(27),
    [anon_sym_U0001f48c] = ACTIONS(27),
    [anon_sym_U0001f49e] = ACTIONS(27),
    [anon_sym_U0001f49f] = ACTIONS(27),
    [anon_sym_U0001faf6] = ACTIONS(29),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(27),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(27),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(27),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(27),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(27),
    [anon_sym_U0001f3e9] = ACTIONS(27),
    [anon_sym_PIPE] = ACTIONS(27),
    [anon_sym_EQ_EQ] = ACTIONS(27),
    [anon_sym_u2248u2248] = ACTIONS(27),
    [anon_sym_TILDE_EQ] = ACTIONS(27),
    [anon_sym_TILDEu2248] = ACTIONS(27),
    [anon_sym_o_TILDE] = ACTIONS(29),
    [anon_sym_TILDEo] = ACTIONS(29),
    [anon_sym_o_TILDE_EQ] = ACTIONS(27),
    [anon_sym_o_TILDEu2248] = ACTIONS(27),
    [anon_sym_TILDEo_EQ] = ACTIONS(27),
    [anon_sym_TILDEou2248] = ACTIONS(27),
    [anon_sym_ou2248] = ACTIONS(27),
    [anon_sym_u2248o] = ACTIONS(27),
    [anon_sym_o_EQ] = ACTIONS(27),
    [anon_sym_EQo] = ACTIONS(27),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [4] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_GT_LPAREN] = ACTIONS(27),
    [anon_sym_RPAREN] = ACTIONS(27),
    [anon_sym_LPAREN] = ACTIONS(29),
    [anon_sym_TILDE] = ACTIONS(29),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(27),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(27),
    [anon_sym_GT_LT] = ACTIONS(29),
    [anon_sym_CARET] = ACTIONS(27),
    [anon_sym_LT] = ACTIONS(29),
    [anon_sym_LBRACK] = ACTIONS(27),
    [anon_sym_DASH] = ACTIONS(27),
    [anon_sym_RBRACK] = ACTIONS(27),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(27),
    [anon_sym_EQ_EQ] = ACTIONS(27),
    [anon_sym_u2248u2248] = ACTIONS(27),
    [anon_sym_TILDE_EQ] = ACTIONS(27),
    [anon_sym_TILDEu2248] = ACTIONS(27),
    [anon_sym_o_TILDE] = ACTIONS(29),
    [anon_sym_TILDEo] = ACTIONS(29),
    [anon_sym_o_TILDE_EQ] = ACTIONS(27),
    [anon_sym_o_TILDEu2248] = ACTIONS(27),
    [anon_sym_TILDEo_EQ] = ACTIONS(27),
    [anon_sym_TILDEou2248] = ACTIONS(27),
    [anon_sym_ou2248] = ACTIONS(27),
    [anon_sym_u2248o] = ACTIONS(27),
    [anon_sym_o_EQ] = ACTIONS(27),
    [anon_sym_EQo] = ACTIONS(27),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [5] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_GT_LPAREN] = ACTIONS(27),
    [anon_sym_RPAREN] = ACTIONS(27),
    [anon_sym_LPAREN] = ACTIONS(29),
    [anon_sym_TILDE] = ACTIONS(29),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(27),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(27),
    [anon_sym_GT_LT] = ACTIONS(29),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(29),
    [anon_sym_LBRACK] = ACTIONS(27),
    [anon_sym_DASH] = ACTIONS(27),
    [anon_sym_RBRACK] = ACTIONS(27),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [6] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_GT_LPAREN] = ACTIONS(41),
    [anon_sym_RPAREN] = ACTIONS(41),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_TILDE] = ACTIONS(46),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(50),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(53),
    [anon_sym_LBRACK] = ACTIONS(56),
    [anon_sym_DASH] = ACTIONS(41),
    [anon_sym_RBRACK] = ACTIONS(41),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [7] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [aux_sym_aquarium_repeat1] = STATE(107),
    [anon_sym_GT_LPAREN] = ACTIONS(59),
    [anon_sym_LPAREN] = ACTIONS(61),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(61),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(61),
    [anon_sym_LBRACK] = ACTIONS(59),
    [anon_sym_DASH] = ACTIONS(63),
    [anon_sym_RBRACK] = ACTIONS(65),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [8] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_DASH] = ACTIONS(71),
    [anon_sym_RBRACK] = ACTIONS(71),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [9] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_GT_LPAREN] = ACTIONS(59),
    [anon_sym_LPAREN] = ACTIONS(61),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(61),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(61),
    [anon_sym_LBRACK] = ACTIONS(59),
    [anon_sym_RBRACK] = ACTIONS(59),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [10] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_TILDE] = ACTIONS(73),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [11] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_TILDE] = ACTIONS(75),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [12] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_RBRACK] = ACTIONS(77),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [13] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_RPAREN] = ACTIONS(79),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [14] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_TILDE] = ACTIONS(81),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [15] = {
    [sym_grilled_fysh] = STATE(6),
    [sym__expression] = STATE(6),
    [sym_aquarium] = STATE(6),
    [sym_fysh_bowl] = STATE(6),
    [sym_positive_ident] = STATE(6),
    [sym_positive_scales] = STATE(6),
    [sym_positive_bones] = STATE(6),
    [sym_negative_ident] = STATE(6),
    [sym_negative_scales] = STATE(6),
    [sym_negative_bones] = STATE(6),
    [sym_binary_expression] = STATE(6),
    [sym_call_expression] = STATE(6),
    [sym_addition] = STATE(24),
    [anon_sym_LPAREN] = ACTIONS(9),
    [anon_sym_TILDE] = ACTIONS(83),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(48),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(48),
    [anon_sym_GT_LT] = ACTIONS(67),
    [anon_sym_CARET] = ACTIONS(31),
    [anon_sym_LT] = ACTIONS(69),
    [anon_sym_LBRACK] = ACTIONS(25),
    [anon_sym_LT_LT] = ACTIONS(33),
    [anon_sym_GT_GT] = ACTIONS(33),
    [anon_sym_AMP] = ACTIONS(33),
    [anon_sym_LT3] = ACTIONS(33),
    [anon_sym_u2661] = ACTIONS(33),
    [anon_sym_LT_SLASH3] = ACTIONS(33),
    [anon_sym_U0001f494] = ACTIONS(33),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(33),
    [anon_sym_u2619] = ACTIONS(33),
    [anon_sym_u2665] = ACTIONS(33),
    [anon_sym_u2763] = ACTIONS(35),
    [anon_sym_u2764] = ACTIONS(35),
    [anon_sym_u2765] = ACTIONS(33),
    [anon_sym_u2766] = ACTIONS(33),
    [anon_sym_u2767] = ACTIONS(33),
    [anon_sym_U0001f394] = ACTIONS(33),
    [anon_sym_U0001fac0] = ACTIONS(33),
    [anon_sym_U0001f5a4] = ACTIONS(33),
    [anon_sym_U0001f499] = ACTIONS(33),
    [anon_sym_U0001fa77] = ACTIONS(33),
    [anon_sym_U0001fa75] = ACTIONS(33),
    [anon_sym_U0001f49a] = ACTIONS(33),
    [anon_sym_U0001f49b] = ACTIONS(33),
    [anon_sym_U0001f49c] = ACTIONS(33),
    [anon_sym_U0001f9e1] = ACTIONS(33),
    [anon_sym_U0001f90d] = ACTIONS(33),
    [anon_sym_U0001f90e] = ACTIONS(33),
    [anon_sym_U0001fa76] = ACTIONS(33),
    [anon_sym_u2764ufe0f] = ACTIONS(35),
    [anon_sym_U0001f493] = ACTIONS(33),
    [anon_sym_U0001f495] = ACTIONS(33),
    [anon_sym_U0001f496] = ACTIONS(33),
    [anon_sym_U0001f497] = ACTIONS(33),
    [anon_sym_U0001f498] = ACTIONS(33),
    [anon_sym_U0001f49d] = ACTIONS(33),
    [anon_sym_u2763ufe0f] = ACTIONS(33),
    [anon_sym_U0001f48c] = ACTIONS(33),
    [anon_sym_U0001f49e] = ACTIONS(33),
    [anon_sym_U0001f49f] = ACTIONS(33),
    [anon_sym_U0001faf6] = ACTIONS(35),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(33),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(33),
    [anon_sym_U0001f3e9] = ACTIONS(33),
    [anon_sym_PIPE] = ACTIONS(31),
    [anon_sym_EQ_EQ] = ACTIONS(37),
    [anon_sym_u2248u2248] = ACTIONS(37),
    [anon_sym_TILDE_EQ] = ACTIONS(37),
    [anon_sym_TILDEu2248] = ACTIONS(37),
    [anon_sym_o_TILDE] = ACTIONS(39),
    [anon_sym_TILDEo] = ACTIONS(39),
    [anon_sym_o_TILDE_EQ] = ACTIONS(37),
    [anon_sym_o_TILDEu2248] = ACTIONS(37),
    [anon_sym_TILDEo_EQ] = ACTIONS(37),
    [anon_sym_TILDEou2248] = ACTIONS(37),
    [anon_sym_ou2248] = ACTIONS(37),
    [anon_sym_u2248o] = ACTIONS(37),
    [anon_sym_o_EQ] = ACTIONS(37),
    [anon_sym_EQo] = ACTIONS(37),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [16] = {
    [anon_sym_GT_LPAREN] = ACTIONS(85),
    [anon_sym_RPAREN] = ACTIONS(85),
    [anon_sym_LPAREN] = ACTIONS(87),
    [anon_sym_TILDE] = ACTIONS(87),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(85),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(85),
    [anon_sym_GT_LT] = ACTIONS(87),
    [anon_sym_CARET] = ACTIONS(85),
    [anon_sym_LT] = ACTIONS(87),
    [anon_sym_u2248] = ACTIONS(87),
    [anon_sym_EQ] = ACTIONS(87),
    [anon_sym_LBRACK] = ACTIONS(85),
    [anon_sym_DASH] = ACTIONS(85),
    [anon_sym_RBRACK] = ACTIONS(85),
    [anon_sym_LT_LT] = ACTIONS(85),
    [anon_sym_GT_GT] = ACTIONS(85),
    [anon_sym_AMP] = ACTIONS(85),
    [anon_sym_LT3] = ACTIONS(85),
    [anon_sym_u2661] = ACTIONS(85),
    [anon_sym_LT_SLASH3] = ACTIONS(85),
    [anon_sym_U0001f494] = ACTIONS(85),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(85),
    [anon_sym_u2619] = ACTIONS(85),
    [anon_sym_u2665] = ACTIONS(85),
    [anon_sym_u2763] = ACTIONS(87),
    [anon_sym_u2764] = ACTIONS(87),
    [anon_sym_u2765] = ACTIONS(85),
    [anon_sym_u2766] = ACTIONS(85),
    [anon_sym_u2767] = ACTIONS(85),
    [anon_sym_U0001f394] = ACTIONS(85),
    [anon_sym_U0001fac0] = ACTIONS(85),
    [anon_sym_U0001f5a4] = ACTIONS(85),
    [anon_sym_U0001f499] = ACTIONS(85),
    [anon_sym_U0001fa77] = ACTIONS(85),
    [anon_sym_U0001fa75] = ACTIONS(85),
    [anon_sym_U0001f49a] = ACTIONS(85),
    [anon_sym_U0001f49b] = ACTIONS(85),
    [anon_sym_U0001f49c] = ACTIONS(85),
    [anon_sym_U0001f9e1] = ACTIONS(85),
    [anon_sym_U0001f90d] = ACTIONS(85),
    [anon_sym_U0001f90e] = ACTIONS(85),
    [anon_sym_U0001fa76] = ACTIONS(85),
    [anon_sym_u2764ufe0f] = ACTIONS(87),
    [anon_sym_U0001f493] = ACTIONS(85),
    [anon_sym_U0001f495] = ACTIONS(85),
    [anon_sym_U0001f496] = ACTIONS(85),
    [anon_sym_U0001f497] = ACTIONS(85),
    [anon_sym_U0001f498] = ACTIONS(85),
    [anon_sym_U0001f49d] = ACTIONS(85),
    [anon_sym_u2763ufe0f] = ACTIONS(85),
    [anon_sym_U0001f48c] = ACTIONS(85),
    [anon_sym_U0001f49e] = ACTIONS(85),
    [anon_sym_U0001f49f] = ACTIONS(85),
    [anon_sym_U0001faf6] = ACTIONS(87),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(85),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(85),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(85),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(85),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(85),
    [anon_sym_U0001f3e9] = ACTIONS(85),
    [anon_sym_PIPE] = ACTIONS(85),
    [anon_sym_EQ_EQ] = ACTIONS(85),
    [anon_sym_u2248u2248] = ACTIONS(85),
    [anon_sym_TILDE_EQ] = ACTIONS(85),
    [anon_sym_TILDEu2248] = ACTIONS(85),
    [anon_sym_o_TILDE] = ACTIONS(87),
    [anon_sym_TILDEo] = ACTIONS(87),
    [anon_sym_o_TILDE_EQ] = ACTIONS(85),
    [anon_sym_o_TILDEu2248] = ACTIONS(85),
    [anon_sym_TILDEo_EQ] = ACTIONS(85),
    [anon_sym_TILDEou2248] = ACTIONS(85),
    [anon_sym_ou2248] = ACTIONS(85),
    [anon_sym_u2248o] = ACTIONS(85),
    [anon_sym_o_EQ] = ACTIONS(85),
    [anon_sym_EQo] = ACTIONS(85),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [17] = {
    [anon_sym_GT_LPAREN] = ACTIONS(89),
    [anon_sym_RPAREN] = ACTIONS(89),
    [anon_sym_LPAREN] = ACTIONS(91),
    [anon_sym_TILDE] = ACTIONS(91),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(89),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(89),
    [anon_sym_GT_LT] = ACTIONS(91),
    [anon_sym_CARET] = ACTIONS(89),
    [anon_sym_LT] = ACTIONS(91),
    [anon_sym_LBRACK] = ACTIONS(89),
    [anon_sym_DASH] = ACTIONS(89),
    [anon_sym_RBRACK] = ACTIONS(89),
    [anon_sym_LT_LT] = ACTIONS(89),
    [anon_sym_GT_GT] = ACTIONS(89),
    [anon_sym_AMP] = ACTIONS(89),
    [anon_sym_LT3] = ACTIONS(89),
    [anon_sym_u2661] = ACTIONS(89),
    [anon_sym_LT_SLASH3] = ACTIONS(89),
    [anon_sym_U0001f494] = ACTIONS(89),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(89),
    [anon_sym_u2619] = ACTIONS(89),
    [anon_sym_u2665] = ACTIONS(89),
    [anon_sym_u2763] = ACTIONS(91),
    [anon_sym_u2764] = ACTIONS(91),
    [anon_sym_u2765] = ACTIONS(89),
    [anon_sym_u2766] = ACTIONS(89),
    [anon_sym_u2767] = ACTIONS(89),
    [anon_sym_U0001f394] = ACTIONS(89),
    [anon_sym_U0001fac0] = ACTIONS(89),
    [anon_sym_U0001f5a4] = ACTIONS(89),
    [anon_sym_U0001f499] = ACTIONS(89),
    [anon_sym_U0001fa77] = ACTIONS(89),
    [anon_sym_U0001fa75] = ACTIONS(89),
    [anon_sym_U0001f49a] = ACTIONS(89),
    [anon_sym_U0001f49b] = ACTIONS(89),
    [anon_sym_U0001f49c] = ACTIONS(89),
    [anon_sym_U0001f9e1] = ACTIONS(89),
    [anon_sym_U0001f90d] = ACTIONS(89),
    [anon_sym_U0001f90e] = ACTIONS(89),
    [anon_sym_U0001fa76] = ACTIONS(89),
    [anon_sym_u2764ufe0f] = ACTIONS(91),
    [anon_sym_U0001f493] = ACTIONS(89),
    [anon_sym_U0001f495] = ACTIONS(89),
    [anon_sym_U0001f496] = ACTIONS(89),
    [anon_sym_U0001f497] = ACTIONS(89),
    [anon_sym_U0001f498] = ACTIONS(89),
    [anon_sym_U0001f49d] = ACTIONS(89),
    [anon_sym_u2763ufe0f] = ACTIONS(89),
    [anon_sym_U0001f48c] = ACTIONS(89),
    [anon_sym_U0001f49e] = ACTIONS(89),
    [anon_sym_U0001f49f] = ACTIONS(89),
    [anon_sym_U0001faf6] = ACTIONS(91),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(89),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(89),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(89),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(89),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(89),
    [anon_sym_U0001f3e9] = ACTIONS(89),
    [anon_sym_PIPE] = ACTIONS(89),
    [anon_sym_EQ_EQ] = ACTIONS(89),
    [anon_sym_u2248u2248] = ACTIONS(89),
    [anon_sym_TILDE_EQ] = ACTIONS(89),
    [anon_sym_TILDEu2248] = ACTIONS(89),
    [anon_sym_o_TILDE] = ACTIONS(91),
    [anon_sym_TILDEo] = ACTIONS(91),
    [anon_sym_o_TILDE_EQ] = ACTIONS(89),
    [anon_sym_o_TILDEu2248] = ACTIONS(89),
    [anon_sym_TILDEo_EQ] = ACTIONS(89),
    [anon_sym_TILDEou2248] = ACTIONS(89),
    [anon_sym_ou2248] = ACTIONS(89),
    [anon_sym_u2248o] = ACTIONS(89),
    [anon_sym_o_EQ] = ACTIONS(89),
    [anon_sym_EQo] = ACTIONS(89),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [18] = {
    [anon_sym_GT_LPAREN] = ACTIONS(93),
    [anon_sym_RPAREN] = ACTIONS(93),
    [anon_sym_LPAREN] = ACTIONS(95),
    [anon_sym_TILDE] = ACTIONS(95),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(93),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(93),
    [anon_sym_GT_LT] = ACTIONS(95),
    [anon_sym_CARET] = ACTIONS(93),
    [anon_sym_LT] = ACTIONS(95),
    [anon_sym_LBRACK] = ACTIONS(93),
    [anon_sym_DASH] = ACTIONS(93),
    [anon_sym_RBRACK] = ACTIONS(93),
    [anon_sym_LT_LT] = ACTIONS(93),
    [anon_sym_GT_GT] = ACTIONS(93),
    [anon_sym_AMP] = ACTIONS(93),
    [anon_sym_LT3] = ACTIONS(93),
    [anon_sym_u2661] = ACTIONS(93),
    [anon_sym_LT_SLASH3] = ACTIONS(93),
    [anon_sym_U0001f494] = ACTIONS(93),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(93),
    [anon_sym_u2619] = ACTIONS(93),
    [anon_sym_u2665] = ACTIONS(93),
    [anon_sym_u2763] = ACTIONS(95),
    [anon_sym_u2764] = ACTIONS(95),
    [anon_sym_u2765] = ACTIONS(93),
    [anon_sym_u2766] = ACTIONS(93),
    [anon_sym_u2767] = ACTIONS(93),
    [anon_sym_U0001f394] = ACTIONS(93),
    [anon_sym_U0001fac0] = ACTIONS(93),
    [anon_sym_U0001f5a4] = ACTIONS(93),
    [anon_sym_U0001f499] = ACTIONS(93),
    [anon_sym_U0001fa77] = ACTIONS(93),
    [anon_sym_U0001fa75] = ACTIONS(93),
    [anon_sym_U0001f49a] = ACTIONS(93),
    [anon_sym_U0001f49b] = ACTIONS(93),
    [anon_sym_U0001f49c] = ACTIONS(93),
    [anon_sym_U0001f9e1] = ACTIONS(93),
    [anon_sym_U0001f90d] = ACTIONS(93),
    [anon_sym_U0001f90e] = ACTIONS(93),
    [anon_sym_U0001fa76] = ACTIONS(93),
    [anon_sym_u2764ufe0f] = ACTIONS(95),
    [anon_sym_U0001f493] = ACTIONS(93),
    [anon_sym_U0001f495] = ACTIONS(93),
    [anon_sym_U0001f496] = ACTIONS(93),
    [anon_sym_U0001f497] = ACTIONS(93),
    [anon_sym_U0001f498] = ACTIONS(93),
    [anon_sym_U0001f49d] = ACTIONS(93),
    [anon_sym_u2763ufe0f] = ACTIONS(93),
    [anon_sym_U0001f48c] = ACTIONS(93),
    [anon_sym_U0001f49e] = ACTIONS(93),
    [anon_sym_U0001f49f] = ACTIONS(93),
    [anon_sym_U0001faf6] = ACTIONS(95),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(93),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(93),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(93),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(93),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(93),
    [anon_sym_U0001f3e9] = ACTIONS(93),
    [anon_sym_PIPE] = ACTIONS(93),
    [anon_sym_EQ_EQ] = ACTIONS(93),
    [anon_sym_u2248u2248] = ACTIONS(93),
    [anon_sym_TILDE_EQ] = ACTIONS(93),
    [anon_sym_TILDEu2248] = ACTIONS(93),
    [anon_sym_o_TILDE] = ACTIONS(95),
    [anon_sym_TILDEo] = ACTIONS(95),
    [anon_sym_o_TILDE_EQ] = ACTIONS(93),
    [anon_sym_o_TILDEu2248] = ACTIONS(93),
    [anon_sym_TILDEo_EQ] = ACTIONS(93),
    [anon_sym_TILDEou2248] = ACTIONS(93),
    [anon_sym_ou2248] = ACTIONS(93),
    [anon_sym_u2248o] = ACTIONS(93),
    [anon_sym_o_EQ] = ACTIONS(93),
    [anon_sym_EQo] = ACTIONS(93),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [19] = {
    [anon_sym_GT_LPAREN] = ACTIONS(97),
    [anon_sym_RPAREN] = ACTIONS(97),
    [anon_sym_LPAREN] = ACTIONS(99),
    [anon_sym_TILDE] = ACTIONS(99),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(97),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(97),
    [anon_sym_GT_LT] = ACTIONS(99),
    [anon_sym_CARET] = ACTIONS(97),
    [anon_sym_LT] = ACTIONS(99),
    [anon_sym_LBRACK] = ACTIONS(97),
    [anon_sym_DASH] = ACTIONS(97),
    [anon_sym_RBRACK] = ACTIONS(97),
    [anon_sym_LT_LT] = ACTIONS(97),
    [anon_sym_GT_GT] = ACTIONS(97),
    [anon_sym_AMP] = ACTIONS(97),
    [anon_sym_LT3] = ACTIONS(97),
    [anon_sym_u2661] = ACTIONS(97),
    [anon_sym_LT_SLASH3] = ACTIONS(97),
    [anon_sym_U0001f494] = ACTIONS(97),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(97),
    [anon_sym_u2619] = ACTIONS(97),
    [anon_sym_u2665] = ACTIONS(97),
    [anon_sym_u2763] = ACTIONS(99),
    [anon_sym_u2764] = ACTIONS(99),
    [anon_sym_u2765] = ACTIONS(97),
    [anon_sym_u2766] = ACTIONS(97),
    [anon_sym_u2767] = ACTIONS(97),
    [anon_sym_U0001f394] = ACTIONS(97),
    [anon_sym_U0001fac0] = ACTIONS(97),
    [anon_sym_U0001f5a4] = ACTIONS(97),
    [anon_sym_U0001f499] = ACTIONS(97),
    [anon_sym_U0001fa77] = ACTIONS(97),
    [anon_sym_U0001fa75] = ACTIONS(97),
    [anon_sym_U0001f49a] = ACTIONS(97),
    [anon_sym_U0001f49b] = ACTIONS(97),
    [anon_sym_U0001f49c] = ACTIONS(97),
    [anon_sym_U0001f9e1] = ACTIONS(97),
    [anon_sym_U0001f90d] = ACTIONS(97),
    [anon_sym_U0001f90e] = ACTIONS(97),
    [anon_sym_U0001fa76] = ACTIONS(97),
    [anon_sym_u2764ufe0f] = ACTIONS(99),
    [anon_sym_U0001f493] = ACTIONS(97),
    [anon_sym_U0001f495] = ACTIONS(97),
    [anon_sym_U0001f496] = ACTIONS(97),
    [anon_sym_U0001f497] = ACTIONS(97),
    [anon_sym_U0001f498] = ACTIONS(97),
    [anon_sym_U0001f49d] = ACTIONS(97),
    [anon_sym_u2763ufe0f] = ACTIONS(97),
    [anon_sym_U0001f48c] = ACTIONS(97),
    [anon_sym_U0001f49e] = ACTIONS(97),
    [anon_sym_U0001f49f] = ACTIONS(97),
    [anon_sym_U0001faf6] = ACTIONS(99),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(97),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(97),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(97),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(97),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(97),
    [anon_sym_U0001f3e9] = ACTIONS(97),
    [anon_sym_PIPE] = ACTIONS(97),
    [anon_sym_EQ_EQ] = ACTIONS(97),
    [anon_sym_u2248u2248] = ACTIONS(97),
    [anon_sym_TILDE_EQ] = ACTIONS(97),
    [anon_sym_TILDEu2248] = ACTIONS(97),
    [anon_sym_o_TILDE] = ACTIONS(99),
    [anon_sym_TILDEo] = ACTIONS(99),
    [anon_sym_o_TILDE_EQ] = ACTIONS(97),
    [anon_sym_o_TILDEu2248] = ACTIONS(97),
    [anon_sym_TILDEo_EQ] = ACTIONS(97),
    [anon_sym_TILDEou2248] = ACTIONS(97),
    [anon_sym_ou2248] = ACTIONS(97),
    [anon_sym_u2248o] = ACTIONS(97),
    [anon_sym_o_EQ] = ACTIONS(97),
    [anon_sym_EQo] = ACTIONS(97),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [20] = {
    [anon_sym_GT_LPAREN] = ACTIONS(101),
    [anon_sym_RPAREN] = ACTIONS(101),
    [anon_sym_LPAREN] = ACTIONS(103),
    [anon_sym_TILDE] = ACTIONS(103),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(101),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(101),
    [anon_sym_GT_LT] = ACTIONS(103),
    [anon_sym_CARET] = ACTIONS(101),
    [anon_sym_LT] = ACTIONS(103),
    [anon_sym_LBRACK] = ACTIONS(101),
    [anon_sym_DASH] = ACTIONS(101),
    [anon_sym_RBRACK] = ACTIONS(101),
    [anon_sym_LT_LT] = ACTIONS(101),
    [anon_sym_GT_GT] = ACTIONS(101),
    [anon_sym_AMP] = ACTIONS(101),
    [anon_sym_LT3] = ACTIONS(101),
    [anon_sym_u2661] = ACTIONS(101),
    [anon_sym_LT_SLASH3] = ACTIONS(101),
    [anon_sym_U0001f494] = ACTIONS(101),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(101),
    [anon_sym_u2619] = ACTIONS(101),
    [anon_sym_u2665] = ACTIONS(101),
    [anon_sym_u2763] = ACTIONS(103),
    [anon_sym_u2764] = ACTIONS(103),
    [anon_sym_u2765] = ACTIONS(101),
    [anon_sym_u2766] = ACTIONS(101),
    [anon_sym_u2767] = ACTIONS(101),
    [anon_sym_U0001f394] = ACTIONS(101),
    [anon_sym_U0001fac0] = ACTIONS(101),
    [anon_sym_U0001f5a4] = ACTIONS(101),
    [anon_sym_U0001f499] = ACTIONS(101),
    [anon_sym_U0001fa77] = ACTIONS(101),
    [anon_sym_U0001fa75] = ACTIONS(101),
    [anon_sym_U0001f49a] = ACTIONS(101),
    [anon_sym_U0001f49b] = ACTIONS(101),
    [anon_sym_U0001f49c] = ACTIONS(101),
    [anon_sym_U0001f9e1] = ACTIONS(101),
    [anon_sym_U0001f90d] = ACTIONS(101),
    [anon_sym_U0001f90e] = ACTIONS(101),
    [anon_sym_U0001fa76] = ACTIONS(101),
    [anon_sym_u2764ufe0f] = ACTIONS(103),
    [anon_sym_U0001f493] = ACTIONS(101),
    [anon_sym_U0001f495] = ACTIONS(101),
    [anon_sym_U0001f496] = ACTIONS(101),
    [anon_sym_U0001f497] = ACTIONS(101),
    [anon_sym_U0001f498] = ACTIONS(101),
    [anon_sym_U0001f49d] = ACTIONS(101),
    [anon_sym_u2763ufe0f] = ACTIONS(101),
    [anon_sym_U0001f48c] = ACTIONS(101),
    [anon_sym_U0001f49e] = ACTIONS(101),
    [anon_sym_U0001f49f] = ACTIONS(101),
    [anon_sym_U0001faf6] = ACTIONS(103),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(101),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(101),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(101),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(101),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(101),
    [anon_sym_U0001f3e9] = ACTIONS(101),
    [anon_sym_PIPE] = ACTIONS(101),
    [anon_sym_EQ_EQ] = ACTIONS(101),
    [anon_sym_u2248u2248] = ACTIONS(101),
    [anon_sym_TILDE_EQ] = ACTIONS(101),
    [anon_sym_TILDEu2248] = ACTIONS(101),
    [anon_sym_o_TILDE] = ACTIONS(103),
    [anon_sym_TILDEo] = ACTIONS(103),
    [anon_sym_o_TILDE_EQ] = ACTIONS(101),
    [anon_sym_o_TILDEu2248] = ACTIONS(101),
    [anon_sym_TILDEo_EQ] = ACTIONS(101),
    [anon_sym_TILDEou2248] = ACTIONS(101),
    [anon_sym_ou2248] = ACTIONS(101),
    [anon_sym_u2248o] = ACTIONS(101),
    [anon_sym_o_EQ] = ACTIONS(101),
    [anon_sym_EQo] = ACTIONS(101),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [21] = {
    [anon_sym_GT_LPAREN] = ACTIONS(105),
    [anon_sym_RPAREN] = ACTIONS(105),
    [anon_sym_LPAREN] = ACTIONS(107),
    [anon_sym_TILDE] = ACTIONS(107),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(105),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(105),
    [anon_sym_GT_LT] = ACTIONS(107),
    [anon_sym_CARET] = ACTIONS(105),
    [anon_sym_LT] = ACTIONS(107),
    [anon_sym_LBRACK] = ACTIONS(105),
    [anon_sym_DASH] = ACTIONS(105),
    [anon_sym_RBRACK] = ACTIONS(105),
    [anon_sym_LT_LT] = ACTIONS(105),
    [anon_sym_GT_GT] = ACTIONS(105),
    [anon_sym_AMP] = ACTIONS(105),
    [anon_sym_LT3] = ACTIONS(105),
    [anon_sym_u2661] = ACTIONS(105),
    [anon_sym_LT_SLASH3] = ACTIONS(105),
    [anon_sym_U0001f494] = ACTIONS(105),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(105),
    [anon_sym_u2619] = ACTIONS(105),
    [anon_sym_u2665] = ACTIONS(105),
    [anon_sym_u2763] = ACTIONS(107),
    [anon_sym_u2764] = ACTIONS(107),
    [anon_sym_u2765] = ACTIONS(105),
    [anon_sym_u2766] = ACTIONS(105),
    [anon_sym_u2767] = ACTIONS(105),
    [anon_sym_U0001f394] = ACTIONS(105),
    [anon_sym_U0001fac0] = ACTIONS(105),
    [anon_sym_U0001f5a4] = ACTIONS(105),
    [anon_sym_U0001f499] = ACTIONS(105),
    [anon_sym_U0001fa77] = ACTIONS(105),
    [anon_sym_U0001fa75] = ACTIONS(105),
    [anon_sym_U0001f49a] = ACTIONS(105),
    [anon_sym_U0001f49b] = ACTIONS(105),
    [anon_sym_U0001f49c] = ACTIONS(105),
    [anon_sym_U0001f9e1] = ACTIONS(105),
    [anon_sym_U0001f90d] = ACTIONS(105),
    [anon_sym_U0001f90e] = ACTIONS(105),
    [anon_sym_U0001fa76] = ACTIONS(105),
    [anon_sym_u2764ufe0f] = ACTIONS(107),
    [anon_sym_U0001f493] = ACTIONS(105),
    [anon_sym_U0001f495] = ACTIONS(105),
    [anon_sym_U0001f496] = ACTIONS(105),
    [anon_sym_U0001f497] = ACTIONS(105),
    [anon_sym_U0001f498] = ACTIONS(105),
    [anon_sym_U0001f49d] = ACTIONS(105),
    [anon_sym_u2763ufe0f] = ACTIONS(105),
    [anon_sym_U0001f48c] = ACTIONS(105),
    [anon_sym_U0001f49e] = ACTIONS(105),
    [anon_sym_U0001f49f] = ACTIONS(105),
    [anon_sym_U0001faf6] = ACTIONS(107),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(105),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(105),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(105),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(105),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(105),
    [anon_sym_U0001f3e9] = ACTIONS(105),
    [anon_sym_PIPE] = ACTIONS(105),
    [anon_sym_EQ_EQ] = ACTIONS(105),
    [anon_sym_u2248u2248] = ACTIONS(105),
    [anon_sym_TILDE_EQ] = ACTIONS(105),
    [anon_sym_TILDEu2248] = ACTIONS(105),
    [anon_sym_o_TILDE] = ACTIONS(107),
    [anon_sym_TILDEo] = ACTIONS(107),
    [anon_sym_o_TILDE_EQ] = ACTIONS(105),
    [anon_sym_o_TILDEu2248] = ACTIONS(105),
    [anon_sym_TILDEo_EQ] = ACTIONS(105),
    [anon_sym_TILDEou2248] = ACTIONS(105),
    [anon_sym_ou2248] = ACTIONS(105),
    [anon_sym_u2248o] = ACTIONS(105),
    [anon_sym_o_EQ] = ACTIONS(105),
    [anon_sym_EQo] = ACTIONS(105),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [22] = {
    [anon_sym_GT_LPAREN] = ACTIONS(109),
    [anon_sym_RPAREN] = ACTIONS(109),
    [anon_sym_LPAREN] = ACTIONS(111),
    [anon_sym_TILDE] = ACTIONS(111),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(109),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(109),
    [anon_sym_GT_LT] = ACTIONS(111),
    [anon_sym_CARET] = ACTIONS(109),
    [anon_sym_LT] = ACTIONS(111),
    [anon_sym_LBRACK] = ACTIONS(109),
    [anon_sym_DASH] = ACTIONS(109),
    [anon_sym_RBRACK] = ACTIONS(109),
    [anon_sym_LT_LT] = ACTIONS(109),
    [anon_sym_GT_GT] = ACTIONS(109),
    [anon_sym_AMP] = ACTIONS(109),
    [anon_sym_LT3] = ACTIONS(109),
    [anon_sym_u2661] = ACTIONS(109),
    [anon_sym_LT_SLASH3] = ACTIONS(109),
    [anon_sym_U0001f494] = ACTIONS(109),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(109),
    [anon_sym_u2619] = ACTIONS(109),
    [anon_sym_u2665] = ACTIONS(109),
    [anon_sym_u2763] = ACTIONS(111),
    [anon_sym_u2764] = ACTIONS(111),
    [anon_sym_u2765] = ACTIONS(109),
    [anon_sym_u2766] = ACTIONS(109),
    [anon_sym_u2767] = ACTIONS(109),
    [anon_sym_U0001f394] = ACTIONS(109),
    [anon_sym_U0001fac0] = ACTIONS(109),
    [anon_sym_U0001f5a4] = ACTIONS(109),
    [anon_sym_U0001f499] = ACTIONS(109),
    [anon_sym_U0001fa77] = ACTIONS(109),
    [anon_sym_U0001fa75] = ACTIONS(109),
    [anon_sym_U0001f49a] = ACTIONS(109),
    [anon_sym_U0001f49b] = ACTIONS(109),
    [anon_sym_U0001f49c] = ACTIONS(109),
    [anon_sym_U0001f9e1] = ACTIONS(109),
    [anon_sym_U0001f90d] = ACTIONS(109),
    [anon_sym_U0001f90e] = ACTIONS(109),
    [anon_sym_U0001fa76] = ACTIONS(109),
    [anon_sym_u2764ufe0f] = ACTIONS(111),
    [anon_sym_U0001f493] = ACTIONS(109),
    [anon_sym_U0001f495] = ACTIONS(109),
    [anon_sym_U0001f496] = ACTIONS(109),
    [anon_sym_U0001f497] = ACTIONS(109),
    [anon_sym_U0001f498] = ACTIONS(109),
    [anon_sym_U0001f49d] = ACTIONS(109),
    [anon_sym_u2763ufe0f] = ACTIONS(109),
    [anon_sym_U0001f48c] = ACTIONS(109),
    [anon_sym_U0001f49e] = ACTIONS(109),
    [anon_sym_U0001f49f] = ACTIONS(109),
    [anon_sym_U0001faf6] = ACTIONS(111),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(109),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(109),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(109),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(109),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(109),
    [anon_sym_U0001f3e9] = ACTIONS(109),
    [anon_sym_PIPE] = ACTIONS(109),
    [anon_sym_EQ_EQ] = ACTIONS(109),
    [anon_sym_u2248u2248] = ACTIONS(109),
    [anon_sym_TILDE_EQ] = ACTIONS(109),
    [anon_sym_TILDEu2248] = ACTIONS(109),
    [anon_sym_o_TILDE] = ACTIONS(111),
    [anon_sym_TILDEo] = ACTIONS(111),
    [anon_sym_o_TILDE_EQ] = ACTIONS(109),
    [anon_sym_o_TILDEu2248] = ACTIONS(109),
    [anon_sym_TILDEo_EQ] = ACTIONS(109),
    [anon_sym_TILDEou2248] = ACTIONS(109),
    [anon_sym_ou2248] = ACTIONS(109),
    [anon_sym_u2248o] = ACTIONS(109),
    [anon_sym_o_EQ] = ACTIONS(109),
    [anon_sym_EQo] = ACTIONS(109),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [23] = {
    [anon_sym_GT_LPAREN] = ACTIONS(113),
    [anon_sym_RPAREN] = ACTIONS(113),
    [anon_sym_LPAREN] = ACTIONS(115),
    [anon_sym_TILDE] = ACTIONS(115),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(113),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(113),
    [anon_sym_GT_LT] = ACTIONS(115),
    [anon_sym_CARET] = ACTIONS(113),
    [anon_sym_LT] = ACTIONS(115),
    [anon_sym_LBRACK] = ACTIONS(113),
    [anon_sym_DASH] = ACTIONS(113),
    [anon_sym_RBRACK] = ACTIONS(113),
    [anon_sym_LT_LT] = ACTIONS(113),
    [anon_sym_GT_GT] = ACTIONS(113),
    [anon_sym_AMP] = ACTIONS(113),
    [anon_sym_LT3] = ACTIONS(113),
    [anon_sym_u2661] = ACTIONS(113),
    [anon_sym_LT_SLASH3] = ACTIONS(113),
    [anon_sym_U0001f494] = ACTIONS(113),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(113),
    [anon_sym_u2619] = ACTIONS(113),
    [anon_sym_u2665] = ACTIONS(113),
    [anon_sym_u2763] = ACTIONS(115),
    [anon_sym_u2764] = ACTIONS(115),
    [anon_sym_u2765] = ACTIONS(113),
    [anon_sym_u2766] = ACTIONS(113),
    [anon_sym_u2767] = ACTIONS(113),
    [anon_sym_U0001f394] = ACTIONS(113),
    [anon_sym_U0001fac0] = ACTIONS(113),
    [anon_sym_U0001f5a4] = ACTIONS(113),
    [anon_sym_U0001f499] = ACTIONS(113),
    [anon_sym_U0001fa77] = ACTIONS(113),
    [anon_sym_U0001fa75] = ACTIONS(113),
    [anon_sym_U0001f49a] = ACTIONS(113),
    [anon_sym_U0001f49b] = ACTIONS(113),
    [anon_sym_U0001f49c] = ACTIONS(113),
    [anon_sym_U0001f9e1] = ACTIONS(113),
    [anon_sym_U0001f90d] = ACTIONS(113),
    [anon_sym_U0001f90e] = ACTIONS(113),
    [anon_sym_U0001fa76] = ACTIONS(113),
    [anon_sym_u2764ufe0f] = ACTIONS(115),
    [anon_sym_U0001f493] = ACTIONS(113),
    [anon_sym_U0001f495] = ACTIONS(113),
    [anon_sym_U0001f496] = ACTIONS(113),
    [anon_sym_U0001f497] = ACTIONS(113),
    [anon_sym_U0001f498] = ACTIONS(113),
    [anon_sym_U0001f49d] = ACTIONS(113),
    [anon_sym_u2763ufe0f] = ACTIONS(113),
    [anon_sym_U0001f48c] = ACTIONS(113),
    [anon_sym_U0001f49e] = ACTIONS(113),
    [anon_sym_U0001f49f] = ACTIONS(113),
    [anon_sym_U0001faf6] = ACTIONS(115),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(113),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(113),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(113),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(113),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(113),
    [anon_sym_U0001f3e9] = ACTIONS(113),
    [anon_sym_PIPE] = ACTIONS(113),
    [anon_sym_EQ_EQ] = ACTIONS(113),
    [anon_sym_u2248u2248] = ACTIONS(113),
    [anon_sym_TILDE_EQ] = ACTIONS(113),
    [anon_sym_TILDEu2248] = ACTIONS(113),
    [anon_sym_o_TILDE] = ACTIONS(115),
    [anon_sym_TILDEo] = ACTIONS(115),
    [anon_sym_o_TILDE_EQ] = ACTIONS(113),
    [anon_sym_o_TILDEu2248] = ACTIONS(113),
    [anon_sym_TILDEo_EQ] = ACTIONS(113),
    [anon_sym_TILDEou2248] = ACTIONS(113),
    [anon_sym_ou2248] = ACTIONS(113),
    [anon_sym_u2248o] = ACTIONS(113),
    [anon_sym_o_EQ] = ACTIONS(113),
    [anon_sym_EQo] = ACTIONS(113),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [24] = {
    [anon_sym_GT_LPAREN] = ACTIONS(117),
    [anon_sym_RPAREN] = ACTIONS(117),
    [anon_sym_LPAREN] = ACTIONS(119),
    [anon_sym_TILDE] = ACTIONS(119),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(117),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(117),
    [anon_sym_GT_LT] = ACTIONS(119),
    [anon_sym_CARET] = ACTIONS(117),
    [anon_sym_LT] = ACTIONS(119),
    [anon_sym_LBRACK] = ACTIONS(117),
    [anon_sym_DASH] = ACTIONS(117),
    [anon_sym_RBRACK] = ACTIONS(117),
    [anon_sym_LT_LT] = ACTIONS(117),
    [anon_sym_GT_GT] = ACTIONS(117),
    [anon_sym_AMP] = ACTIONS(117),
    [anon_sym_LT3] = ACTIONS(117),
    [anon_sym_u2661] = ACTIONS(117),
    [anon_sym_LT_SLASH3] = ACTIONS(117),
    [anon_sym_U0001f494] = ACTIONS(117),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(117),
    [anon_sym_u2619] = ACTIONS(117),
    [anon_sym_u2665] = ACTIONS(117),
    [anon_sym_u2763] = ACTIONS(119),
    [anon_sym_u2764] = ACTIONS(119),
    [anon_sym_u2765] = ACTIONS(117),
    [anon_sym_u2766] = ACTIONS(117),
    [anon_sym_u2767] = ACTIONS(117),
    [anon_sym_U0001f394] = ACTIONS(117),
    [anon_sym_U0001fac0] = ACTIONS(117),
    [anon_sym_U0001f5a4] = ACTIONS(117),
    [anon_sym_U0001f499] = ACTIONS(117),
    [anon_sym_U0001fa77] = ACTIONS(117),
    [anon_sym_U0001fa75] = ACTIONS(117),
    [anon_sym_U0001f49a] = ACTIONS(117),
    [anon_sym_U0001f49b] = ACTIONS(117),
    [anon_sym_U0001f49c] = ACTIONS(117),
    [anon_sym_U0001f9e1] = ACTIONS(117),
    [anon_sym_U0001f90d] = ACTIONS(117),
    [anon_sym_U0001f90e] = ACTIONS(117),
    [anon_sym_U0001fa76] = ACTIONS(117),
    [anon_sym_u2764ufe0f] = ACTIONS(119),
    [anon_sym_U0001f493] = ACTIONS(117),
    [anon_sym_U0001f495] = ACTIONS(117),
    [anon_sym_U0001f496] = ACTIONS(117),
    [anon_sym_U0001f497] = ACTIONS(117),
    [anon_sym_U0001f498] = ACTIONS(117),
    [anon_sym_U0001f49d] = ACTIONS(117),
    [anon_sym_u2763ufe0f] = ACTIONS(117),
    [anon_sym_U0001f48c] = ACTIONS(117),
    [anon_sym_U0001f49e] = ACTIONS(117),
    [anon_sym_U0001f49f] = ACTIONS(117),
    [anon_sym_U0001faf6] = ACTIONS(119),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(117),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(117),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(117),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(117),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(117),
    [anon_sym_U0001f3e9] = ACTIONS(117),
    [anon_sym_PIPE] = ACTIONS(117),
    [anon_sym_EQ_EQ] = ACTIONS(117),
    [anon_sym_u2248u2248] = ACTIONS(117),
    [anon_sym_TILDE_EQ] = ACTIONS(117),
    [anon_sym_TILDEu2248] = ACTIONS(117),
    [anon_sym_o_TILDE] = ACTIONS(119),
    [anon_sym_TILDEo] = ACTIONS(119),
    [anon_sym_o_TILDE_EQ] = ACTIONS(117),
    [anon_sym_o_TILDEu2248] = ACTIONS(117),
    [anon_sym_TILDEo_EQ] = ACTIONS(117),
    [anon_sym_TILDEou2248] = ACTIONS(117),
    [anon_sym_ou2248] = ACTIONS(117),
    [anon_sym_u2248o] = ACTIONS(117),
    [anon_sym_o_EQ] = ACTIONS(117),
    [anon_sym_EQo] = ACTIONS(117),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [25] = {
    [anon_sym_GT_LPAREN] = ACTIONS(121),
    [anon_sym_RPAREN] = ACTIONS(121),
    [anon_sym_LPAREN] = ACTIONS(123),
    [anon_sym_TILDE] = ACTIONS(123),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(121),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(121),
    [anon_sym_GT_LT] = ACTIONS(123),
    [anon_sym_CARET] = ACTIONS(121),
    [anon_sym_LT] = ACTIONS(123),
    [anon_sym_LBRACK] = ACTIONS(121),
    [anon_sym_DASH] = ACTIONS(121),
    [anon_sym_RBRACK] = ACTIONS(121),
    [anon_sym_LT_LT] = ACTIONS(121),
    [anon_sym_GT_GT] = ACTIONS(121),
    [anon_sym_AMP] = ACTIONS(121),
    [anon_sym_LT3] = ACTIONS(121),
    [anon_sym_u2661] = ACTIONS(121),
    [anon_sym_LT_SLASH3] = ACTIONS(121),
    [anon_sym_U0001f494] = ACTIONS(121),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(121),
    [anon_sym_u2619] = ACTIONS(121),
    [anon_sym_u2665] = ACTIONS(121),
    [anon_sym_u2763] = ACTIONS(123),
    [anon_sym_u2764] = ACTIONS(123),
    [anon_sym_u2765] = ACTIONS(121),
    [anon_sym_u2766] = ACTIONS(121),
    [anon_sym_u2767] = ACTIONS(121),
    [anon_sym_U0001f394] = ACTIONS(121),
    [anon_sym_U0001fac0] = ACTIONS(121),
    [anon_sym_U0001f5a4] = ACTIONS(121),
    [anon_sym_U0001f499] = ACTIONS(121),
    [anon_sym_U0001fa77] = ACTIONS(121),
    [anon_sym_U0001fa75] = ACTIONS(121),
    [anon_sym_U0001f49a] = ACTIONS(121),
    [anon_sym_U0001f49b] = ACTIONS(121),
    [anon_sym_U0001f49c] = ACTIONS(121),
    [anon_sym_U0001f9e1] = ACTIONS(121),
    [anon_sym_U0001f90d] = ACTIONS(121),
    [anon_sym_U0001f90e] = ACTIONS(121),
    [anon_sym_U0001fa76] = ACTIONS(121),
    [anon_sym_u2764ufe0f] = ACTIONS(123),
    [anon_sym_U0001f493] = ACTIONS(121),
    [anon_sym_U0001f495] = ACTIONS(121),
    [anon_sym_U0001f496] = ACTIONS(121),
    [anon_sym_U0001f497] = ACTIONS(121),
    [anon_sym_U0001f498] = ACTIONS(121),
    [anon_sym_U0001f49d] = ACTIONS(121),
    [anon_sym_u2763ufe0f] = ACTIONS(121),
    [anon_sym_U0001f48c] = ACTIONS(121),
    [anon_sym_U0001f49e] = ACTIONS(121),
    [anon_sym_U0001f49f] = ACTIONS(121),
    [anon_sym_U0001faf6] = ACTIONS(123),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(121),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(121),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(121),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(121),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(121),
    [anon_sym_U0001f3e9] = ACTIONS(121),
    [anon_sym_PIPE] = ACTIONS(121),
    [anon_sym_EQ_EQ] = ACTIONS(121),
    [anon_sym_u2248u2248] = ACTIONS(121),
    [anon_sym_TILDE_EQ] = ACTIONS(121),
    [anon_sym_TILDEu2248] = ACTIONS(121),
    [anon_sym_o_TILDE] = ACTIONS(123),
    [anon_sym_TILDEo] = ACTIONS(123),
    [anon_sym_o_TILDE_EQ] = ACTIONS(121),
    [anon_sym_o_TILDEu2248] = ACTIONS(121),
    [anon_sym_TILDEo_EQ] = ACTIONS(121),
    [anon_sym_TILDEou2248] = ACTIONS(121),
    [anon_sym_ou2248] = ACTIONS(121),
    [anon_sym_u2248o] = ACTIONS(121),
    [anon_sym_o_EQ] = ACTIONS(121),
    [anon_sym_EQo] = ACTIONS(121),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [26] = {
    [anon_sym_GT_LPAREN] = ACTIONS(125),
    [anon_sym_RPAREN] = ACTIONS(125),
    [anon_sym_LPAREN] = ACTIONS(127),
    [anon_sym_TILDE] = ACTIONS(127),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(125),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(125),
    [anon_sym_GT_LT] = ACTIONS(127),
    [anon_sym_CARET] = ACTIONS(125),
    [anon_sym_LT] = ACTIONS(127),
    [anon_sym_LBRACK] = ACTIONS(125),
    [anon_sym_DASH] = ACTIONS(125),
    [anon_sym_RBRACK] = ACTIONS(125),
    [anon_sym_LT_LT] = ACTIONS(125),
    [anon_sym_GT_GT] = ACTIONS(125),
    [anon_sym_AMP] = ACTIONS(125),
    [anon_sym_LT3] = ACTIONS(125),
    [anon_sym_u2661] = ACTIONS(125),
    [anon_sym_LT_SLASH3] = ACTIONS(125),
    [anon_sym_U0001f494] = ACTIONS(125),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(125),
    [anon_sym_u2619] = ACTIONS(125),
    [anon_sym_u2665] = ACTIONS(125),
    [anon_sym_u2763] = ACTIONS(127),
    [anon_sym_u2764] = ACTIONS(127),
    [anon_sym_u2765] = ACTIONS(125),
    [anon_sym_u2766] = ACTIONS(125),
    [anon_sym_u2767] = ACTIONS(125),
    [anon_sym_U0001f394] = ACTIONS(125),
    [anon_sym_U0001fac0] = ACTIONS(125),
    [anon_sym_U0001f5a4] = ACTIONS(125),
    [anon_sym_U0001f499] = ACTIONS(125),
    [anon_sym_U0001fa77] = ACTIONS(125),
    [anon_sym_U0001fa75] = ACTIONS(125),
    [anon_sym_U0001f49a] = ACTIONS(125),
    [anon_sym_U0001f49b] = ACTIONS(125),
    [anon_sym_U0001f49c] = ACTIONS(125),
    [anon_sym_U0001f9e1] = ACTIONS(125),
    [anon_sym_U0001f90d] = ACTIONS(125),
    [anon_sym_U0001f90e] = ACTIONS(125),
    [anon_sym_U0001fa76] = ACTIONS(125),
    [anon_sym_u2764ufe0f] = ACTIONS(127),
    [anon_sym_U0001f493] = ACTIONS(125),
    [anon_sym_U0001f495] = ACTIONS(125),
    [anon_sym_U0001f496] = ACTIONS(125),
    [anon_sym_U0001f497] = ACTIONS(125),
    [anon_sym_U0001f498] = ACTIONS(125),
    [anon_sym_U0001f49d] = ACTIONS(125),
    [anon_sym_u2763ufe0f] = ACTIONS(125),
    [anon_sym_U0001f48c] = ACTIONS(125),
    [anon_sym_U0001f49e] = ACTIONS(125),
    [anon_sym_U0001f49f] = ACTIONS(125),
    [anon_sym_U0001faf6] = ACTIONS(127),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(125),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(125),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(125),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(125),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(125),
    [anon_sym_U0001f3e9] = ACTIONS(125),
    [anon_sym_PIPE] = ACTIONS(125),
    [anon_sym_EQ_EQ] = ACTIONS(125),
    [anon_sym_u2248u2248] = ACTIONS(125),
    [anon_sym_TILDE_EQ] = ACTIONS(125),
    [anon_sym_TILDEu2248] = ACTIONS(125),
    [anon_sym_o_TILDE] = ACTIONS(127),
    [anon_sym_TILDEo] = ACTIONS(127),
    [anon_sym_o_TILDE_EQ] = ACTIONS(125),
    [anon_sym_o_TILDEu2248] = ACTIONS(125),
    [anon_sym_TILDEo_EQ] = ACTIONS(125),
    [anon_sym_TILDEou2248] = ACTIONS(125),
    [anon_sym_ou2248] = ACTIONS(125),
    [anon_sym_u2248o] = ACTIONS(125),
    [anon_sym_o_EQ] = ACTIONS(125),
    [anon_sym_EQo] = ACTIONS(125),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [27] = {
    [anon_sym_GT_LPAREN] = ACTIONS(129),
    [anon_sym_RPAREN] = ACTIONS(129),
    [anon_sym_LPAREN] = ACTIONS(131),
    [anon_sym_TILDE] = ACTIONS(131),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(129),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(129),
    [anon_sym_GT_LT] = ACTIONS(131),
    [anon_sym_CARET] = ACTIONS(129),
    [anon_sym_LT] = ACTIONS(131),
    [anon_sym_LBRACK] = ACTIONS(129),
    [anon_sym_DASH] = ACTIONS(129),
    [anon_sym_RBRACK] = ACTIONS(129),
    [anon_sym_LT_LT] = ACTIONS(129),
    [anon_sym_GT_GT] = ACTIONS(129),
    [anon_sym_AMP] = ACTIONS(129),
    [anon_sym_LT3] = ACTIONS(129),
    [anon_sym_u2661] = ACTIONS(129),
    [anon_sym_LT_SLASH3] = ACTIONS(129),
    [anon_sym_U0001f494] = ACTIONS(129),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(129),
    [anon_sym_u2619] = ACTIONS(129),
    [anon_sym_u2665] = ACTIONS(129),
    [anon_sym_u2763] = ACTIONS(131),
    [anon_sym_u2764] = ACTIONS(131),
    [anon_sym_u2765] = ACTIONS(129),
    [anon_sym_u2766] = ACTIONS(129),
    [anon_sym_u2767] = ACTIONS(129),
    [anon_sym_U0001f394] = ACTIONS(129),
    [anon_sym_U0001fac0] = ACTIONS(129),
    [anon_sym_U0001f5a4] = ACTIONS(129),
    [anon_sym_U0001f499] = ACTIONS(129),
    [anon_sym_U0001fa77] = ACTIONS(129),
    [anon_sym_U0001fa75] = ACTIONS(129),
    [anon_sym_U0001f49a] = ACTIONS(129),
    [anon_sym_U0001f49b] = ACTIONS(129),
    [anon_sym_U0001f49c] = ACTIONS(129),
    [anon_sym_U0001f9e1] = ACTIONS(129),
    [anon_sym_U0001f90d] = ACTIONS(129),
    [anon_sym_U0001f90e] = ACTIONS(129),
    [anon_sym_U0001fa76] = ACTIONS(129),
    [anon_sym_u2764ufe0f] = ACTIONS(131),
    [anon_sym_U0001f493] = ACTIONS(129),
    [anon_sym_U0001f495] = ACTIONS(129),
    [anon_sym_U0001f496] = ACTIONS(129),
    [anon_sym_U0001f497] = ACTIONS(129),
    [anon_sym_U0001f498] = ACTIONS(129),
    [anon_sym_U0001f49d] = ACTIONS(129),
    [anon_sym_u2763ufe0f] = ACTIONS(129),
    [anon_sym_U0001f48c] = ACTIONS(129),
    [anon_sym_U0001f49e] = ACTIONS(129),
    [anon_sym_U0001f49f] = ACTIONS(129),
    [anon_sym_U0001faf6] = ACTIONS(131),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(129),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(129),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(129),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(129),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(129),
    [anon_sym_U0001f3e9] = ACTIONS(129),
    [anon_sym_PIPE] = ACTIONS(129),
    [anon_sym_EQ_EQ] = ACTIONS(129),
    [anon_sym_u2248u2248] = ACTIONS(129),
    [anon_sym_TILDE_EQ] = ACTIONS(129),
    [anon_sym_TILDEu2248] = ACTIONS(129),
    [anon_sym_o_TILDE] = ACTIONS(131),
    [anon_sym_TILDEo] = ACTIONS(131),
    [anon_sym_o_TILDE_EQ] = ACTIONS(129),
    [anon_sym_o_TILDEu2248] = ACTIONS(129),
    [anon_sym_TILDEo_EQ] = ACTIONS(129),
    [anon_sym_TILDEou2248] = ACTIONS(129),
    [anon_sym_ou2248] = ACTIONS(129),
    [anon_sym_u2248o] = ACTIONS(129),
    [anon_sym_o_EQ] = ACTIONS(129),
    [anon_sym_EQo] = ACTIONS(129),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [28] = {
    [anon_sym_GT_LPAREN] = ACTIONS(133),
    [anon_sym_RPAREN] = ACTIONS(133),
    [anon_sym_LPAREN] = ACTIONS(135),
    [anon_sym_TILDE] = ACTIONS(135),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(133),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(133),
    [anon_sym_GT_LT] = ACTIONS(135),
    [anon_sym_CARET] = ACTIONS(133),
    [anon_sym_LT] = ACTIONS(135),
    [anon_sym_LBRACK] = ACTIONS(133),
    [anon_sym_DASH] = ACTIONS(133),
    [anon_sym_RBRACK] = ACTIONS(133),
    [anon_sym_LT_LT] = ACTIONS(133),
    [anon_sym_GT_GT] = ACTIONS(133),
    [anon_sym_AMP] = ACTIONS(133),
    [anon_sym_LT3] = ACTIONS(133),
    [anon_sym_u2661] = ACTIONS(133),
    [anon_sym_LT_SLASH3] = ACTIONS(133),
    [anon_sym_U0001f494] = ACTIONS(133),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(133),
    [anon_sym_u2619] = ACTIONS(133),
    [anon_sym_u2665] = ACTIONS(133),
    [anon_sym_u2763] = ACTIONS(135),
    [anon_sym_u2764] = ACTIONS(135),
    [anon_sym_u2765] = ACTIONS(133),
    [anon_sym_u2766] = ACTIONS(133),
    [anon_sym_u2767] = ACTIONS(133),
    [anon_sym_U0001f394] = ACTIONS(133),
    [anon_sym_U0001fac0] = ACTIONS(133),
    [anon_sym_U0001f5a4] = ACTIONS(133),
    [anon_sym_U0001f499] = ACTIONS(133),
    [anon_sym_U0001fa77] = ACTIONS(133),
    [anon_sym_U0001fa75] = ACTIONS(133),
    [anon_sym_U0001f49a] = ACTIONS(133),
    [anon_sym_U0001f49b] = ACTIONS(133),
    [anon_sym_U0001f49c] = ACTIONS(133),
    [anon_sym_U0001f9e1] = ACTIONS(133),
    [anon_sym_U0001f90d] = ACTIONS(133),
    [anon_sym_U0001f90e] = ACTIONS(133),
    [anon_sym_U0001fa76] = ACTIONS(133),
    [anon_sym_u2764ufe0f] = ACTIONS(135),
    [anon_sym_U0001f493] = ACTIONS(133),
    [anon_sym_U0001f495] = ACTIONS(133),
    [anon_sym_U0001f496] = ACTIONS(133),
    [anon_sym_U0001f497] = ACTIONS(133),
    [anon_sym_U0001f498] = ACTIONS(133),
    [anon_sym_U0001f49d] = ACTIONS(133),
    [anon_sym_u2763ufe0f] = ACTIONS(133),
    [anon_sym_U0001f48c] = ACTIONS(133),
    [anon_sym_U0001f49e] = ACTIONS(133),
    [anon_sym_U0001f49f] = ACTIONS(133),
    [anon_sym_U0001faf6] = ACTIONS(135),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(133),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(133),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(133),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(133),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(133),
    [anon_sym_U0001f3e9] = ACTIONS(133),
    [anon_sym_PIPE] = ACTIONS(133),
    [anon_sym_EQ_EQ] = ACTIONS(133),
    [anon_sym_u2248u2248] = ACTIONS(133),
    [anon_sym_TILDE_EQ] = ACTIONS(133),
    [anon_sym_TILDEu2248] = ACTIONS(133),
    [anon_sym_o_TILDE] = ACTIONS(135),
    [anon_sym_TILDEo] = ACTIONS(135),
    [anon_sym_o_TILDE_EQ] = ACTIONS(133),
    [anon_sym_o_TILDEu2248] = ACTIONS(133),
    [anon_sym_TILDEo_EQ] = ACTIONS(133),
    [anon_sym_TILDEou2248] = ACTIONS(133),
    [anon_sym_ou2248] = ACTIONS(133),
    [anon_sym_u2248o] = ACTIONS(133),
    [anon_sym_o_EQ] = ACTIONS(133),
    [anon_sym_EQo] = ACTIONS(133),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [29] = {
    [anon_sym_GT_LPAREN] = ACTIONS(137),
    [anon_sym_RPAREN] = ACTIONS(137),
    [anon_sym_LPAREN] = ACTIONS(139),
    [anon_sym_TILDE] = ACTIONS(139),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(137),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(137),
    [anon_sym_GT_LT] = ACTIONS(139),
    [anon_sym_CARET] = ACTIONS(137),
    [anon_sym_LT] = ACTIONS(139),
    [anon_sym_LBRACK] = ACTIONS(137),
    [anon_sym_DASH] = ACTIONS(137),
    [anon_sym_RBRACK] = ACTIONS(137),
    [anon_sym_LT_LT] = ACTIONS(137),
    [anon_sym_GT_GT] = ACTIONS(137),
    [anon_sym_AMP] = ACTIONS(137),
    [anon_sym_LT3] = ACTIONS(137),
    [anon_sym_u2661] = ACTIONS(137),
    [anon_sym_LT_SLASH3] = ACTIONS(137),
    [anon_sym_U0001f494] = ACTIONS(137),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(137),
    [anon_sym_u2619] = ACTIONS(137),
    [anon_sym_u2665] = ACTIONS(137),
    [anon_sym_u2763] = ACTIONS(139),
    [anon_sym_u2764] = ACTIONS(139),
    [anon_sym_u2765] = ACTIONS(137),
    [anon_sym_u2766] = ACTIONS(137),
    [anon_sym_u2767] = ACTIONS(137),
    [anon_sym_U0001f394] = ACTIONS(137),
    [anon_sym_U0001fac0] = ACTIONS(137),
    [anon_sym_U0001f5a4] = ACTIONS(137),
    [anon_sym_U0001f499] = ACTIONS(137),
    [anon_sym_U0001fa77] = ACTIONS(137),
    [anon_sym_U0001fa75] = ACTIONS(137),
    [anon_sym_U0001f49a] = ACTIONS(137),
    [anon_sym_U0001f49b] = ACTIONS(137),
    [anon_sym_U0001f49c] = ACTIONS(137),
    [anon_sym_U0001f9e1] = ACTIONS(137),
    [anon_sym_U0001f90d] = ACTIONS(137),
    [anon_sym_U0001f90e] = ACTIONS(137),
    [anon_sym_U0001fa76] = ACTIONS(137),
    [anon_sym_u2764ufe0f] = ACTIONS(139),
    [anon_sym_U0001f493] = ACTIONS(137),
    [anon_sym_U0001f495] = ACTIONS(137),
    [anon_sym_U0001f496] = ACTIONS(137),
    [anon_sym_U0001f497] = ACTIONS(137),
    [anon_sym_U0001f498] = ACTIONS(137),
    [anon_sym_U0001f49d] = ACTIONS(137),
    [anon_sym_u2763ufe0f] = ACTIONS(137),
    [anon_sym_U0001f48c] = ACTIONS(137),
    [anon_sym_U0001f49e] = ACTIONS(137),
    [anon_sym_U0001f49f] = ACTIONS(137),
    [anon_sym_U0001faf6] = ACTIONS(139),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(137),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(137),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(137),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(137),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(137),
    [anon_sym_U0001f3e9] = ACTIONS(137),
    [anon_sym_PIPE] = ACTIONS(137),
    [anon_sym_EQ_EQ] = ACTIONS(137),
    [anon_sym_u2248u2248] = ACTIONS(137),
    [anon_sym_TILDE_EQ] = ACTIONS(137),
    [anon_sym_TILDEu2248] = ACTIONS(137),
    [anon_sym_o_TILDE] = ACTIONS(139),
    [anon_sym_TILDEo] = ACTIONS(139),
    [anon_sym_o_TILDE_EQ] = ACTIONS(137),
    [anon_sym_o_TILDEu2248] = ACTIONS(137),
    [anon_sym_TILDEo_EQ] = ACTIONS(137),
    [anon_sym_TILDEou2248] = ACTIONS(137),
    [anon_sym_ou2248] = ACTIONS(137),
    [anon_sym_u2248o] = ACTIONS(137),
    [anon_sym_o_EQ] = ACTIONS(137),
    [anon_sym_EQo] = ACTIONS(137),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [30] = {
    [anon_sym_GT_LPAREN] = ACTIONS(141),
    [anon_sym_RPAREN] = ACTIONS(141),
    [anon_sym_LPAREN] = ACTIONS(143),
    [anon_sym_TILDE] = ACTIONS(143),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(141),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(141),
    [anon_sym_GT_LT] = ACTIONS(143),
    [anon_sym_CARET] = ACTIONS(141),
    [anon_sym_LT] = ACTIONS(143),
    [anon_sym_LBRACK] = ACTIONS(141),
    [anon_sym_DASH] = ACTIONS(141),
    [anon_sym_RBRACK] = ACTIONS(141),
    [anon_sym_LT_LT] = ACTIONS(141),
    [anon_sym_GT_GT] = ACTIONS(141),
    [anon_sym_AMP] = ACTIONS(141),
    [anon_sym_LT3] = ACTIONS(141),
    [anon_sym_u2661] = ACTIONS(141),
    [anon_sym_LT_SLASH3] = ACTIONS(141),
    [anon_sym_U0001f494] = ACTIONS(141),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(141),
    [anon_sym_u2619] = ACTIONS(141),
    [anon_sym_u2665] = ACTIONS(141),
    [anon_sym_u2763] = ACTIONS(143),
    [anon_sym_u2764] = ACTIONS(143),
    [anon_sym_u2765] = ACTIONS(141),
    [anon_sym_u2766] = ACTIONS(141),
    [anon_sym_u2767] = ACTIONS(141),
    [anon_sym_U0001f394] = ACTIONS(141),
    [anon_sym_U0001fac0] = ACTIONS(141),
    [anon_sym_U0001f5a4] = ACTIONS(141),
    [anon_sym_U0001f499] = ACTIONS(141),
    [anon_sym_U0001fa77] = ACTIONS(141),
    [anon_sym_U0001fa75] = ACTIONS(141),
    [anon_sym_U0001f49a] = ACTIONS(141),
    [anon_sym_U0001f49b] = ACTIONS(141),
    [anon_sym_U0001f49c] = ACTIONS(141),
    [anon_sym_U0001f9e1] = ACTIONS(141),
    [anon_sym_U0001f90d] = ACTIONS(141),
    [anon_sym_U0001f90e] = ACTIONS(141),
    [anon_sym_U0001fa76] = ACTIONS(141),
    [anon_sym_u2764ufe0f] = ACTIONS(143),
    [anon_sym_U0001f493] = ACTIONS(141),
    [anon_sym_U0001f495] = ACTIONS(141),
    [anon_sym_U0001f496] = ACTIONS(141),
    [anon_sym_U0001f497] = ACTIONS(141),
    [anon_sym_U0001f498] = ACTIONS(141),
    [anon_sym_U0001f49d] = ACTIONS(141),
    [anon_sym_u2763ufe0f] = ACTIONS(141),
    [anon_sym_U0001f48c] = ACTIONS(141),
    [anon_sym_U0001f49e] = ACTIONS(141),
    [anon_sym_U0001f49f] = ACTIONS(141),
    [anon_sym_U0001faf6] = ACTIONS(143),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(141),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(141),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(141),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(141),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(141),
    [anon_sym_U0001f3e9] = ACTIONS(141),
    [anon_sym_PIPE] = ACTIONS(141),
    [anon_sym_EQ_EQ] = ACTIONS(141),
    [anon_sym_u2248u2248] = ACTIONS(141),
    [anon_sym_TILDE_EQ] = ACTIONS(141),
    [anon_sym_TILDEu2248] = ACTIONS(141),
    [anon_sym_o_TILDE] = ACTIONS(143),
    [anon_sym_TILDEo] = ACTIONS(143),
    [anon_sym_o_TILDE_EQ] = ACTIONS(141),
    [anon_sym_o_TILDEu2248] = ACTIONS(141),
    [anon_sym_TILDEo_EQ] = ACTIONS(141),
    [anon_sym_TILDEou2248] = ACTIONS(141),
    [anon_sym_ou2248] = ACTIONS(141),
    [anon_sym_u2248o] = ACTIONS(141),
    [anon_sym_o_EQ] = ACTIONS(141),
    [anon_sym_EQo] = ACTIONS(141),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [31] = {
    [anon_sym_GT_LPAREN] = ACTIONS(145),
    [anon_sym_RPAREN] = ACTIONS(145),
    [anon_sym_LPAREN] = ACTIONS(147),
    [anon_sym_TILDE] = ACTIONS(147),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(145),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(145),
    [anon_sym_GT_LT] = ACTIONS(147),
    [anon_sym_CARET] = ACTIONS(145),
    [anon_sym_LT] = ACTIONS(147),
    [anon_sym_LBRACK] = ACTIONS(145),
    [anon_sym_DASH] = ACTIONS(145),
    [anon_sym_RBRACK] = ACTIONS(145),
    [anon_sym_LT_LT] = ACTIONS(145),
    [anon_sym_GT_GT] = ACTIONS(145),
    [anon_sym_AMP] = ACTIONS(145),
    [anon_sym_LT3] = ACTIONS(145),
    [anon_sym_u2661] = ACTIONS(145),
    [anon_sym_LT_SLASH3] = ACTIONS(145),
    [anon_sym_U0001f494] = ACTIONS(145),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(145),
    [anon_sym_u2619] = ACTIONS(145),
    [anon_sym_u2665] = ACTIONS(145),
    [anon_sym_u2763] = ACTIONS(147),
    [anon_sym_u2764] = ACTIONS(147),
    [anon_sym_u2765] = ACTIONS(145),
    [anon_sym_u2766] = ACTIONS(145),
    [anon_sym_u2767] = ACTIONS(145),
    [anon_sym_U0001f394] = ACTIONS(145),
    [anon_sym_U0001fac0] = ACTIONS(145),
    [anon_sym_U0001f5a4] = ACTIONS(145),
    [anon_sym_U0001f499] = ACTIONS(145),
    [anon_sym_U0001fa77] = ACTIONS(145),
    [anon_sym_U0001fa75] = ACTIONS(145),
    [anon_sym_U0001f49a] = ACTIONS(145),
    [anon_sym_U0001f49b] = ACTIONS(145),
    [anon_sym_U0001f49c] = ACTIONS(145),
    [anon_sym_U0001f9e1] = ACTIONS(145),
    [anon_sym_U0001f90d] = ACTIONS(145),
    [anon_sym_U0001f90e] = ACTIONS(145),
    [anon_sym_U0001fa76] = ACTIONS(145),
    [anon_sym_u2764ufe0f] = ACTIONS(147),
    [anon_sym_U0001f493] = ACTIONS(145),
    [anon_sym_U0001f495] = ACTIONS(145),
    [anon_sym_U0001f496] = ACTIONS(145),
    [anon_sym_U0001f497] = ACTIONS(145),
    [anon_sym_U0001f498] = ACTIONS(145),
    [anon_sym_U0001f49d] = ACTIONS(145),
    [anon_sym_u2763ufe0f] = ACTIONS(145),
    [anon_sym_U0001f48c] = ACTIONS(145),
    [anon_sym_U0001f49e] = ACTIONS(145),
    [anon_sym_U0001f49f] = ACTIONS(145),
    [anon_sym_U0001faf6] = ACTIONS(147),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(145),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(145),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(145),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(145),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(145),
    [anon_sym_U0001f3e9] = ACTIONS(145),
    [anon_sym_PIPE] = ACTIONS(145),
    [anon_sym_EQ_EQ] = ACTIONS(145),
    [anon_sym_u2248u2248] = ACTIONS(145),
    [anon_sym_TILDE_EQ] = ACTIONS(145),
    [anon_sym_TILDEu2248] = ACTIONS(145),
    [anon_sym_o_TILDE] = ACTIONS(147),
    [anon_sym_TILDEo] = ACTIONS(147),
    [anon_sym_o_TILDE_EQ] = ACTIONS(145),
    [anon_sym_o_TILDEu2248] = ACTIONS(145),
    [anon_sym_TILDEo_EQ] = ACTIONS(145),
    [anon_sym_TILDEou2248] = ACTIONS(145),
    [anon_sym_ou2248] = ACTIONS(145),
    [anon_sym_u2248o] = ACTIONS(145),
    [anon_sym_o_EQ] = ACTIONS(145),
    [anon_sym_EQo] = ACTIONS(145),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [32] = {
    [anon_sym_GT_LPAREN] = ACTIONS(149),
    [anon_sym_RPAREN] = ACTIONS(149),
    [anon_sym_LPAREN] = ACTIONS(151),
    [anon_sym_TILDE] = ACTIONS(151),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(149),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(149),
    [anon_sym_GT_LT] = ACTIONS(151),
    [anon_sym_CARET] = ACTIONS(149),
    [anon_sym_LT] = ACTIONS(151),
    [anon_sym_LBRACK] = ACTIONS(149),
    [anon_sym_DASH] = ACTIONS(149),
    [anon_sym_RBRACK] = ACTIONS(149),
    [anon_sym_LT_LT] = ACTIONS(149),
    [anon_sym_GT_GT] = ACTIONS(149),
    [anon_sym_AMP] = ACTIONS(149),
    [anon_sym_LT3] = ACTIONS(149),
    [anon_sym_u2661] = ACTIONS(149),
    [anon_sym_LT_SLASH3] = ACTIONS(149),
    [anon_sym_U0001f494] = ACTIONS(149),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(149),
    [anon_sym_u2619] = ACTIONS(149),
    [anon_sym_u2665] = ACTIONS(149),
    [anon_sym_u2763] = ACTIONS(151),
    [anon_sym_u2764] = ACTIONS(151),
    [anon_sym_u2765] = ACTIONS(149),
    [anon_sym_u2766] = ACTIONS(149),
    [anon_sym_u2767] = ACTIONS(149),
    [anon_sym_U0001f394] = ACTIONS(149),
    [anon_sym_U0001fac0] = ACTIONS(149),
    [anon_sym_U0001f5a4] = ACTIONS(149),
    [anon_sym_U0001f499] = ACTIONS(149),
    [anon_sym_U0001fa77] = ACTIONS(149),
    [anon_sym_U0001fa75] = ACTIONS(149),
    [anon_sym_U0001f49a] = ACTIONS(149),
    [anon_sym_U0001f49b] = ACTIONS(149),
    [anon_sym_U0001f49c] = ACTIONS(149),
    [anon_sym_U0001f9e1] = ACTIONS(149),
    [anon_sym_U0001f90d] = ACTIONS(149),
    [anon_sym_U0001f90e] = ACTIONS(149),
    [anon_sym_U0001fa76] = ACTIONS(149),
    [anon_sym_u2764ufe0f] = ACTIONS(151),
    [anon_sym_U0001f493] = ACTIONS(149),
    [anon_sym_U0001f495] = ACTIONS(149),
    [anon_sym_U0001f496] = ACTIONS(149),
    [anon_sym_U0001f497] = ACTIONS(149),
    [anon_sym_U0001f498] = ACTIONS(149),
    [anon_sym_U0001f49d] = ACTIONS(149),
    [anon_sym_u2763ufe0f] = ACTIONS(149),
    [anon_sym_U0001f48c] = ACTIONS(149),
    [anon_sym_U0001f49e] = ACTIONS(149),
    [anon_sym_U0001f49f] = ACTIONS(149),
    [anon_sym_U0001faf6] = ACTIONS(151),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(149),
    [anon_sym_U0001f3e9] = ACTIONS(149),
    [anon_sym_PIPE] = ACTIONS(149),
    [anon_sym_EQ_EQ] = ACTIONS(149),
    [anon_sym_u2248u2248] = ACTIONS(149),
    [anon_sym_TILDE_EQ] = ACTIONS(149),
    [anon_sym_TILDEu2248] = ACTIONS(149),
    [anon_sym_o_TILDE] = ACTIONS(151),
    [anon_sym_TILDEo] = ACTIONS(151),
    [anon_sym_o_TILDE_EQ] = ACTIONS(149),
    [anon_sym_o_TILDEu2248] = ACTIONS(149),
    [anon_sym_TILDEo_EQ] = ACTIONS(149),
    [anon_sym_TILDEou2248] = ACTIONS(149),
    [anon_sym_ou2248] = ACTIONS(149),
    [anon_sym_u2248o] = ACTIONS(149),
    [anon_sym_o_EQ] = ACTIONS(149),
    [anon_sym_EQo] = ACTIONS(149),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [33] = {
    [anon_sym_GT_LPAREN] = ACTIONS(153),
    [anon_sym_RPAREN] = ACTIONS(153),
    [anon_sym_LPAREN] = ACTIONS(155),
    [anon_sym_TILDE] = ACTIONS(155),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(153),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(153),
    [anon_sym_GT_LT] = ACTIONS(155),
    [anon_sym_CARET] = ACTIONS(153),
    [anon_sym_LT] = ACTIONS(155),
    [anon_sym_LBRACK] = ACTIONS(153),
    [anon_sym_DASH] = ACTIONS(153),
    [anon_sym_RBRACK] = ACTIONS(153),
    [anon_sym_LT_LT] = ACTIONS(153),
    [anon_sym_GT_GT] = ACTIONS(153),
    [anon_sym_AMP] = ACTIONS(153),
    [anon_sym_LT3] = ACTIONS(153),
    [anon_sym_u2661] = ACTIONS(153),
    [anon_sym_LT_SLASH3] = ACTIONS(153),
    [anon_sym_U0001f494] = ACTIONS(153),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(153),
    [anon_sym_u2619] = ACTIONS(153),
    [anon_sym_u2665] = ACTIONS(153),
    [anon_sym_u2763] = ACTIONS(155),
    [anon_sym_u2764] = ACTIONS(155),
    [anon_sym_u2765] = ACTIONS(153),
    [anon_sym_u2766] = ACTIONS(153),
    [anon_sym_u2767] = ACTIONS(153),
    [anon_sym_U0001f394] = ACTIONS(153),
    [anon_sym_U0001fac0] = ACTIONS(153),
    [anon_sym_U0001f5a4] = ACTIONS(153),
    [anon_sym_U0001f499] = ACTIONS(153),
    [anon_sym_U0001fa77] = ACTIONS(153),
    [anon_sym_U0001fa75] = ACTIONS(153),
    [anon_sym_U0001f49a] = ACTIONS(153),
    [anon_sym_U0001f49b] = ACTIONS(153),
    [anon_sym_U0001f49c] = ACTIONS(153),
    [anon_sym_U0001f9e1] = ACTIONS(153),
    [anon_sym_U0001f90d] = ACTIONS(153),
    [anon_sym_U0001f90e] = ACTIONS(153),
    [anon_sym_U0001fa76] = ACTIONS(153),
    [anon_sym_u2764ufe0f] = ACTIONS(155),
    [anon_sym_U0001f493] = ACTIONS(153),
    [anon_sym_U0001f495] = ACTIONS(153),
    [anon_sym_U0001f496] = ACTIONS(153),
    [anon_sym_U0001f497] = ACTIONS(153),
    [anon_sym_U0001f498] = ACTIONS(153),
    [anon_sym_U0001f49d] = ACTIONS(153),
    [anon_sym_u2763ufe0f] = ACTIONS(153),
    [anon_sym_U0001f48c] = ACTIONS(153),
    [anon_sym_U0001f49e] = ACTIONS(153),
    [anon_sym_U0001f49f] = ACTIONS(153),
    [anon_sym_U0001faf6] = ACTIONS(155),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(153),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(153),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(153),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(153),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(153),
    [anon_sym_U0001f3e9] = ACTIONS(153),
    [anon_sym_PIPE] = ACTIONS(153),
    [anon_sym_EQ_EQ] = ACTIONS(153),
    [anon_sym_u2248u2248] = ACTIONS(153),
    [anon_sym_TILDE_EQ] = ACTIONS(153),
    [anon_sym_TILDEu2248] = ACTIONS(153),
    [anon_sym_o_TILDE] = ACTIONS(155),
    [anon_sym_TILDEo] = ACTIONS(155),
    [anon_sym_o_TILDE_EQ] = ACTIONS(153),
    [anon_sym_o_TILDEu2248] = ACTIONS(153),
    [anon_sym_TILDEo_EQ] = ACTIONS(153),
    [anon_sym_TILDEou2248] = ACTIONS(153),
    [anon_sym_ou2248] = ACTIONS(153),
    [anon_sym_u2248o] = ACTIONS(153),
    [anon_sym_o_EQ] = ACTIONS(153),
    [anon_sym_EQo] = ACTIONS(153),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [34] = {
    [anon_sym_GT_LPAREN] = ACTIONS(157),
    [anon_sym_RPAREN] = ACTIONS(157),
    [anon_sym_LPAREN] = ACTIONS(159),
    [anon_sym_TILDE] = ACTIONS(159),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(157),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(157),
    [anon_sym_GT_LT] = ACTIONS(159),
    [anon_sym_CARET] = ACTIONS(157),
    [anon_sym_LT] = ACTIONS(159),
    [anon_sym_LBRACK] = ACTIONS(157),
    [anon_sym_DASH] = ACTIONS(157),
    [anon_sym_RBRACK] = ACTIONS(157),
    [anon_sym_LT_LT] = ACTIONS(157),
    [anon_sym_GT_GT] = ACTIONS(157),
    [anon_sym_AMP] = ACTIONS(157),
    [anon_sym_LT3] = ACTIONS(157),
    [anon_sym_u2661] = ACTIONS(157),
    [anon_sym_LT_SLASH3] = ACTIONS(157),
    [anon_sym_U0001f494] = ACTIONS(157),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(157),
    [anon_sym_u2619] = ACTIONS(157),
    [anon_sym_u2665] = ACTIONS(157),
    [anon_sym_u2763] = ACTIONS(159),
    [anon_sym_u2764] = ACTIONS(159),
    [anon_sym_u2765] = ACTIONS(157),
    [anon_sym_u2766] = ACTIONS(157),
    [anon_sym_u2767] = ACTIONS(157),
    [anon_sym_U0001f394] = ACTIONS(157),
    [anon_sym_U0001fac0] = ACTIONS(157),
    [anon_sym_U0001f5a4] = ACTIONS(157),
    [anon_sym_U0001f499] = ACTIONS(157),
    [anon_sym_U0001fa77] = ACTIONS(157),
    [anon_sym_U0001fa75] = ACTIONS(157),
    [anon_sym_U0001f49a] = ACTIONS(157),
    [anon_sym_U0001f49b] = ACTIONS(157),
    [anon_sym_U0001f49c] = ACTIONS(157),
    [anon_sym_U0001f9e1] = ACTIONS(157),
    [anon_sym_U0001f90d] = ACTIONS(157),
    [anon_sym_U0001f90e] = ACTIONS(157),
    [anon_sym_U0001fa76] = ACTIONS(157),
    [anon_sym_u2764ufe0f] = ACTIONS(159),
    [anon_sym_U0001f493] = ACTIONS(157),
    [anon_sym_U0001f495] = ACTIONS(157),
    [anon_sym_U0001f496] = ACTIONS(157),
    [anon_sym_U0001f497] = ACTIONS(157),
    [anon_sym_U0001f498] = ACTIONS(157),
    [anon_sym_U0001f49d] = ACTIONS(157),
    [anon_sym_u2763ufe0f] = ACTIONS(157),
    [anon_sym_U0001f48c] = ACTIONS(157),
    [anon_sym_U0001f49e] = ACTIONS(157),
    [anon_sym_U0001f49f] = ACTIONS(157),
    [anon_sym_U0001faf6] = ACTIONS(159),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(157),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(157),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(157),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(157),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(157),
    [anon_sym_U0001f3e9] = ACTIONS(157),
    [anon_sym_PIPE] = ACTIONS(157),
    [anon_sym_EQ_EQ] = ACTIONS(157),
    [anon_sym_u2248u2248] = ACTIONS(157),
    [anon_sym_TILDE_EQ] = ACTIONS(157),
    [anon_sym_TILDEu2248] = ACTIONS(157),
    [anon_sym_o_TILDE] = ACTIONS(159),
    [anon_sym_TILDEo] = ACTIONS(159),
    [anon_sym_o_TILDE_EQ] = ACTIONS(157),
    [anon_sym_o_TILDEu2248] = ACTIONS(157),
    [anon_sym_TILDEo_EQ] = ACTIONS(157),
    [anon_sym_TILDEou2248] = ACTIONS(157),
    [anon_sym_ou2248] = ACTIONS(157),
    [anon_sym_u2248o] = ACTIONS(157),
    [anon_sym_o_EQ] = ACTIONS(157),
    [anon_sym_EQo] = ACTIONS(157),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [35] = {
    [anon_sym_LPAREN] = ACTIONS(161),
    [anon_sym_TILDE] = ACTIONS(161),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(163),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(163),
    [anon_sym_GT_LT] = ACTIONS(161),
    [anon_sym_CARET] = ACTIONS(163),
    [anon_sym_LT] = ACTIONS(161),
    [anon_sym_u2248] = ACTIONS(165),
    [anon_sym_EQ] = ACTIONS(165),
    [anon_sym_LBRACK] = ACTIONS(163),
    [anon_sym_LT_LT] = ACTIONS(163),
    [anon_sym_GT_GT] = ACTIONS(163),
    [anon_sym_AMP] = ACTIONS(163),
    [anon_sym_LT3] = ACTIONS(163),
    [anon_sym_u2661] = ACTIONS(163),
    [anon_sym_LT_SLASH3] = ACTIONS(163),
    [anon_sym_U0001f494] = ACTIONS(163),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(163),
    [anon_sym_u2619] = ACTIONS(163),
    [anon_sym_u2665] = ACTIONS(163),
    [anon_sym_u2763] = ACTIONS(161),
    [anon_sym_u2764] = ACTIONS(161),
    [anon_sym_u2765] = ACTIONS(163),
    [anon_sym_u2766] = ACTIONS(163),
    [anon_sym_u2767] = ACTIONS(163),
    [anon_sym_U0001f394] = ACTIONS(163),
    [anon_sym_U0001fac0] = ACTIONS(163),
    [anon_sym_U0001f5a4] = ACTIONS(163),
    [anon_sym_U0001f499] = ACTIONS(163),
    [anon_sym_U0001fa77] = ACTIONS(163),
    [anon_sym_U0001fa75] = ACTIONS(163),
    [anon_sym_U0001f49a] = ACTIONS(163),
    [anon_sym_U0001f49b] = ACTIONS(163),
    [anon_sym_U0001f49c] = ACTIONS(163),
    [anon_sym_U0001f9e1] = ACTIONS(163),
    [anon_sym_U0001f90d] = ACTIONS(163),
    [anon_sym_U0001f90e] = ACTIONS(163),
    [anon_sym_U0001fa76] = ACTIONS(163),
    [anon_sym_u2764ufe0f] = ACTIONS(161),
    [anon_sym_U0001f493] = ACTIONS(163),
    [anon_sym_U0001f495] = ACTIONS(163),
    [anon_sym_U0001f496] = ACTIONS(163),
    [anon_sym_U0001f497] = ACTIONS(163),
    [anon_sym_U0001f498] = ACTIONS(163),
    [anon_sym_U0001f49d] = ACTIONS(163),
    [anon_sym_u2763ufe0f] = ACTIONS(163),
    [anon_sym_U0001f48c] = ACTIONS(163),
    [anon_sym_U0001f49e] = ACTIONS(163),
    [anon_sym_U0001f49f] = ACTIONS(163),
    [anon_sym_U0001faf6] = ACTIONS(161),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(163),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(163),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(163),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(163),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(163),
    [anon_sym_U0001f3e9] = ACTIONS(163),
    [anon_sym_PIPE] = ACTIONS(163),
    [anon_sym_EQ_EQ] = ACTIONS(163),
    [anon_sym_u2248u2248] = ACTIONS(163),
    [anon_sym_TILDE_EQ] = ACTIONS(163),
    [anon_sym_TILDEu2248] = ACTIONS(163),
    [anon_sym_o_TILDE] = ACTIONS(161),
    [anon_sym_TILDEo] = ACTIONS(161),
    [anon_sym_o_TILDE_EQ] = ACTIONS(163),
    [anon_sym_o_TILDEu2248] = ACTIONS(163),
    [anon_sym_TILDEo_EQ] = ACTIONS(163),
    [anon_sym_TILDEou2248] = ACTIONS(163),
    [anon_sym_ou2248] = ACTIONS(163),
    [anon_sym_u2248o] = ACTIONS(163),
    [anon_sym_o_EQ] = ACTIONS(163),
    [anon_sym_EQo] = ACTIONS(163),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
  [36] = {
    [anon_sym_LPAREN] = ACTIONS(151),
    [anon_sym_TILDE] = ACTIONS(151),
    [anon_sym_LPAREN_PLUSo] = ACTIONS(149),
    [anon_sym_o_PLUS_RPAREN] = ACTIONS(149),
    [anon_sym_GT_LT] = ACTIONS(151),
    [anon_sym_CARET] = ACTIONS(149),
    [anon_sym_LT] = ACTIONS(167),
    [anon_sym_LBRACK] = ACTIONS(149),
    [anon_sym_LT_LT] = ACTIONS(149),
    [anon_sym_GT_GT] = ACTIONS(149),
    [anon_sym_AMP] = ACTIONS(149),
    [anon_sym_LT3] = ACTIONS(149),
    [anon_sym_u2661] = ACTIONS(149),
    [anon_sym_LT_SLASH3] = ACTIONS(149),
    [anon_sym_U0001f494] = ACTIONS(149),
    [anon_sym_u2764ufe0fu200dU0001fa79] = ACTIONS(149),
    [anon_sym_u2619] = ACTIONS(149),
    [anon_sym_u2665] = ACTIONS(149),
    [anon_sym_u2763] = ACTIONS(151),
    [anon_sym_u2764] = ACTIONS(151),
    [anon_sym_u2765] = ACTIONS(149),
    [anon_sym_u2766] = ACTIONS(149),
    [anon_sym_u2767] = ACTIONS(149),
    [anon_sym_U0001f394] = ACTIONS(149),
    [anon_sym_U0001fac0] = ACTIONS(149),
    [anon_sym_U0001f5a4] = ACTIONS(149),
    [anon_sym_U0001f499] = ACTIONS(149),
    [anon_sym_U0001fa77] = ACTIONS(149),
    [anon_sym_U0001fa75] = ACTIONS(149),
    [anon_sym_U0001f49a] = ACTIONS(149),
    [anon_sym_U0001f49b] = ACTIONS(149),
    [anon_sym_U0001f49c] = ACTIONS(149),
    [anon_sym_U0001f9e1] = ACTIONS(149),
    [anon_sym_U0001f90d] = ACTIONS(149),
    [anon_sym_U0001f90e] = ACTIONS(149),
    [anon_sym_U0001fa76] = ACTIONS(149),
    [anon_sym_u2764ufe0f] = ACTIONS(151),
    [anon_sym_U0001f493] = ACTIONS(149),
    [anon_sym_U0001f495] = ACTIONS(149),
    [anon_sym_U0001f496] = ACTIONS(149),
    [anon_sym_U0001f497] = ACTIONS(149),
    [anon_sym_U0001f498] = ACTIONS(149),
    [anon_sym_U0001f49d] = ACTIONS(149),
    [anon_sym_u2763ufe0f] = ACTIONS(149),
    [anon_sym_U0001f48c] = ACTIONS(149),
    [anon_sym_U0001f49e] = ACTIONS(149),
    [anon_sym_U0001f49f] = ACTIONS(149),
    [anon_sym_U0001faf6] = ACTIONS(151),
    [anon_sym_U0001faf6U0001f3fb] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3fc] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3fd] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3fe] = ACTIONS(149),
    [anon_sym_U0001faf6U0001f3ff] = ACTIONS(149),
    [anon_sym_U0001f3e9] = ACTIONS(149),
    [anon_sym_PIPE] = ACTIONS(149),
    [anon_sym_EQ_EQ] = ACTIONS(149),
    [anon_sym_u2248u2248] = ACTIONS(149),
    [anon_sym_TILDE_EQ] = ACTIONS(149),
    [anon_sym_TILDEu2248] = ACTIONS(149),
    [anon_sym_o_TILDE] = ACTIONS(151),
    [anon_sym_TILDEo] = ACTIONS(151),
    [anon_sym_o_TILDE_EQ] = ACTIONS(149),
    [anon_sym_o_TILDEu2248] = ACTIONS(149),
    [anon_sym_TILDEo_EQ] = ACTIONS(149),
    [anon_sym_TILDEou2248] = ACTIONS(149),
    [anon_sym_ou2248] = ACTIONS(149),
    [anon_sym_u2248o] = ACTIONS(149),
    [anon_sym_o_EQ] = ACTIONS(149),
    [anon_sym_EQo] = ACTIONS(149),
    [sym_comment] = ACTIONS(3),
    [sym_multiline_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 20,
    ACTIONS(7), 1,
      anon_sym_GT_LPAREN,
    ACTIONS(9), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(19), 1,
      anon_sym_GT_LT,
    ACTIONS(21), 1,
      anon_sym_GT,
    ACTIONS(23), 1,
      anon_sym_LT,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(169), 1,
      ts_builtin_sym_end,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(99), 1,
      sym_right_sub,
    STATE(115), 1,
      sym_loopy_fysh,
    STATE(118), 1,
      sym_happy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(11), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(13), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(17), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(38), 7,
      sym_subroutine,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
      aux_sym_source_file_repeat1,
    STATE(146), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [87] = 20,
    ACTIONS(171), 1,
      ts_builtin_sym_end,
    ACTIONS(173), 1,
      anon_sym_GT_LPAREN,
    ACTIONS(176), 1,
      anon_sym_LPAREN,
    ACTIONS(185), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(191), 1,
      anon_sym_GT_LT,
    ACTIONS(194), 1,
      anon_sym_GT,
    ACTIONS(197), 1,
      anon_sym_LT,
    ACTIONS(200), 1,
      anon_sym_LBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(99), 1,
      sym_right_sub,
    STATE(115), 1,
      sym_loopy_fysh,
    STATE(118), 1,
      sym_happy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(179), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(182), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(188), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(38), 7,
      sym_subroutine,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
      aux_sym_source_file_repeat1,
    STATE(146), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [174] = 18,
    ACTIONS(9), 1,
      anon_sym_LPAREN,
    ACTIONS(19), 1,
      anon_sym_GT_LT,
    ACTIONS(21), 1,
      anon_sym_GT,
    ACTIONS(23), 1,
      anon_sym_LT,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(205), 1,
      anon_sym_LT_GT_LT,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(113), 1,
      sym_happy_fysh,
    STATE(114), 1,
      sym_loopy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(11), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(13), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(17), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(42), 6,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
      aux_sym__statement_list_repeat1,
    STATE(147), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [254] = 19,
    ACTIONS(9), 1,
      anon_sym_LPAREN,
    ACTIONS(19), 1,
      anon_sym_GT_LT,
    ACTIONS(21), 1,
      anon_sym_GT,
    ACTIONS(23), 1,
      anon_sym_LT,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(207), 1,
      anon_sym_LT_GT_LT,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(113), 1,
      sym_happy_fysh,
    STATE(114), 1,
      sym_loopy_fysh,
    STATE(144), 1,
      sym__statement_list,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(11), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(13), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(17), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(43), 5,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
    STATE(147), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [336] = 19,
    ACTIONS(9), 1,
      anon_sym_LPAREN,
    ACTIONS(19), 1,
      anon_sym_GT_LT,
    ACTIONS(21), 1,
      anon_sym_GT,
    ACTIONS(23), 1,
      anon_sym_LT,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(209), 1,
      anon_sym_LT_GT_LT,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(113), 1,
      sym_happy_fysh,
    STATE(114), 1,
      sym_loopy_fysh,
    STATE(149), 1,
      sym__statement_list,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(11), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(13), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(17), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(43), 5,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
    STATE(147), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [418] = 18,
    ACTIONS(211), 1,
      anon_sym_LPAREN,
    ACTIONS(220), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(223), 1,
      anon_sym_LT_GT_LT,
    ACTIONS(228), 1,
      anon_sym_GT_LT,
    ACTIONS(231), 1,
      anon_sym_GT,
    ACTIONS(234), 1,
      anon_sym_LT,
    ACTIONS(237), 1,
      anon_sym_LBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(113), 1,
      sym_happy_fysh,
    STATE(114), 1,
      sym_loopy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(214), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(217), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(225), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(42), 6,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
      aux_sym__statement_list_repeat1,
    STATE(147), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [498] = 18,
    ACTIONS(9), 1,
      anon_sym_LPAREN,
    ACTIONS(19), 1,
      anon_sym_GT_LT,
    ACTIONS(21), 1,
      anon_sym_GT,
    ACTIONS(23), 1,
      anon_sym_LT,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(240), 1,
      anon_sym_LT_GT_LT,
    STATE(24), 1,
      sym_addition,
    STATE(35), 1,
      sym_positive_ident,
    STATE(113), 1,
      sym_happy_fysh,
    STATE(114), 1,
      sym_loopy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(11), 2,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
    ACTIONS(13), 2,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
    ACTIONS(17), 2,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
    STATE(39), 6,
      sym__statement,
      sym__simple_statement,
      sym_block,
      sym_loop_statement,
      sym_if_statement,
      aux_sym__statement_list_repeat1,
    STATE(147), 7,
      sym_return_statement,
      sym_break_statement,
      sym_anchor_statement,
      sym_expression_statement,
      sym_inc_statement,
      sym_dec_statement,
      sym_assignment_statement,
    STATE(10), 11,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [578] = 11,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(242), 1,
      anon_sym_GT_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LPAREN,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(248), 1,
      anon_sym_RBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(45), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(48), 2,
      sym_right_sub,
      sym_left_sub,
    STATE(7), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [625] = 10,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(242), 1,
      anon_sym_GT_LPAREN,
    ACTIONS(244), 1,
      anon_sym_LPAREN,
    ACTIONS(246), 1,
      anon_sym_LT,
    STATE(24), 1,
      sym_addition,
    STATE(46), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(49), 2,
      sym_right_sub,
      sym_left_sub,
    STATE(9), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [669] = 9,
    ACTIONS(252), 1,
      anon_sym_LPAREN,
    ACTIONS(255), 1,
      anon_sym_GT_LT,
    ACTIONS(258), 1,
      anon_sym_LT,
    ACTIONS(261), 1,
      anon_sym_LBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(46), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(250), 2,
      anon_sym_GT_LPAREN,
      anon_sym_RBRACK,
    STATE(9), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [710] = 9,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    ACTIONS(266), 1,
      anon_sym_RBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(46), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(9), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [750] = 9,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    ACTIONS(268), 1,
      anon_sym_RBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(50), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(9), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [790] = 9,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    ACTIONS(270), 1,
      anon_sym_RBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(47), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(9), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [830] = 9,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    ACTIONS(270), 1,
      anon_sym_RBRACK,
    STATE(24), 1,
      sym_addition,
    STATE(46), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(9), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [870] = 8,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    ACTIONS(272), 1,
      sym__name,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(13), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [907] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(12), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [941] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(14), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [975] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(13), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1009] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(5), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1043] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(4), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1077] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(3), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1111] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(2), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1145] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(11), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1179] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(8), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1213] = 7,
    ACTIONS(25), 1,
      anon_sym_LBRACK,
    ACTIONS(67), 1,
      anon_sym_GT_LT,
    ACTIONS(246), 1,
      anon_sym_LT,
    ACTIONS(264), 1,
      anon_sym_LPAREN,
    STATE(24), 1,
      sym_addition,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(15), 12,
      sym_grilled_fysh,
      sym__expression,
      sym_aquarium,
      sym_fysh_bowl,
      sym_positive_ident,
      sym_positive_scales,
      sym_positive_bones,
      sym_negative_ident,
      sym_negative_scales,
      sym_negative_bones,
      sym_binary_expression,
      sym_call_expression,
  [1247] = 5,
    ACTIONS(278), 1,
      anon_sym_GT_LT,
    STATE(90), 1,
      sym_dead_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(276), 3,
      anon_sym_LPAREN,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(274), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1275] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(283), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(281), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1298] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(287), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(285), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1321] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(291), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(289), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1344] = 5,
    ACTIONS(278), 1,
      anon_sym_GT_LT,
    STATE(92), 1,
      sym_dead_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(276), 3,
      anon_sym_LPAREN,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(274), 9,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LT_GT_LT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1371] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(295), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(293), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1394] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(299), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(297), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1417] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(303), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(301), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1440] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(307), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(305), 10,
      ts_builtin_sym_end,
      anon_sym_GT_LPAREN,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1463] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(295), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(293), 9,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LT_GT_LT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1485] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(299), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(297), 9,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LT_GT_LT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1507] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(283), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(281), 9,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LT_GT_LT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1529] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(287), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(285), 9,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LT_GT_LT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1551] = 3,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(291), 4,
      anon_sym_LPAREN,
      anon_sym_GT_LT,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(289), 9,
      anon_sym_LT_TILDE,
      anon_sym_U0001f991,
      anon_sym_GT_LT_BSLASH_SLASH_GT,
      anon_sym_LT_BSLASH_SLASH_GT_LT,
      anon_sym_GT_LT_GT,
      anon_sym_LT_GT_LT,
      anon_sym_LPAREN_PLUSo,
      anon_sym_o_PLUS_RPAREN,
      anon_sym_LBRACK,
  [1573] = 6,
    ACTIONS(309), 1,
      anon_sym_GT,
    ACTIONS(311), 1,
      anon_sym_DASH,
    ACTIONS(313), 1,
      aux_sym_positive_scales_token1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(315), 2,
      sym_one,
      sym_zero,
    STATE(80), 2,
      sym_spine,
      aux_sym__bones_repeat1,
  [1595] = 8,
    ACTIONS(317), 1,
      sym__name,
    ACTIONS(319), 1,
      anon_sym_LPAREN_LPAREN_LPAREN,
    ACTIONS(321), 1,
      anon_sym_POUND_POUND_POUND,
    ACTIONS(323), 1,
      sym_one,
    ACTIONS(325), 1,
      sym_zero,
    STATE(93), 1,
      sym__scales,
    STATE(106), 1,
      sym__bones,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [1621] = 6,
    ACTIONS(311), 1,
      anon_sym_DASH,
    ACTIONS(327), 1,
      anon_sym_GT,
    ACTIONS(329), 1,
      aux_sym_positive_scales_token1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(331), 2,
      sym_one,
      sym_zero,
    STATE(76), 2,
      sym_spine,
      aux_sym__bones_repeat1,
  [1643] = 7,
    ACTIONS(333), 1,
      sym__name,
    ACTIONS(335), 1,
      aux_sym_positive_scales_token1,
    STATE(82), 1,
      aux_sym_positive_scales_repeat1,
    STATE(108), 1,
      sym__scales,
    STATE(138), 1,
      sym__bones,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(337), 2,
      sym_one,
      sym_zero,
  [1667] = 6,
    ACTIONS(339), 1,
      anon_sym_GT,
    ACTIONS(341), 1,
      anon_sym_DASH,
    ACTIONS(344), 1,
      aux_sym_positive_scales_token1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(346), 2,
      sym_one,
      sym_zero,
    STATE(80), 2,
      sym_spine,
      aux_sym__bones_repeat1,
  [1689] = 7,
    ACTIONS(335), 1,
      aux_sym_positive_scales_token1,
    ACTIONS(349), 1,
      sym__name,
    STATE(82), 1,
      aux_sym_positive_scales_repeat1,
    STATE(108), 1,
      sym__scales,
    STATE(138), 1,
      sym__bones,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(337), 2,
      sym_one,
      sym_zero,
  [1713] = 6,
    ACTIONS(351), 1,
      aux_sym_positive_scales_token1,
    STATE(96), 1,
      aux_sym_positive_scales_repeat1,
    STATE(110), 1,
      sym__scales,
    STATE(123), 1,
      sym__bones,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(337), 2,
      sym_one,
      sym_zero,
  [1734] = 5,
    ACTIONS(353), 1,
      anon_sym_GT,
    STATE(87), 1,
      aux_sym__scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(355), 2,
      anon_sym_DASH,
      aux_sym_positive_scales_token1,
    ACTIONS(357), 2,
      sym_one,
      sym_zero,
  [1753] = 5,
    ACTIONS(309), 1,
      anon_sym_GT_LT,
    ACTIONS(359), 1,
      anon_sym_DASH,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(361), 2,
      sym_one,
      sym_zero,
    STATE(86), 2,
      sym_spine,
      aux_sym__bones_repeat1,
  [1772] = 5,
    ACTIONS(363), 1,
      anon_sym_GT,
    STATE(85), 1,
      aux_sym__scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(365), 2,
      anon_sym_DASH,
      aux_sym_positive_scales_token1,
    ACTIONS(367), 2,
      sym_one,
      sym_zero,
  [1791] = 5,
    ACTIONS(339), 1,
      anon_sym_GT_LT,
    ACTIONS(370), 1,
      anon_sym_DASH,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(373), 2,
      sym_one,
      sym_zero,
    STATE(86), 2,
      sym_spine,
      aux_sym__bones_repeat1,
  [1810] = 5,
    ACTIONS(376), 1,
      anon_sym_GT,
    STATE(85), 1,
      aux_sym__scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(378), 2,
      anon_sym_DASH,
      aux_sym_positive_scales_token1,
    ACTIONS(380), 2,
      sym_one,
      sym_zero,
  [1829] = 6,
    ACTIONS(317), 1,
      sym__name,
    ACTIONS(321), 1,
      anon_sym_POUND_POUND_POUND,
    STATE(93), 1,
      sym__scales,
    STATE(106), 1,
      sym__bones,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(323), 2,
      sym_one,
      sym_zero,
  [1850] = 5,
    ACTIONS(327), 1,
      anon_sym_GT_LT,
    ACTIONS(359), 1,
      anon_sym_DASH,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(382), 2,
      sym_one,
      sym_zero,
    STATE(84), 2,
      sym_spine,
      aux_sym__bones_repeat1,
  [1869] = 5,
    ACTIONS(15), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(384), 1,
      anon_sym_GT_LT,
    STATE(118), 1,
      sym_happy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(65), 2,
      sym_block,
      sym_if_statement,
  [1887] = 5,
    ACTIONS(15), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(386), 1,
      anon_sym_GT_LT,
    STATE(70), 1,
      sym_block,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(103), 2,
      sym_positive_ident,
      aux_sym_subroutine_repeat1,
  [1905] = 5,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(384), 1,
      anon_sym_GT_LT,
    STATE(113), 1,
      sym_happy_fysh,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(75), 2,
      sym_block,
      sym_if_statement,
  [1923] = 6,
    ACTIONS(311), 1,
      anon_sym_DASH,
    ACTIONS(388), 1,
      anon_sym_GT,
    ACTIONS(390), 1,
      aux_sym_positive_scales_token1,
    STATE(78), 1,
      sym_spine,
    STATE(105), 1,
      aux_sym_positive_scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [1943] = 3,
    ACTIONS(392), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(394), 4,
      anon_sym_DASH,
      aux_sym_positive_scales_token1,
      sym_one,
      sym_zero,
  [1957] = 3,
    ACTIONS(398), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(396), 4,
      anon_sym_LPAREN,
      anon_sym_LT,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [1971] = 5,
    ACTIONS(400), 1,
      anon_sym_GT,
    ACTIONS(402), 1,
      aux_sym_positive_scales_token1,
    STATE(96), 1,
      aux_sym_positive_scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(405), 2,
      sym_one,
      sym_zero,
  [1989] = 3,
    ACTIONS(409), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(407), 4,
      anon_sym_LPAREN,
      anon_sym_LT,
      anon_sym_LBRACK,
      anon_sym_RBRACK,
  [2003] = 5,
    ACTIONS(363), 1,
      anon_sym_GT_LT,
    ACTIONS(365), 1,
      anon_sym_DASH,
    STATE(98), 1,
      aux_sym__scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(411), 2,
      sym_one,
      sym_zero,
  [2021] = 5,
    ACTIONS(15), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(386), 1,
      anon_sym_GT_LT,
    STATE(69), 1,
      sym_block,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(91), 2,
      sym_positive_ident,
      aux_sym_subroutine_repeat1,
  [2039] = 5,
    ACTIONS(353), 1,
      anon_sym_GT_LT,
    ACTIONS(355), 1,
      anon_sym_DASH,
    STATE(101), 1,
      aux_sym__scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(414), 2,
      sym_one,
      sym_zero,
  [2057] = 5,
    ACTIONS(376), 1,
      anon_sym_GT_LT,
    ACTIONS(378), 1,
      anon_sym_DASH,
    STATE(98), 1,
      aux_sym__scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(416), 2,
      sym_one,
      sym_zero,
  [2075] = 3,
    ACTIONS(392), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    ACTIONS(394), 3,
      anon_sym_DASH,
      sym_one,
      sym_zero,
  [2088] = 4,
    ACTIONS(418), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(420), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
    STATE(103), 2,
      sym_positive_ident,
      aux_sym_subroutine_repeat1,
  [2103] = 4,
    ACTIONS(351), 1,
      aux_sym_positive_scales_token1,
    ACTIONS(423), 1,
      anon_sym_GT,
    STATE(96), 1,
      aux_sym_positive_scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2117] = 4,
    ACTIONS(351), 1,
      aux_sym_positive_scales_token1,
    ACTIONS(425), 1,
      anon_sym_GT,
    STATE(96), 1,
      aux_sym_positive_scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2131] = 4,
    ACTIONS(427), 1,
      anon_sym_GT,
    ACTIONS(429), 1,
      aux_sym_positive_scales_token1,
    STATE(104), 1,
      aux_sym_positive_scales_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2145] = 4,
    ACTIONS(63), 1,
      anon_sym_DASH,
    ACTIONS(431), 1,
      anon_sym_RBRACK,
    STATE(109), 1,
      aux_sym_aquarium_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2159] = 4,
    ACTIONS(359), 1,
      anon_sym_DASH,
    ACTIONS(433), 1,
      anon_sym_GT_LT,
    STATE(89), 1,
      sym_spine,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2173] = 4,
    ACTIONS(71), 1,
      anon_sym_RBRACK,
    ACTIONS(435), 1,
      anon_sym_DASH,
    STATE(109), 1,
      aux_sym_aquarium_repeat1,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2187] = 4,
    ACTIONS(359), 1,
      anon_sym_DASH,
    ACTIONS(438), 1,
      anon_sym_GT_LT,
    STATE(89), 1,
      sym_spine,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2201] = 3,
    ACTIONS(15), 1,
      anon_sym_GT_LT_GT,
    STATE(67), 1,
      sym_block,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2212] = 3,
    ACTIONS(15), 1,
      anon_sym_GT_LT_GT,
    STATE(62), 1,
      sym_block,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2223] = 3,
    ACTIONS(440), 1,
      anon_sym_LBRACK,
    STATE(116), 1,
      sym_fysh_tank,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2234] = 3,
    ACTIONS(440), 1,
      anon_sym_LBRACK,
    STATE(117), 1,
      sym_fysh_tank,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2245] = 3,
    ACTIONS(440), 1,
      anon_sym_LBRACK,
    STATE(111), 1,
      sym_fysh_tank,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2256] = 3,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    STATE(66), 1,
      sym_block,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2267] = 3,
    ACTIONS(203), 1,
      anon_sym_GT_LT_GT,
    STATE(71), 1,
      sym_block,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2278] = 3,
    ACTIONS(440), 1,
      anon_sym_LBRACK,
    STATE(112), 1,
      sym_fysh_tank,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2289] = 3,
    ACTIONS(442), 1,
      anon_sym_AT,
    ACTIONS(444), 1,
      anon_sym_CARET,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2300] = 3,
    ACTIONS(85), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(87), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2311] = 3,
    ACTIONS(446), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(448), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2322] = 3,
    ACTIONS(396), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(398), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2333] = 2,
    ACTIONS(450), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2341] = 2,
    ACTIONS(452), 1,
      sym__name,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2349] = 2,
    ACTIONS(454), 1,
      anon_sym_RPAREN_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2357] = 2,
    ACTIONS(456), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2365] = 2,
    ACTIONS(458), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2373] = 2,
    ACTIONS(460), 1,
      anon_sym_STAR,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2381] = 2,
    ACTIONS(462), 1,
      anon_sym_LPAREN_LPAREN_LPAREN,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2389] = 2,
    ACTIONS(464), 1,
      sym__name,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2397] = 2,
    ACTIONS(466), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2405] = 2,
    ACTIONS(468), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2413] = 2,
    ACTIONS(470), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2421] = 2,
    ACTIONS(472), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2429] = 2,
    ACTIONS(474), 1,
      ts_builtin_sym_end,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2437] = 2,
    ACTIONS(476), 1,
      sym__name,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2445] = 2,
    ACTIONS(478), 1,
      anon_sym_TILDE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2453] = 2,
    ACTIONS(480), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2461] = 2,
    ACTIONS(482), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2469] = 2,
    ACTIONS(484), 1,
      anon_sym_LPAREN_LPAREN_LPAREN,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2477] = 2,
    ACTIONS(486), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2485] = 2,
    ACTIONS(488), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2493] = 2,
    ACTIONS(490), 1,
      anon_sym_GT_LT_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2501] = 2,
    ACTIONS(492), 1,
      anon_sym_LT_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2509] = 2,
    ACTIONS(494), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2517] = 2,
    ACTIONS(496), 1,
      anon_sym_TILDE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2525] = 2,
    ACTIONS(498), 1,
      anon_sym_TILDE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2533] = 2,
    ACTIONS(500), 1,
      anon_sym_RPAREN,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2541] = 2,
    ACTIONS(502), 1,
      anon_sym_LT_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2549] = 2,
    ACTIONS(504), 1,
      anon_sym_GT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2557] = 2,
    ACTIONS(506), 1,
      anon_sym_TILDE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2565] = 2,
    ACTIONS(508), 1,
      anon_sym_TILDE,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2573] = 2,
    ACTIONS(510), 1,
      anon_sym_LBRACK,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2581] = 2,
    ACTIONS(512), 1,
      sym__name,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2589] = 2,
    ACTIONS(444), 1,
      anon_sym_CARET,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
  [2597] = 2,
    ACTIONS(514), 1,
      anon_sym_GT_LT,
    ACTIONS(3), 2,
      sym_multiline_comment,
      sym_comment,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(37)] = 0,
  [SMALL_STATE(38)] = 87,
  [SMALL_STATE(39)] = 174,
  [SMALL_STATE(40)] = 254,
  [SMALL_STATE(41)] = 336,
  [SMALL_STATE(42)] = 418,
  [SMALL_STATE(43)] = 498,
  [SMALL_STATE(44)] = 578,
  [SMALL_STATE(45)] = 625,
  [SMALL_STATE(46)] = 669,
  [SMALL_STATE(47)] = 710,
  [SMALL_STATE(48)] = 750,
  [SMALL_STATE(49)] = 790,
  [SMALL_STATE(50)] = 830,
  [SMALL_STATE(51)] = 870,
  [SMALL_STATE(52)] = 907,
  [SMALL_STATE(53)] = 941,
  [SMALL_STATE(54)] = 975,
  [SMALL_STATE(55)] = 1009,
  [SMALL_STATE(56)] = 1043,
  [SMALL_STATE(57)] = 1077,
  [SMALL_STATE(58)] = 1111,
  [SMALL_STATE(59)] = 1145,
  [SMALL_STATE(60)] = 1179,
  [SMALL_STATE(61)] = 1213,
  [SMALL_STATE(62)] = 1247,
  [SMALL_STATE(63)] = 1275,
  [SMALL_STATE(64)] = 1298,
  [SMALL_STATE(65)] = 1321,
  [SMALL_STATE(66)] = 1344,
  [SMALL_STATE(67)] = 1371,
  [SMALL_STATE(68)] = 1394,
  [SMALL_STATE(69)] = 1417,
  [SMALL_STATE(70)] = 1440,
  [SMALL_STATE(71)] = 1463,
  [SMALL_STATE(72)] = 1485,
  [SMALL_STATE(73)] = 1507,
  [SMALL_STATE(74)] = 1529,
  [SMALL_STATE(75)] = 1551,
  [SMALL_STATE(76)] = 1573,
  [SMALL_STATE(77)] = 1595,
  [SMALL_STATE(78)] = 1621,
  [SMALL_STATE(79)] = 1643,
  [SMALL_STATE(80)] = 1667,
  [SMALL_STATE(81)] = 1689,
  [SMALL_STATE(82)] = 1713,
  [SMALL_STATE(83)] = 1734,
  [SMALL_STATE(84)] = 1753,
  [SMALL_STATE(85)] = 1772,
  [SMALL_STATE(86)] = 1791,
  [SMALL_STATE(87)] = 1810,
  [SMALL_STATE(88)] = 1829,
  [SMALL_STATE(89)] = 1850,
  [SMALL_STATE(90)] = 1869,
  [SMALL_STATE(91)] = 1887,
  [SMALL_STATE(92)] = 1905,
  [SMALL_STATE(93)] = 1923,
  [SMALL_STATE(94)] = 1943,
  [SMALL_STATE(95)] = 1957,
  [SMALL_STATE(96)] = 1971,
  [SMALL_STATE(97)] = 1989,
  [SMALL_STATE(98)] = 2003,
  [SMALL_STATE(99)] = 2021,
  [SMALL_STATE(100)] = 2039,
  [SMALL_STATE(101)] = 2057,
  [SMALL_STATE(102)] = 2075,
  [SMALL_STATE(103)] = 2088,
  [SMALL_STATE(104)] = 2103,
  [SMALL_STATE(105)] = 2117,
  [SMALL_STATE(106)] = 2131,
  [SMALL_STATE(107)] = 2145,
  [SMALL_STATE(108)] = 2159,
  [SMALL_STATE(109)] = 2173,
  [SMALL_STATE(110)] = 2187,
  [SMALL_STATE(111)] = 2201,
  [SMALL_STATE(112)] = 2212,
  [SMALL_STATE(113)] = 2223,
  [SMALL_STATE(114)] = 2234,
  [SMALL_STATE(115)] = 2245,
  [SMALL_STATE(116)] = 2256,
  [SMALL_STATE(117)] = 2267,
  [SMALL_STATE(118)] = 2278,
  [SMALL_STATE(119)] = 2289,
  [SMALL_STATE(120)] = 2300,
  [SMALL_STATE(121)] = 2311,
  [SMALL_STATE(122)] = 2322,
  [SMALL_STATE(123)] = 2333,
  [SMALL_STATE(124)] = 2341,
  [SMALL_STATE(125)] = 2349,
  [SMALL_STATE(126)] = 2357,
  [SMALL_STATE(127)] = 2365,
  [SMALL_STATE(128)] = 2373,
  [SMALL_STATE(129)] = 2381,
  [SMALL_STATE(130)] = 2389,
  [SMALL_STATE(131)] = 2397,
  [SMALL_STATE(132)] = 2405,
  [SMALL_STATE(133)] = 2413,
  [SMALL_STATE(134)] = 2421,
  [SMALL_STATE(135)] = 2429,
  [SMALL_STATE(136)] = 2437,
  [SMALL_STATE(137)] = 2445,
  [SMALL_STATE(138)] = 2453,
  [SMALL_STATE(139)] = 2461,
  [SMALL_STATE(140)] = 2469,
  [SMALL_STATE(141)] = 2477,
  [SMALL_STATE(142)] = 2485,
  [SMALL_STATE(143)] = 2493,
  [SMALL_STATE(144)] = 2501,
  [SMALL_STATE(145)] = 2509,
  [SMALL_STATE(146)] = 2517,
  [SMALL_STATE(147)] = 2525,
  [SMALL_STATE(148)] = 2533,
  [SMALL_STATE(149)] = 2541,
  [SMALL_STATE(150)] = 2549,
  [SMALL_STATE(151)] = 2557,
  [SMALL_STATE(152)] = 2565,
  [SMALL_STATE(153)] = 2573,
  [SMALL_STATE(154)] = 2581,
  [SMALL_STATE(155)] = 2589,
  [SMALL_STATE(156)] = 2597,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(156),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, .production_id = 11),
  [29] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 3, .production_id = 11),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_addition, 2, .production_id = 4),
  [43] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_addition, 2, .production_id = 4), SHIFT(54),
  [46] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_addition, 2, .production_id = 4),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [50] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_addition, 2, .production_id = 4), SHIFT(88),
  [53] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_addition, 2, .production_id = 4), SHIFT(81),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_addition, 2, .production_id = 4), SHIFT(44),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 1),
  [61] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_call_expression_repeat1, 1),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [67] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_aquarium_repeat1, 2),
  [73] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_expression_statement, 1),
  [75] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment_statement, 3, .production_id = 12),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [81] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_return_statement, 2, .production_id = 1),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_anchor_statement, 2, .production_id = 2),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_positive_ident, 3, .production_id = 5),
  [87] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_positive_ident, 3, .production_id = 5),
  [89] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_aquarium, 4),
  [91] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_aquarium, 4),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 3),
  [95] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 3),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_grilled_fysh, 3),
  [99] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_grilled_fysh, 3),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 5),
  [103] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 5),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_positive_scales, 3, .production_id = 6),
  [107] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_positive_scales, 3, .production_id = 6),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 4),
  [111] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 4),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_positive_bones, 3, .production_id = 7),
  [115] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_positive_bones, 3, .production_id = 7),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 1),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 1),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_negative_scales, 3, .production_id = 6),
  [123] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_negative_scales, 3, .production_id = 6),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_negative_bones, 4, .production_id = 15),
  [127] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_negative_bones, 4, .production_id = 15),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_negative_scales, 4, .production_id = 14),
  [131] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_negative_scales, 4, .production_id = 14),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_positive_bones, 4, .production_id = 7),
  [135] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_positive_bones, 4, .production_id = 7),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_positive_scales, 4, .production_id = 6),
  [139] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_positive_scales, 4, .production_id = 6),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_aquarium, 2),
  [143] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_aquarium, 2),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_negative_bones, 3, .production_id = 7),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_negative_bones, 3, .production_id = 7),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_negative_ident, 3, .production_id = 5),
  [151] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_negative_ident, 3, .production_id = 5),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fysh_bowl, 3),
  [155] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fysh_bowl, 3),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_aquarium, 3),
  [159] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_aquarium, 3),
  [161] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__expression, 1),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1),
  [165] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [167] = {.entry = {.count = 1, .reusable = false}}, SHIFT(151),
  [169] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [171] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [173] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(130),
  [176] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(54),
  [179] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(53),
  [182] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(137),
  [185] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(40),
  [188] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(61),
  [191] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(77),
  [194] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(156),
  [197] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(79),
  [200] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(44),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__statement_list, 2),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [211] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(54),
  [214] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(53),
  [217] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(137),
  [220] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(41),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__statement_list_repeat1, 2),
  [225] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(61),
  [228] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(77),
  [231] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(156),
  [234] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(79),
  [237] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__statement_list_repeat1, 2), SHIFT_REPEAT(44),
  [240] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__statement_list, 1),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 2),
  [252] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 2), SHIFT_REPEAT(54),
  [255] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_call_expression_repeat1, 2), SHIFT_REPEAT(88),
  [258] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 2), SHIFT_REPEAT(81),
  [261] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 2), SHIFT_REPEAT(44),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 3, .production_id = 10),
  [276] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_if_statement, 3, .production_id = 10),
  [278] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_if_statement, 3, .production_id = 10), SHIFT(140),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2),
  [283] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 2),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3),
  [287] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block, 3),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 5, .production_id = 16),
  [291] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_if_statement, 5, .production_id = 16),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_loop_statement, 3, .production_id = 9),
  [295] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_loop_statement, 3, .production_id = 9),
  [297] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__simple_statement, 2),
  [299] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__simple_statement, 2),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_subroutine, 2, .production_id = 3),
  [303] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_subroutine, 2, .production_id = 3),
  [305] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_subroutine, 3, .production_id = 8),
  [307] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_subroutine, 3, .production_id = 8),
  [309] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bones, 3),
  [311] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bones, 3),
  [315] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [317] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [319] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [321] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [323] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [325] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [327] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__bones, 2),
  [329] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bones, 2),
  [331] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [333] = {.entry = {.count = 1, .reusable = false}}, SHIFT(139),
  [335] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [337] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [339] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__bones_repeat1, 2),
  [341] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__bones_repeat1, 2), SHIFT_REPEAT(94),
  [344] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__bones_repeat1, 2),
  [346] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__bones_repeat1, 2), SHIFT_REPEAT(80),
  [349] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [353] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__scales, 1),
  [355] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__scales, 1),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [361] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [363] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym__scales_repeat1, 2),
  [365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__scales_repeat1, 2),
  [367] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__scales_repeat1, 2), SHIFT_REPEAT(85),
  [370] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__bones_repeat1, 2), SHIFT_REPEAT(102),
  [373] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__bones_repeat1, 2), SHIFT_REPEAT(86),
  [376] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__scales, 2),
  [378] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__scales, 2),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [384] = {.entry = {.count = 1, .reusable = false}}, SHIFT(129),
  [386] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [388] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [392] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_spine, 1),
  [394] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_spine, 1),
  [396] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_right_sub, 3, .production_id = 5),
  [398] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_right_sub, 3, .production_id = 5),
  [400] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_positive_scales_repeat1, 2),
  [402] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_positive_scales_repeat1, 2), SHIFT_REPEAT(96),
  [405] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_positive_scales_repeat1, 2),
  [407] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_left_sub, 3, .production_id = 5),
  [409] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_left_sub, 3, .production_id = 5),
  [411] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__scales_repeat1, 2), SHIFT_REPEAT(98),
  [414] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [418] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_subroutine_repeat1, 2),
  [420] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_subroutine_repeat1, 2), SHIFT_REPEAT(136),
  [423] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [425] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [427] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [431] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [433] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [435] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_aquarium_repeat1, 2), SHIFT_REPEAT(60),
  [438] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [446] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dead_fysh, 4),
  [448] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dead_fysh, 4),
  [450] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [456] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_happy_fysh, 4),
  [458] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [466] = {.entry = {.count = 1, .reusable = false}}, SHIFT(121),
  [468] = {.entry = {.count = 1, .reusable = false}}, SHIFT(126),
  [470] = {.entry = {.count = 1, .reusable = false}}, SHIFT(153),
  [472] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [474] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [478] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_break_statement, 1),
  [480] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [482] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [484] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [486] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [488] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [490] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fysh_tank, 3),
  [492] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [494] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [496] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [498] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [500] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [504] = {.entry = {.count = 1, .reusable = false}}, SHIFT(120),
  [506] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dec_statement, 4, .production_id = 5),
  [508] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inc_statement, 4, .production_id = 13),
  [510] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_loopy_fysh, 4),
  [512] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [514] = {.entry = {.count = 1, .reusable = false}}, SHIFT(124),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token_multiline_comment = 0,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_multiline_comment] = sym_multiline_comment,
};

static const bool ts_external_scanner_states[2][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_multiline_comment] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_fysh_external_scanner_create(void);
void tree_sitter_fysh_external_scanner_destroy(void *);
bool tree_sitter_fysh_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_fysh_external_scanner_serialize(void *, char *);
void tree_sitter_fysh_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_fysh() {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym__name,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_fysh_external_scanner_create,
      tree_sitter_fysh_external_scanner_destroy,
      tree_sitter_fysh_external_scanner_scan,
      tree_sitter_fysh_external_scanner_serialize,
      tree_sitter_fysh_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
