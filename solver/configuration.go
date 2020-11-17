package solver

type list []cell

type configuration struct {
	unsolved list    // list of unsolved cells from the connected sub-graph
	covered  list    // list of covered cells adjacent to the unsolved cells
	edges    [][]int // edges between unsolved end covered cells
}

func (l list) find(y, x int) int {
	for i, iter := range l {
		if y == iter.y && x == iter.x {
			return i
		}
	}
	return -1
}

func (l list) exist(y, x int) bool {
	return l.find(y, x) != -1
}

//  [-1, -1] [-1,  0] [-1, 1]
//  [ 0, -1] < Cell > [ 0, 1]
//  [ 1, -1] [ 1,  0] [ 1, 1]
var neighbors = []cell{
	{0, 1}, {1, 1}, {1, 0}, {1, -1},
	{0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
}

// check if the coordinates are not out of bounds.
func checkCoord(grid [][]int, y, x int) bool {
	return (y >= 0 && y < len(grid)) && (x >= 0 && x < len(grid[0]))
}

// Get the sub-graph of uncovered cells from cell {y, x}
func getSubGraph(grid [][]int, y, x int, uncovered *list) {
	*uncovered = append(*uncovered, cell{y, x})
	for _, n := range neighbors {
		yn := y + n.y
		xn := x + n.x
		if checkCoord(grid, yn, xn) {
			v := grid[yn][xn]
			if !uncovered.exist(yn, xn) && v >= 1 && v <= 8 {
				getSubGraph(grid, yn, xn, uncovered)
			}
		}
	}
}

// Get the list of unique unsolved cells
func (cfg *configuration) getUnsolved(grid [][]int, uncovered *list) {
	for _, ce := range *uncovered {
		flag := false
		for _, n := range neighbors {
			yn := ce.y + n.y
			xn := ce.x + n.x
			if checkCoord(grid, yn, xn) && grid[yn][xn] == covered {
				flag = true
				break
			}
		}
		if flag {
			cfg.unsolved = append(cfg.unsolved, ce)
		}
	}
	cfg.edges = make([][]int, len(cfg.unsolved))
	for i := range cfg.edges {
		cfg.edges[i] = make([]int, 0)
	}
}

// Get the list of unique adjacent covered cells.
func (cfg *configuration) getCovered(grid [][]int) {
	for i, ce := range cfg.unsolved {
		for _, n := range neighbors {
			yn := ce.y + n.y
			xn := ce.x + n.x
			if checkCoord(grid, yn, xn) {
				if grid[yn][xn] == covered {
					edge := cfg.covered.find(yn, xn)
					if edge == -1 {
						cfg.covered = append(cfg.covered, cell{yn, xn})
						edge = len(cfg.covered) - 1
					}
					cfg.edges[i] = append(cfg.edges[i], edge)
				}
			}
		}
	}
}

// Find an unsolved cell in the grid.
func findUnsolved(grid [][]int) (int, int) {
	for y, line := range grid {
		for x, v := range line {
			if v >= 1 && v <= 8 {
				for _, n := range neighbors {
					yn := y + n.y
					xn := x + n.x
					if checkCoord(grid, yn, xn) &&
						grid[yn][xn] == covered {
						return y, x
					}
				}
			}
		}
	}
	panic("impossible to find an unsolved cell")
}

// Get a sub-configuration from a grid.
func getSubConfiguration(grid [][]int) *configuration {
	cfg := configuration{}
	uncovered := list{}
	y, x := findUnsolved(grid)
	getSubGraph(grid, y, x, &uncovered)
	cfg.getUnsolved(grid, &uncovered)
	cfg.getCovered(grid)
	return &cfg
}
