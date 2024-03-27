/**
 * @file Fysh grammar for tree-sitter
 * @author Charles Ancheta
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

const PREC = {
    primary: 7,
    unary: 6,
    multiplicative: 5,
    additive: 4,
    comparative: 3,
    anchor: 2,
    composite_literal: -1,
  },
  multiplicative_operators = ["<3", "♡", "</3", "💔", "<<", ">>", "&"],
  additive_operators = ["|", "^"],
  comparative_operators = [
    "==",
    "≈≈",
    "~=",
    "~≈",
    "o~",
    "~o",
    "o~=",
    "o~≈",
    "~o=",
    "~o≈",
  ],
  anchor = choice("(+o", "o+)");

module.exports = grammar({
  name: "fysh",

  word: ($) => $._name,

  extras: ($) => [
    $.comment,
    $.multiline_comment,
    /\s/,
  ],

  externals: ($) => [
    $.multiline_comment,
  ],

  conflicts: ($) => [
    [$.loop_statement, $.if_statement, $.scales],
    [$.addition],
    [$.if_statement],
  ],

  rules: {
    source_file: ($) => seq(repeat(choice($._statement, $.subroutine))),

    subroutine: ($) =>
      seq(
        $.left_sub,
        field("params", repeat($.positive_ident)),
        field("body", $.block),
      ),

    left_sub: ($) => seq(">(", field("name", $._name), ")"),
    right_sub: ($) => seq("(", field("name", $._name), ")<"),

    _statement: ($) =>
      choice(
        $._simple_statement,
        $.if_statement,
        $.loop_statement,
        $.block,
      ),

    _simple_statement: ($) =>
      seq(
        choice(
          $.assignment_statement,
          $.anchor_statement,
          $.expression_statement,
          $.inc_statement,
          $.dec_statement,
        ),
        "~",
      ),

    _statement_list: ($) => seq($._statement, repeat($._statement)),

    block: ($) => seq("><>", optional($._statement_list), "<><"),

    anchor_statement: ($) =>
      seq(field("dir", anchor), field("value", $._expression)),

    loopy_fysh: (_) => controlFysh("@"),
    happy_fysh: (_) => controlFysh("^"),
    dead_fysh: (_) => controlFysh("*"),
    grilled_fysh: (_) => rightFysh("###"),

    loop_statement: ($) =>
      seq($.loopy_fysh, field("cond", $.fysh_tank), field("body", $.block)),

    if_statement: ($) =>
      seq(
        $.happy_fysh,
        field("cond", $.fysh_tank),
        field("then", $.block),
        optional(
          seq(
            $.dead_fysh,
            field("else", choice($.block, $.if_statement)),
          ),
        ),
      ),

    expression_statement: ($) => $._expression,
    inc_statement: ($) =>
      prec(PREC.primary, seq(">", rightFysh(field("name", $._name)))),
    dec_statement: ($) =>
      prec(PREC.primary, seq(leftFysh(field("name", $._name)), "<")),

    assignment_statement: ($) =>
      seq(
        field("left", $.positive_ident),
        choice("≈", "="),
        field("right", $._expression),
      ),

    _expression: ($) =>
      choice(
        $.binary_expression,
        $.fysh_bowl,
        $.positive_ident,
        $.positive_literal,
        $.negative_ident,
        $.negative_literal,
        $.grilled_fysh,
        $.call_expression,
      ),

    fysh_tank: ($) => seq("[", $._expression, "]"),
    fysh_bowl: ($) => seq("(", $._expression, ")"),

    positive_ident: ($) => rightFysh(field("name", $._name)),
    positive_literal: ($) =>
      rightFysh($.scales, repeat(token.immediate(choice("o", "°")))),
    negative_ident: ($) => leftFysh(field("name", $._name)),
    negative_literal: ($) =>
      leftFysh(repeat(token.immediate(choice("o", "°"))), $.scales),

    scales: ($) => seq(choice($.one, $.zero), repeat(choice($.one, $.zero))),
    one: (_) => token(choice("{", "}")),
    zero: (_) => token(choice("(", ")")),

    binary_expression: ($) => {
      const table = [
        [PREC.multiplicative, choice(...multiplicative_operators)],
        [PREC.additive, choice(...additive_operators)],
        [PREC.comparative, choice(...comparative_operators)],
        [PREC.anchor, anchor],
      ];

      return choice(
        ...table.map(([precedence, operator]) =>
          prec.left(
            // @ts-expect-error
            precedence,
            seq(
              field("left", $._expression),
              // @ts-expect-error
              field("operator", operator),
              field("right", $._expression),
            ),
          )
        ),
        prec.left(PREC.additive, $.addition),
      );
    },

    call_expression: ($) =>
      seq(
        "[",
        repeat(prec(PREC.primary, $._expression)),
        choice($.left_sub, $.right_sub),
        repeat(prec(PREC.primary, $._expression)),
        "]",
      ),

    addition: ($) =>
      seq(field("left", $._expression), field("right", $._expression)),

    _name: (_) => /[_\p{XID_Start}][_\p{XID_Continue}]*/,

    comment: (_) => token(seq("><//>", /[^\n]*/)),
  },
});

/**
 * Creates a rule for right-facing fysh
 *
 * @param {RuleOrLiteral[]} body
 *
 * @return {SeqRule}
 */
function rightFysh(...body) {
  return seq("><", ...body, ">");
}

/**
 * Creates a rule for left-facing fysh
 *
 * @param {RuleOrLiteral[]} body
 *
 * @return {SeqRule}
 */
function leftFysh(...body) {
  return seq("<", ...body, "><");
}

/**
 * Creates a rule for control flow fysh
 *
 * @param {string} eye
 *
 * @return {SeqRule}
 */
function controlFysh(eye) {
  return rightFysh("(((", eye);
}
