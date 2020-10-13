package bot

import (
	"time"

	"github.com/micmonay/keybd_event"
)

const (
	inc = iota // left / up
	dec        // right / down
	left
	right
	down
	up
	focus
	setEmpty
	setMine
)

// Interaction manage all interactions with the game
type interaction struct {
	kb   keybd_event.KeyBonding // keys mapping
	y, x int                    // current position
	h, w int                    // grid dims
}

// NewInteraction create a new instance of interaction
func newInteraction(h, w int) *interaction {
	var err error
	i := new(interaction)
	i.kb, err = keybd_event.NewKeyBonding()
	if err != nil {
		panic(err)
	}
	i.h = h
	i.w = w
	i.getFocus()
	return i
}

type move struct {
	y, x       int
	yDir, xDir int
	click      int
}

func getDirection(start, end, dim int) (int, int) {
	m1 := 0
	m2 := 0

	if start < end {
		m1 = end - start
		m2 = start + dim - end
	} else if start > end {
		m1 = dim - start + end
		m2 = start - end
	}
	if m1 < m2 {
		return m1, inc
	}
	return m2, dec
}

func (i *interaction) getMove(y, x int) move {
	var m move
	var dirX, dirY int

	m.x, dirX = getDirection(i.x, x, i.w)
	m.y, dirY = getDirection(i.y, y, i.h)

	if dirX == inc {
		m.xDir = right
	} else {
		m.xDir = left
	}

	if dirY == inc {
		m.yDir = down
	} else {
		m.yDir = up
	}

	return m
}

// GetFocus get the focus on the gnome-mines window
func (i *interaction) getFocus() {
	i.pressKey(focus, 1)
	i.pressKey(left, 1)
}

func (i *interaction) move(y, x, action int) {
	move := i.getMove(y, x)
	i.pressKey(move.yDir, move.y)
	i.pressKey(move.xDir, move.x)
	i.pressKey(action, 1)
	i.x = x
	i.y = y
}

func (i *interaction) pressKey(move, n int) {
	i.kb.Clear()
	switch move {
	case setEmpty:
		i.kb.SetKeys(keybd_event.VK_SPACE)
	case setMine:
		i.kb.HasCTRL(true)
		i.kb.SetKeys(keybd_event.VK_SPACE)
	case focus:
		i.kb.SetKeys(keybd_event.VK_ENTER)
	case right:
		i.kb.SetKeys(keybd_event.VK_RIGHT)
	case left:
		i.kb.SetKeys(keybd_event.VK_LEFT)
	case up:
		i.kb.SetKeys(keybd_event.VK_UP)
	case down:
		i.kb.SetKeys(keybd_event.VK_DOWN)
	}

	for k := 0; k < n; k++ {
		i.kb.Press()
		time.Sleep(50 * time.Millisecond)
		i.kb.Release()
	}
}
