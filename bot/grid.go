package bot

// Grid of the minesweepers
type grid struct {
	cells [][]int // cells of the grid
	h, w  int     // height and widht of the grid
}

func newGrid(h, w int) *grid {
	g := new(grid)
	g.h = h
	g.w = w
	g.cells = make([][]int, g.h)
	for i := range g.cells {
		g.cells[i] = make([]int, g.w)
		for j := range g.cells[i] {
			g.cells[i][j] = unreveal
		}
	}
	return g
}

// set a cell of the grid
func (g *grid) set(y, x, v int) {
	g.cells[y][x] = v
}

// get a cell of the grid
func (g *grid) get(y, x int) int {
	return g.cells[y][x]
}

// set a line of the grid
func (g *grid) setLine(y int, line []int) {
	for x, v := range line {
		g.set(y, x, v)
	}
}

// set the cells of the grid
func (g *grid) setGrid(cells [][]int) {
	for y, line := range cells {
		g.setLine(y, line)
	}
}
