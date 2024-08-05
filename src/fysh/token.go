package fysh

import (
	"strconv"
	"strings"
)

type Species int

const (
	/* Invalid token! */
	Invalid Species = iota

	End     /* End of the input */
	Scales  /* binary value */
	Bones   /* floating point value ><}-}-}> */
	Ident   /* variable */
	Mul     /* <3 or ♡ */
	Div     /* </3 or 💔 */
	LT      /* ~o (less than    '<' ) */
	GT      /* o~ (greater than '>' ) */
	LTE     /* ~o≈ (less than equal to    '<=' ) */
	GTE     /* o~≈ (greater than equal to '>=' ) */
	Assign  /* ≈ */
	Eq      /* ≈≈  (Equal to '==') */
	NEq     /* ~≈  (Not equal to '!=') */
	Inc     /* >><fysh> (add 1 'fysh++') */
	Dec     /* <fysh><< (sub 1 'fysh--') */
	LTank   /* [ (used for Arrays, loops, and conditionals) */
	RTank   /* ] */
	LBowl   /* ( (Used for FISHS (BEDMAS)) */
	RBowl   /* ) */
	LFysh   /* ><> (same as open curly bracket '{' ) */
	RFysh   /* <>< (same as closing curly bracket '}' ) */
	LWTF    /* WHAT THE FYSHs(Throw error opening) ><!@#$> */
	RWTF    /* WHAT THE FYSH (Throw error closing) <!@#$>< */
	Grilled /* Random fysh ><###> */
	Loop    /* ><(((@> */
	Comment /* ><//> Comment */
	BlockC  /* Multiline Comment */
	BWAnd   /* & */
	BWOr    /* | */
	BWNot   /* ! */
	Caret   /* ^ */
	LAnd    /* && */
	LOr     /* || */
	LNot    /* !! */
	Water   /* ~ */
	LShift  /* << */
	RShift  /* \>\> */
	If      /* ><(((^> */
	Else    /* ><(((*> */
	Food    /* - */
	LAnchor /* (+o */
	RAnchor /* o+) */
	Sub     /* (submarine)< */
	Squid   /* <~ return operator */
	BreakFysh  /* ><\/> or <\/>< (break) */
	String	/*🫧*/
)

var tokens = [...]string{
	Scales:  "LITERAL",
	Bones:   "FLOAT",
	Ident:   "IDENT",
	Mul:     "*",
	Div:     "/",
	LT:      "<",
	GT:      ">",
	LTE:     "<=",
	GTE:     ">=",
	Assign:  "=",
	Eq:      "==",
	NEq:     "!=",
	Inc:     "++",
	Dec:     "--",
	LTank:   "[",
	RTank:   "]",
	LBowl:   "(",
	RBowl:   ")",
	LFysh:   "{",
	RFysh:   "}",
	LWTF:    "WTF(",
	RWTF:    ")WTF",
	Grilled: "><###>",
	Loop:    "while",
	Comment: "//",
	BlockC:  "/**/",
	Invalid: "INVALID",
	End:     "END",
	BWAnd:   "&",
	BWOr:    "|",
	BWNot:   "~",
	Caret:   "^",
	LAnd:    "&&",
	LOr:     "||",
	LNot:    "!",
	Water:   ";",
	LShift:  "<<",
	RShift:  ">>",
	If:      "if",
	Else:    "else",
	Food:    ",",
	LAnchor: "(+o",
	RAnchor: "o+)",
	Sub:     "SUBMARINE",
	Squid:   "return",
	BreakFysh:  "break",
	String: "STRING",
}

type Fysh struct {
	Type  Species
	Value string
}

func (f *Fysh) String() string {
	var s string
	switch f.Type {
	default:
		s = f.Type.String()
	case Scales:
		fallthrough
	case Bones:
		fallthrough
	case Ident:
		fallthrough
	case Inc:
		fallthrough
	case Dec:
		fallthrough
	case Comment:
		fallthrough
	case BlockC:
		fallthrough
	case Invalid:
		s = f.Value
	}
	return s
}

func getBin(s string) string {
	s = strings.ReplaceAll(s, "o", "")
	s = strings.ReplaceAll(s, "°", "")
	s = strings.ReplaceAll(s, "}", "1")
	s = strings.ReplaceAll(s, "{", "1")
	s = strings.ReplaceAll(s, "(", "0")
	return strings.ReplaceAll(s, ")", "0")
}

func (f *Fysh) Unfysh() (string, bool) {
	var s string
	negate := false
	switch f.Type {
	case Dec:
		// <name><<
		s = f.Value[1 : len(f.Value)-3]
	case Inc:
		// >><name>
		s = f.Value[3 : len(f.Value)-1]
	case Scales:
		fallthrough
	case Bones:
		fallthrough
	case Ident:
		fallthrough
	case Sub:
		negate = f.Value[0] != '>'
		if negate {
			// left
			// *name*<
			s = f.Value[1 : len(f.Value)-2]
		} else {
			// right
			// >*name*
			s = f.Value[2 : len(f.Value)-1]
		}

	}
	if f.Type == Scales || f.Type == Bones {
		s = getBin(s)
	}
	return s, negate
}

func (s Species) IsOneOf(other ...Species) bool {
	for _, o := range other {
		if s == o {
			return true
		}
	}
	return false
}

func (s Species) String() string {
	str := ""
	if 0 <= s && s < Species(len(tokens)) {
		str = tokens[s]
	}
	if str == "" {
		str = "species(" + strconv.Itoa(int(s)) + ")"
	}
	return str
}
