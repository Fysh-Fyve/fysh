package scanner

import (
	"fmt"
	"unicode"
	"unicode/utf8"

	"github.com/cbebe/go-fysh/fysh"
)

type Scanner struct {
	input   string
	current int
	peek    int
	ch      rune
}

// Checks if the character can be the start of an identifier
func isIdentStart(c rune) bool {
	switch c {
	case '_':
		fallthrough
	case '^':
		return true
	default:
		// We can literally start with numbers
		return unicode.IsLetter(c) || unicode.IsNumber(c) || c > unicode.MaxASCII
	}
}

func isIdentBody(c rune) bool {
	switch c {
	case '_':
		fallthrough
	case ' ':
		fallthrough
	case '^':
		fallthrough
	case '-':
		return true
	default:
		return unicode.IsLetter(c) || unicode.IsNumber(c) || c > unicode.MaxASCII
	}
}

func New(input string) *Scanner {
	s := &Scanner{input: input}
	s.reel()
	return s
}

func isScale(ch rune) bool {
	switch ch {
	case '{':
		fallthrough
	case '}':
		fallthrough
	case '(':
		fallthrough
	case ')':
		return true
	default:
		return false
	}
}

func (s *Scanner) expect(b rune) bool {
	res := s.periscope() == b
	if res {
		s.reel()
	}
	return res
}

func (s *Scanner) match(str string) bool {
	for _, v := range str {
		if !s.expect(v) {
			return false
		}
	}
	return true
}

func (s *Scanner) lt(start int) fysh.Fysh {
	var f fysh.Fysh
	switch s.periscope() {
	case '~':
		s.reel()
		f = newFysh(fysh.Squid)
	case '/':
		s.reel()
		if s.expect('3') {
			f = newFysh(fysh.Div)
		} else {
			f.Type = fysh.Invalid
			f.Value = string(s.input[start:s.peek])
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
			f.Type = fysh.Invalid
			f.Value = string(s.input[start:s.peek])
		}
	default:
		// left fysh
		for ch := s.periscope(); ch == 'o' || ch == '°'; ch = s.reel() {
		}
		ch := s.periscope()
		if isScale(rune(ch)) {
			for ch := s.periscope(); isScale(rune(ch)); ch = s.reel() {
			}
			if s.match("><") {
				f.Type = fysh.Scales
			} else {
				f.Type = fysh.Invalid
			}
		} else {
			for ch := s.periscope(); ch != '>' && ch != 0; ch = s.reel() {
			}
			if s.match("><") {
				if s.expect('<') {
					f.Type = fysh.Dec
				} else {
					f.Type = fysh.Ident
				}
			}
		}

		f.Value = string(s.input[start:s.peek])
	}

	return f
}

func (s *Scanner) comment() fysh.Fysh {
	var f fysh.Fysh

	s.reel()
	if s.expect('*') {
		if s.expect('>') {
			for {
				for ch := s.periscope(); ch != '<' && ch != 0; ch = s.reel() {
				}
				if s.periscope() == 0 {
					break
				} else if s.match("<*/>") {
					if s.periscope() == '<' {
						f.Type = fysh.BlockC
						break
					}
				}
			}
		}
	} else if s.expect('/') {
		if s.expect('>') {
			f.Type = fysh.Comment
			for ch := s.periscope(); ch != '\n' && ch != 0; ch = s.reel() {
			}
		}
	}
	return f
}

func (s *Scanner) rightFysh(start int) fysh.Fysh {
	var f fysh.Fysh
	// right fysh
	s.reel()
	ch := s.periscope()
	closeFysh, noValue := false, false
	switch ch {
	case '/':
		f = s.comment()
	case '>':
		f.Type = fysh.LFysh
		noValue = true
		closeFysh = true
	default:
		if isScale(rune(ch)) {
			closeFysh = true
			f.Type = fysh.Scales
			for ch := s.periscope(); isScale(ch); ch = s.reel() {
			}
			if s.expect('@') {
				f.Type = fysh.Loop
				noValue = true
			} else if s.expect('^') {
				f.Type = fysh.If
				noValue = true
			} else if s.expect('*') {
				f.Type = fysh.Else
				noValue = true
			}
			for ch := s.periscope(); ch == 'o' || ch == '°'; ch = s.reel() {
			}
		} else {
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
		f.Value = string(s.input[start:s.peek])
	} else {
		f = newFysh(f.Type)
	}

	return f
}

func (s *Scanner) gt(start int) fysh.Fysh {
	var f fysh.Fysh
	switch s.periscope() {
	case '(':
		s.reel()
		for ch := s.periscope(); ch != ')' && ch != 0; ch = s.reel() {
		}
		if s.expect(')') {
			f.Type = fysh.Sub
			f.Value = string(s.input[start:s.peek])
		}
	case '>':
		s.reel()
		if s.periscope() == '<' {
			// increment
			f.Type = fysh.Ident
			for ch := s.periscope(); ch != '>' && ch != 0; ch = s.reel() {
			}
			if s.expect('>') {
				f.Type = fysh.Inc
				f.Value = string(s.input[start:s.peek])
			}
		} else {
			f = newFysh(fysh.RShift)
		}
	case '<':
		f = s.rightFysh(start)
	}

	return f
}

func (s *Scanner) ascii() fysh.Fysh {
	var f fysh.Fysh
	start := s.current

	switch s.ch {
	case 0:
		f = fyshWithValue(fysh.End, "")
	case '<':
		f = s.lt(start)
	case '>':
		f = s.gt(start)
	case '^':
		f = newFysh(fysh.Caret)
	case '-':
		f = newFysh(fysh.Food)
	case '[':
		f = newFysh(fysh.LTank)
	case ']':
		f = newFysh(fysh.RTank)
	case '(':
		if s.expect('+') {
			if s.expect('o') {
				f = newFysh(fysh.LAnchor)
			} else {
				f.Value = string(s.input[start:s.peek])
			}
		} else if isIdentStart(s.periscope()) {
			for ch := s.periscope(); isIdentBody(ch); ch = s.reel() {
			}
			if s.match(")<") {
				f.Type = fysh.Sub
			}
			f.Value = string(s.input[start:s.peek])
		} else {
			f = newFysh(fysh.LBowl)
		}
	case ')':
		f = newFysh(fysh.RBowl)
	case 'o':
		if s.expect('~') {
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
			f.Value = string(s.input[start:s.peek])
		}
	case '~':
		if s.expect('o') {
			if s.expect('=') || s.expect('≈') {
				f = newFysh(fysh.LTE)
			} else {
				f = newFysh(fysh.LT)
			}
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

func (s *Scanner) unicode() fysh.Fysh {
	var f fysh.Fysh
	switch s.ch {
	case '🦑':
		f = newFysh(fysh.Squid)
	case '💝':
		fallthrough
	case '☙':
		fallthrough
	case '♥':
		fallthrough
	case '❣':
		fallthrough
	case '❤':
		fallthrough
	case '❥':
		fallthrough
	case '❦':
		fallthrough
	case '❧':
		fallthrough
	case '🎔':
		fallthrough
	case '🖤':
		fallthrough
	case '💙':
		fallthrough
	case '💚':
		fallthrough
	case '💛':
		fallthrough
	case '💜':
		fallthrough
	case '🧡':
		fallthrough
	case '🤍':
		fallthrough
	case '🤎':
		fallthrough
	case '🩶':
		fallthrough
	case '🩷':
		fallthrough
	case '🩵':
		fallthrough
	case '💓':
		fallthrough
	case '💕':
		fallthrough
	case '💖':
		fallthrough
	case '💗':
		fallthrough
	case '💘':
		fallthrough
	case '🫀':
		fallthrough
	case '💌':
		fallthrough
	case '💞':
		fallthrough
	case '💟':
		fallthrough
	case '🫶':
		fallthrough
	case '♡':
		f = newFysh(fysh.Mul)
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
	}
	return f
}

func (s *Scanner) NextFysh() fysh.Fysh {
	var f fysh.Fysh

	s.skipSpace()

	switch ch := s.ch; {
	case ch > unicode.MaxASCII:
		f = s.unicode()
	default:
		f = s.ascii()
	}

	if f.Type == fysh.Invalid {
		fmt.Printf("%c", s.ch)
	}
	s.reel()
	return f
}

func fyshWithValue(t fysh.Species, v string) fysh.Fysh {
	return fysh.Fysh{Type: t, Value: v}
}
func newFysh(t fysh.Species) fysh.Fysh {
	return fysh.Fysh{Type: t, Value: t.String()}
}

func (s *Scanner) skipSpace() {
	for s.ch == ' ' || s.ch == '\t' || s.ch == '\n' || s.ch == '\r' {
		s.reel()
	}
}

func (s *Scanner) reel() rune {
	if s.peek >= len(s.input) {
		s.ch = 0
		s.current = s.peek
	} else {
		end := min(len(s.input), s.peek+4)
		val, width := utf8.DecodeRuneInString(s.input[s.peek:end])
		s.ch = val
		s.current = s.peek
		s.peek += width
	}
	return s.periscope()
}

func (s *Scanner) periscope() rune {
	if s.peek >= len(s.input) {
		return 0
	} else {
		end := min(len(s.input), s.peek+4)
		val, _ := utf8.DecodeRuneInString(s.input[s.peek:end])
		return val
	}
}
