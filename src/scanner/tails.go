package scanner

func IsLeftTailSlice(ch rune) bool {
	leftTails := []rune{'<', '⧼', '⟨', '⟪', '〈', '⦃', '⦅', '⦇', '⦉', '⦋', '⦍', '⦏', '⦑', '⦓', '⦕', '〈', '❬', '❮', '❰', '❲', '❴'}
	for _, tale := range leftTails {
		if ch == tale {
			return true
		}
	}
	return false
}

func IsLeftTailSwitch(ch rune) bool {
	switch ch {
	case '<', '⧼', '⟨', '⟪', '〈', '⦃', '⦅', '⦇', '⦉', '⦋', '⦍', '⦏', '⦑', '⦓', '⦕', '〈', '❬', '❮', '❰', '❲', '❴':
		return true
	default:
		return false
	}
}

func IsRightTailSlice(ch rune) bool {
	rightTails := []rune{'>', '⧽', '⟩', '⟫', '〉', '⦄', '⦆', '⦈', '⦊', '⦌', '⦎', '⦐', '⦒', '⦔', '⦖', '〉', '❭', '❯', '❱', '❳', '❵'}
	for _, tale := range rightTails {
		if ch == tale {
			return true
		}
	}
	return false
}

func IsRightTailSwitch(ch rune) bool {
	switch ch {
	case '>', '⧽', '⟩', '⟫', '〉', '⦄', '⦆', '⦈', '⦊', '⦌', '⦎', '⦐', '⦒', '⦔', '⦖', '〉', '❭', '❯', '❱', '❳', '❵':
		return true
	default:
		return false
	}
}
