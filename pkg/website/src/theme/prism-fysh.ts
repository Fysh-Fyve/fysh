Prism.languages.fysh = {
  comment: [
    {
      pattern: /><\/\*>[\s\S]*?<\*\/></,
      greedy: true,
    },
    {
      pattern: /><\/\/>.*$/m,
      greedy: true,
    },
  ],
  string: [
    {
      pattern: /\*[^*]*\*/,
      greedy: true,
    },
    {
      pattern: /🫧[^🫧]*🫧/,
      greedy: true,
      alias: 'special',
    },
  ],
  keyword: [
    {
      pattern: /><\(*[*^@]>/,
      greedy: true,
    },
    {
      pattern: /><\\\/>|<\\\/></,
      alias: 'control-flow',
    },
  ],
};
