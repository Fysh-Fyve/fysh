/**
 * @file Fysh grammar for tree-sitter
 * @author Charles Ancheta
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "fysh",
  rules: {
    source_file: ($) => "",
  },
});
