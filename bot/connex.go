package bot

import "fmt"

// cell coordinates
type cell struct {
	y, x int
}

// list of cell
type listCell []cell

// get the connections between cells revealed
// and neighbors unrevealed
type connex struct {
	rcc listCell // list of reveal connex cells
	ucc listCell // list of unreveal connex cells
}

//  [-1, -1] [-1,  0] [-1, 1]
//  [ 0, -1] < Cell > [ 0, 1]
//  [ 1, -1] [ 1,  0] [ 1, 1]
var neighbors = []cell{
	{0, 1}, {1, 1}, {1, 0}, {1, -1},
	{0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
}

// check if the coordinates are valid
func check(h, w, y, x int) bool {
	return (y >= 0 && y < h) && (x >= 0 && x < w)
}

// return true if the coordinates are equals,
// otherwise return false
func (c *cell) eq(y, x int) bool {
	return c.y == y && c.x == x
}

// find the cell with the coordinates
func (lc listCell) find(y, x int) (*cell, int) {
	for idx, iter := range lc {
		if iter.eq(y, x) {
			return &iter, idx
		}
	}
	return nil, -1
}

// get the connections between cells
func (c *connex) getConnex(g *grid, y, x int) {
	for _, n := range neighbors {
		yn := y + n.y
		xn := x + n.x
		if check(g.h, g.w, yn, xn) {
			v := g.get(yn, xn)
			rc, _ := c.rcc.find(yn, xn)
			uc, _ := c.ucc.find(yn, xn)
			if v >= 1 && v <= 8 && rc == nil {
				c.rcc = append(c.rcc, cell{yn, xn})
				c.getConnex(g, yn, xn)
			} else if v == unreveal && uc == nil {
				c.ucc = append(c.ucc, cell{yn, xn})
			}
		}
	}
}

func (c *connex) buildMatrix(g *grid) *matrix {
	m := newMatrix(len(c.rcc), len(c.ucc)+1)

	for y, rc := range c.rcc {
		fmt.Printf("line: %d, rc: %d,%d\n", y, rc.y, rc.x)
		for _, n := range neighbors {
			yn := rc.y + n.y
			xn := rc.x + n.x
			if check(g.h, g.w, yn, xn) && g.get(yn, xn) == unreveal {
				fmt.Printf("unrevealed cell: %d, %d\n", yn, xn)
				_, x := c.ucc.find(yn, xn)
				m.set(y, x, 1)
			}
		}
		// TODO minnus nr neigh mines
		m.set(y, len(c.ucc), float64(g.cells[rc.y][rc.x]))
	}
	return m
}
