package bot

import (
	"fmt"
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

	rccExpected := listCell{{0, 1}, {1, 1}, {2, 1}, {2, 0}}
	uccExpected := listCell{{0, 2}, {1, 2}, {2, 2}, {3, 2}, {3, 1}, {3, 0}}

	if !testListExpected(rccExpected, c.rcc) {
		t.Errorf("[connex] rcc not expected:%v, got:%v",
			rccExpected, c.rcc)
	}
	if !testListExpected(uccExpected, c.ucc) {
		t.Errorf("[connex] ucc not expected:%v, got:%v",
			uccExpected, c.ucc)
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
	m.dump()
	fmt.Println()
	m.gaussJordan()
	m.dump()
}
