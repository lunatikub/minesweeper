package bot

import (
	"testing"
)

func TestProb1(t *testing.T) {
	g := newGrid(8, 8, flagged)
	g.setGrid([][]int{
		{0, 0, 0, 0, 0, 1, 10, 1},
		{0, 0, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 10, 1, 0, 0, 0},
		{1, 1, 2, 1, 1, 0, 0, 0},
		{1, 10, 2, 1, 1, 1, 2, 2},
		{3, 3, 3, 10, 2, 2, 10, 10},
		{10, 10, 2, 2, 9, 9, 3, 9},
		{2, 2, 1, 1, 9, 9, 9, 9}})
	c := new(connex)
	y, x := findUnresolvedCell(g)
	c.revealedUnrevealed(g, y, x)
	c.unsolved(g)

	cell := getEmptyProbabilistic(g, c.listUnreveal, 10)
	if cell.y != 6 || cell.x != 7 {
		t.Errorf("probability: expected:{%v,%v}, got:{%v,%v}",
			6, 7, cell.y, cell.x)

	}
}

func TestProb2(t *testing.T) {
	g := newGrid(16, 16, covered)
	g.setGrid([][]int{
		{0, 0, 0, 0, 0, 1, 10, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{0, 0, 1, 1, 1, 1, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{0, 0, 2, 10, 2, 0, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{1, 1, 3, 10, 3, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 2, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}})
	c := new(connex)
	y, x := findUnresolvedCell(g)
	c.revealedUnrevealed(g, y, x)
	c.unsolved(g)
	cell := getEmptyProbabilistic(g, c.listUnreveal, 10)
	if cell.y != 6 || cell.x != 0 {
		t.Errorf("probability: expected:{%v,%v}, got:{%v,%v}",
			6, 0, cell.y, cell.x)

	}
}
