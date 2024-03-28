; TODO: Be more colourful??

(comment) @comment @spell
(multiline_comment) @comment @spell

(positive_ident) @type
(negative_ident) @type.definition

(one) @punctuation.special
(zero) @constant

[
  "["
  "]"
  "><>"
  "<><"
  "("
  ")"
] @punctuation.bracket

(happy_fysh) @keyword
(loopy_fysh) @keyword
(dead_fysh) @keyword

; TODO: Finish all operators
[
  "<<"
  ">>"
  "(+o"
  "o+)"
  "o~"
  "~o"
] @operator

[
  "<3"
  "</3"
  "♡"
] @hearts

