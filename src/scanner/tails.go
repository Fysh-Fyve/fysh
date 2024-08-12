package scanner

func IsLeftTailSwitch(ch rune) bool {
	switch ch {
	case '<', '⧼', '⟨', '⟪', '〈', '⦃', '⦅', '⦇', '⦉', '⦋', '⦍', '⦏', '⦑', '⦓', '⦕', '〈', '❬', '❮', '❰', '❲', '❴':
		return true
	default:
		return false
	}
}
