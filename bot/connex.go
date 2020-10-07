package bot

// cell coordinates
type cell struct {
	y, x int
}

// list of cell
type listCell []cell

// get the connex cells revealed
// and neighbors unrevealed
type connex struct {
	listReveal   listCell // list of reveal connex cells
	listUnreveal listCell // list of unreveal connex cells
}

//  [-1, -1] [-1,  0] [-1, 1]
//  [ 0, -1] < Cell > [ 0, 1]
//  [ 1, -1] [ 1,  0] [ 1, 1]
var neighbors = []cell{
	{0, 1}, {1, 1}, {1, 0}, {1, -1},
	{0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
}

// check if the coordinates are valid (not out of bounds)
func check(h, w, y, x int) bool {
	return (y >= 0 && y < h) && (x >= 0 && x < w)
}

// return true if the coordinates are equals,
// otherwise return false
func (c *cell) eq(y, x int) bool {
	return c.y == y && c.x == x
}

// find the cell with the coordinates in the list
func (l listCell) find(y, x int) (*cell, int) {
	for idx, iter := range l {
		if iter.eq(y, x) {
			return &iter, idx
		}
	}
	return nil, -1
}

// Get the revealed connex cells and unrevealed neighbords
// Example: [019] (3x3 grid)
//          [019]
//          [999]
// List of revealed connex cells from {0,1}: {{0,1}, {1,1}}
// List of unrevealed neighbords: {{0,2}, {1,2}, {2,0}, {2,1}, {2,2}}
func (c *connex) getConnex(g *grid, y, x int) {
	c.listReveal = append(c.listReveal, cell{y, x})
	for _, n := range neighbors {
		yn := y + n.y
		xn := x + n.x
		if check(g.h, g.w, yn, xn) {
			v := g.get(yn, xn)
			r, _ := c.listReveal.find(yn, xn)
			u, _ := c.listUnreveal.find(yn, xn)
			if v >= 1 && v <= 8 && r == nil {
				c.getConnex(g, yn, xn)
			} else if v == unreveal && u == nil {
				c.listUnreveal = append(c.listUnreveal, cell{yn, xn})
			}
		}
	}
}

// Create an augmented matrix with n rows and m + 1 columns
// by bordering the matrix A by the vector B.
// A is a matrix n x m where n is the number of revealed connex cells
// and m is the number of unrevealed cells in the neighborhood.
// B is a fix vector where values are the revealed number substract
// by the number of mines in the neighborhood.
func (c *connex) buildMatrix(g *grid) *matrix {
	m := newMatrix(len(c.listReveal), len(c.listUnreveal)+1) // augmented matrix
	for y, r := range c.listReveal {
		nrMines := 0
		for _, n := range neighbors {
			yn := r.y + n.y
			xn := r.x + n.x
			if check(g.h, g.w, yn, xn) {
				v := g.get(yn, xn)
				if v == unreveal {
					// list index is the column index in the matrix
					_, x := c.listUnreveal.find(yn, xn)
					m.set(y, x, 1)
				} else if v == mine {
					nrMines++
				}
			}
		}
		// vector B of the augmented matrix
		m.set(y, len(c.listUnreveal), g.cells[r.y][r.x]-nrMines)
	}
	return m
}
