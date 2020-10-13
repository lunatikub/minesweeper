package bot

import (
	"testing"
)

func TestGetDirection(t *testing.T) {
	n, dir := getDirection(0, 5, 8)
	if n != 3 && dir != dec {
		t.Errorf("getDirection")
	}
	n, dir = getDirection(5, 0, 8)
	if n != 3 && dir != inc {
		t.Errorf("getDirection")
	}
	n, dir = getDirection(4, 5, 8)
	if n != 1 && dir != inc {
		t.Errorf("getDirection")
	}
	n, dir = getDirection(5, 4, 8)
	if n != 1 && dir != dec {
		t.Errorf("getDirection")
	}
}

func TestGetMove(t *testing.T) {
	inter := newInteraction(8, 8)
	move := inter.getMove(2, 7)
	if move.y != 2 || move.yDir != down ||
		move.x != 1 || move.xDir != left {
		t.Errorf("getDirection")
	}
}
