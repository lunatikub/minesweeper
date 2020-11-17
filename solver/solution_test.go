package solver

import (
	"testing"
)

func TestSolution(t *testing.T) {
	// reduced row echelon form
	A := [][]int{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 1, 0, 0, -1, 0, 0, 0, 0, -1},
		{0, 0, 0, 1, 0, 0, -1, 0, 0, 1, 1},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, -1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}}

	lower, upper := getBounds(A)
	empty := getEmpty(A, &lower, &upper)
	mines := getMines(A, &lower, &upper)

	emptyExpected := []int{0, 2, 7}
	minesExpected := []int{1, 5}

	if len(emptyExpected) != len(empty) {
		t.Errorf("[solution] empty expected:%v, got:%v", emptyExpected, empty)
	}
	for i := range empty {
		if emptyExpected[i] != empty[i] {
			t.Errorf("[solution] empty expected:%v, got:%v", emptyExpected, empty)
		}
	}

	if len(minesExpected) != len(mines) {
		t.Errorf("[solution] empty expected:%v, got:%v", emptyExpected, empty)
	}
	for i := range mines {
		if minesExpected[i] != mines[i] {
			t.Errorf("[solution] mines expected:%v, got:%v", minesExpected, mines)
		}
	}
}
