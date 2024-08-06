package scanner

import (
	"fmt"
	"io"
	"unicode"
	"unicode/utf8"

	"github.com/Fysh-Fyve/fysh/src/fysh"
)

type Scanner struct {
	input    []byte
	filename string
	current  int
	peek     int
	ch       rune

	line int
	col  int
}

// Creates a new scanner given a filename and reader
func NewFile(filename string, r io.Reader) (*Scanner, error) {
	b, err := io.ReadAll(r)
	if err != nil {
		return nil, fmt.Errorf("NewFile: %w", err)

	}
	s := &Scanner{filename: filename, input: b}
	s.reel()
	return s, nil
}

func New(input []byte) *Scanner {
	s := &Scanner{input: input}
	s.reel()
	return s
}

// Checks if the character can be the start of an identifier
func isIdentStart(c rune) bool {
	return c == '_' || c == '^' || unicode.IsLetter(c) || unicode.IsNumber(c) || c > unicode.MaxASCII
}

// Checks if the character is a fysh eye
func isEye(c rune) bool {
	return c == 'o' || c == 'O' || c == '0' || c == '°'
}

// Checks if the character can be part of an identifier body
func isIdentBody(c rune) bool {
	return c == '_' || c == ' ' || c == '^' || c == '-' || unicode.IsLetter(c) || unicode.IsNumber(c) || c > unicode.MaxASCII
}

// Checks if the character is a scale character
func isScale(ch rune) bool {
	return ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '-'
}

func isLeftTale(ch rune) bool {
	leftTales := []rune{'<', '⧼', '⟨', '⟪', '〈', '⦃', '⦅', '⦇', '⦉', '⦋', '⦍', '⦏', '⦑', '⦓', '⦕', '〈', '❬', '❮', '❰', '❲', '❴'}
	for _, tale := range leftTales {
		if ch == tale {
			return true
		}
	}
	return false
}

func isRightTale(ch rune) bool {
	rightTales := []rune{'>', '⧽', '⟩', '⟫', '〉', '⦄', '⦆', '⦈', '⦊', '⦌', '⦎', '⦐', '⦒', '⦔', '⦖', '〉', '❭', '❯', '❱', '❳', '❵'}
	for _, tale := range rightTales {
		if ch == tale {
			return true
		}
	}
	return false
}

// Peeks at the next character without advancing the scanner
func (s *Scanner) periscope() rune {
	if s.peek >= len(s.input) {
		return 0
	}
	end := min(len(s.input), s.peek+4)
	val, _ := utf8.DecodeRune(s.input[s.peek:end])
	return val
}

// Advances the scanner to the next character (peek + 1)
func (s *Scanner) reel() rune {
	if s.peek >= len(s.input) {
		s.ch = 0
		s.current = s.peek
	} else {
		end := min(len(s.input), s.peek+4)
		val, width := utf8.DecodeRune(s.input[s.peek:end])
		s.ch = val
		s.current = s.peek
		s.peek += width
	}
	return s.periscope()
}

// Expects a specific rune and advances if it matches
func (s *Scanner) expect(b rune) bool {
	res := s.periscope() == b
	if res {
		s.reel()
	}
	return res
}

// Matches a string of runes, advancing the scanner if they match
func (s *Scanner) match(str string) bool {
	for _, v := range str {
		if !s.expect(v) {
			return false
		}
	}
	return true
}

// Handles the '<' (less than) character and determines the appropriate fysh type
func (s *Scanner) lt(start int) fysh.Fysh {
	var f fysh.Fysh

	switch s.periscope() {
	case '~': // <~ (less than or equal to) or <= (less than or equal to)
		s.reel()
		f = newFysh(fysh.Squid)
	case '\\':
		s.reel()
		if s.match("/><") {
			f = newFysh(fysh.BreakFysh)
		} else {
			f = fyshWithValue(fysh.Invalid, s.input[start:s.peek])
		}
	case '/':
		s.reel()
		if s.expect('3') {
			f = newFysh(fysh.Div)
		} else {
			f = fyshWithValue(fysh.Invalid, s.input[start:s.peek])
		}
	case '3':
		s.reel()
		f = newFysh(fysh.Mul)
	case '<':
		s.reel()
		f = newFysh(fysh.LShift)
	case '>':
		s.reel()
		if s.expect('<') {
			f = newFysh(fysh.RFysh)
		} else {
			f = fyshWithValue(fysh.Invalid, s.input[start:s.peek])
		}
	default:
		// left swimming fysh
		for ch := s.periscope(); isEye(ch); ch = s.reel() {
		}
		ch := s.periscope()
		if isScale(ch) {
			for ch := s.periscope(); isScale(ch); ch = s.reel() {
				if ch == '-' {
					f.Type = fysh.Bones
				} // check if its a floating point number
			}

			// (end of the fysh) <((><
			if s.match("><") {
				if f.Type != fysh.Bones {
					f.Type = fysh.Scales
				} // if not a floating point number then its an integer
			} else {
				f.Type = fysh.Invalid
			}
		} else {
			for ch := s.periscope(); isIdentBody(ch); ch = s.reel() {
			}
			if s.match("><") {
				if s.expect('<') { // <><< (decrement)
					f.Type = fysh.Dec
				} else { // <>< (identifier)
					f.Type = fysh.Ident
				}
			}
		}
		f.Value = s.input[start:s.peek]
	}
	return f
}

// Handles the '>' (greater than) character and determines the appropriate fysh type
func (s *Scanner) rt(start int) fysh.Fysh {
	var f fysh.Fysh

	switch s.periscope() {
	case '(': // >(
		s.reel()
		for ch := s.periscope(); isIdentBody(ch); ch = s.reel() {
		}
		if s.expect(')') {
			f.Type = fysh.Sub
		}
		f.Value = s.input[start:s.peek]
	case '>': // >>
		s.reel()
		if s.expect('<') { // >>< (increment)
			for ch := s.periscope(); isIdentBody(ch); ch = s.reel() {
			}
			if s.expect('>') {
				f.Type = fysh.Inc
			}
			f.Value = s.input[start:s.peek]
		} else {
			f = newFysh(fysh.RShift)
		}
	case '<': // ><
		f = s.rightFysh(start)
	}
	return f
}

// Handles the '><' character and determines the appropriate fysh type (right swimming fysh)
func (s *Scanner) rightFysh(start int) fysh.Fysh {
	var f fysh.Fysh
	closeFysh, noValue := false, false

	s.reel()
	switch ch := s.periscope(); ch {
	case '#': // ><# (grilled fysh)
		s.reel()
		closeFysh = true
		if s.match("##") {
			f.Type = fysh.Grilled
			noValue = true
		}
	case '\\': // ><\ (break fysh)
		s.reel()
		closeFysh = true
		if s.expect('/') {
			f.Type = fysh.BreakFysh
			noValue = true
		}
	case '/': // ><// (comment) or ></* (block comment)
		f = s.comment()
	case '>': // ><> // open bracket
		f.Type = fysh.LFysh
		noValue = true
		closeFysh = true
	default:
		if isScale(ch) { // ><{} (number) or ><(((@> (loop) or ><(((^> (if) or ><(((*> (else)
			closeFysh = true
			f.Type = fysh.Scales
			for ch := s.periscope(); isScale(ch); ch = s.reel() {
				if ch == '-' {
					f.Type = fysh.Bones
				}
			}
			if s.expect('@') { // ><(((@> (loop)
				f.Type = fysh.Loop
				noValue = true
			} else if s.expect('^') { // ><(((^> (if)
				f.Type = fysh.If
				noValue = true
			} else if s.expect('*') { // ><(((*> (else)
				f.Type = fysh.Else
				noValue = true
			}
			for ch := s.periscope(); isEye(ch); ch = s.reel() { // fysh eyes
			}
		} else { // identifier (variable)
			closeFysh = true
			f.Type = fysh.Ident
			for ch := s.periscope(); isIdentBody(ch); ch = s.reel() {
			}
		}
	}

	if closeFysh && s.periscope() != '>' {
		f.Type = fysh.Invalid
	}
	s.reel()
	if !noValue {
		f.Value = s.input[start:s.peek]
	} else {
		f = newFysh(f.Type)
	}

	return f
}

// Handles '></' for comments and block comments ><//> ></*> <*/><
func (s *Scanner) comment() fysh.Fysh {
	var f fysh.Fysh

	s.reel()
	if s.expect('*') && s.expect('>') {
		for {
			for ch := s.periscope(); ch != '<' && ch != 0; ch = s.reel() {
			}
			if s.periscope() == 0 {
				break
			} else if s.match("<*/>") && s.periscope() == '<' {
				f.Type = fysh.BlockC
				break
			}
		}
	} else if s.expect('/') && s.expect('>') {
		f.Type = fysh.Comment
		for ch := s.periscope(); ch != '\n' && ch != 0; ch = s.reel() {
		}
	}
	return f
}

// Processes the first character of the input and determines the appropriate fysh type
func (s *Scanner) ascii() fysh.Fysh {
	var f fysh.Fysh
	start := s.current

	switch s.ch {
	case 0:
		f = fyshWithValue(fysh.End, []byte{})
	case '<':
		f = s.lt(start)
	case '>':
		f = s.rt(start)
	case '^':
		f = newFysh(fysh.Caret)
	case '-':
		f = newFysh(fysh.Food)
	case '@':
		f = newFysh(fysh.Loop)
	case '[':
		f = newFysh(fysh.LTank)
	case ']':
		f = newFysh(fysh.RTank)
	case '(':
		if s.expect('+') {
			if s.expect('o') {
				f = newFysh(fysh.LAnchor)
			} else {
				f.Value = s.input[start:s.peek]
			}
		} else if isIdentStart(s.periscope()) {
			for ch := s.periscope(); isIdentBody(ch); ch = s.reel() {
			}
			if s.match(")<") {
				f.Type = fysh.Sub
			}
			f.Value = s.input[start:s.peek]
		} else {
			f = newFysh(fysh.LBowl)
		}
	case ')':
		f = newFysh(fysh.RBowl)
	case 'o':
		if s.expect('~') {
			// o~ or o~=
			if s.expect('=') || s.expect('≈') {
				f = newFysh(fysh.GTE)
			} else {
				f = newFysh(fysh.GT)
			}
		} else if s.expect('=') || s.expect('≈') {
			// o= shorthand
			f = newFysh(fysh.GTE)
		} else if s.match("+)") {
			f = newFysh(fysh.RAnchor)
		} else {
			f.Value = s.input[start:s.peek]
		}
	case '~':
		if s.expect('o') {
			// ~o or ~o=
			if s.expect('=') || s.expect('≈') {
				f = newFysh(fysh.LTE)
			} else {
				f = newFysh(fysh.LT)
			}
			// ~=
		} else if s.expect('=') || s.expect('≈') {
			f = newFysh(fysh.NEq)
		} else {
			f = newFysh(fysh.Water)
		}
	case '=':
		if s.expect('o') {
			f = newFysh(fysh.LTE)
		} else if s.expect('=') || s.expect('≈') {
			f = newFysh(fysh.Eq)
		} else {
			f = newFysh(fysh.Assign)
		}
	case '&':
		if s.expect('&') {
			f = newFysh(fysh.LAnd)
		} else {
			f = newFysh(fysh.BWAnd)
		}
	case '|':
		if s.expect('|') {
			f = newFysh(fysh.LOr)
		} else {
			f = newFysh(fysh.BWOr)
		}
	case '!':
		if s.expect('!') {
			f = newFysh(fysh.LNot)
		} else {
			f = newFysh(fysh.BWNot)
		}
	}
	return f
}

const (
	// variation selector
	EMOJIFY = 0xFE0F
	// zero width joiner
	ZWJ = 0x200D

	// Emoji skin tone modifier
	// https://en.wikipedia.org/wiki/Fitzpatrick_scale
	SKIN_MIN = 0x1F3FB // type 1-2
	SKIN_MAX = 0x1F3FF // type 6
)

func (s *Scanner) unicode() fysh.Fysh {
	start := s.current
	var f fysh.Fysh

	switch s.ch {
	case '⧽', '⟩', '⟫', '〉', '⦄', '⦆', '⦈', '⦊', '⦌', '⦎', '⦐', '⦒', '⦔', '⦖', '〉', '❭', '❯', '❱', '❳', '❵':
		f = s.rt(start)
	case '🦑':
		f = newFysh(fysh.Squid)
	case '💝', '☙', '♥', '❣', '❥', '❦', '❧', '🎔', '🖤', '💙', '💚', '💛', '💜', '🧡', '🤍', '🤎', '🩶', '🩷', '🩵', '💓', '💕', '💖', '💗', '💘', '🫀', '💌', '💞', '💟', '🫶', '♡':
		s.expect(EMOJIFY)
		if ch := s.periscope(); ch >= SKIN_MIN && ch <= SKIN_MAX {
			s.reel()
		}
		f = newFysh(fysh.Mul)
	// special heart
	case '❤':
		if s.expect(EMOJIFY) {
			// ZWJ
			if s.expect(ZWJ) {
				if s.expect('🔥') || s.expect('🩹') {
					f = newFysh(fysh.Mul)
				} else {
					// unexpected ZWJ pair
					f.Type = fysh.Invalid
					f.Value = s.input[start:s.peek]
				}
			} else {
				// red heart emoji
				f = newFysh(fysh.Mul)
			}
		} else {
			// normal heart
			f = newFysh(fysh.Mul)
		}
	case '💔':
		f = newFysh(fysh.Div)
	case '≈':
		if s.expect('≈') || s.expect('=') {
			f = newFysh(fysh.Eq)
		} else if s.expect('o') {
			f = newFysh(fysh.LTE)
		} else {
			f = newFysh(fysh.Assign)
		}
	case '🌀':
		f = newFysh(fysh.Loop)
	case '⚓':
		f = newFysh(fysh.LAnchor)
	case '🫧':
		for ch := s.periscope(); ch != '🫧' && ch != 0; ch = s.reel() {
		}
		if s.expect('🫧') {
			f.Type = fysh.String
		}
		f.Value = s.input[start:s.peek]
	}
	return f
}

// Goes onto the next fysh token's start
func (s *Scanner) NextFysh() fysh.Fysh {
	var f fysh.Fysh

	s.skipSpace()

	if s.ch > unicode.MaxASCII {
		f = s.unicode()
	} else {
		f = s.ascii()
	}

	s.reel()
	return f
}

func fyshWithValue(t fysh.Species, v []byte) fysh.Fysh {
	return fysh.Fysh{Type: t, Value: v}
}
func newFysh(t fysh.Species) fysh.Fysh {
	return fysh.Fysh{Type: t, Value: []byte(t.String())}
}

func (s *Scanner) skipSpace() {
	for s.ch == ' ' || s.ch == '\t' || s.ch == '\n' || s.ch == '\r' {
		s.reel()
	}
}
