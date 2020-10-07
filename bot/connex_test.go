package bot

import (
	"testing"
)

func testListExpected(le, lg listCell) bool {
	if len(le) != len(lg) {
		return false
	}
	for _, iter := range le {
		c, _ := lg.find(iter.y, iter.x)
		if c == nil {
			return false
		}
	}
	return true
}

func TestConnex(t *testing.T) {
	g := newGrid(5, 4)
	g.setGrid([][]int{
		{0, 1, 9, 9},
		{0, 1, 9, 9},
		{1, 1, 9, 9},
		{9, 9, 9, 9},
		{9, 9, 9, 9}})

	c := new(connex)
	c.getConnex(g, 0, 1)

	revealExpected := listCell{{0, 1}, {1, 1}, {2, 1}, {2, 0}}
	unrevealExpected := listCell{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {3, 1}, {3, 0}}

	if !testListExpected(revealExpected, c.listReveal) {
		t.Errorf("[connex] rcc not expected:%v, got:%v",
			revealExpected, c.listReveal)
	}
	if !testListExpected(unrevealExpected, c.listUnreveal) {
		t.Errorf("[connex] ucc not expected:%v, got:%v",
			unrevealExpected, c.listUnreveal)
	}
}

func TestBuildMatrix(t *testing.T) {
	g := newGrid(5, 4)
	g.setGrid([][]int{
		{0, 1, 9, 9},
		{0, 1, 9, 9},
		{1, 1, 9, 9},
		{9, 9, 9, 9},
		{9, 9, 9, 9}})
	c := new(connex)
	c.getConnex(g, 0, 1)
	m := c.buildMatrix(g)
	if !eq(m, [][]int{
		{1, 1, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 1},
		{0, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 1, 1, 1}}) {
		t.Errorf("RowReduction")
	}
}
