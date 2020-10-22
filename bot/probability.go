package bot

import (
	"log"
)

// Return true if the grid is valid, otherwise return false.
func checkGrid(g *grid, totMine int) bool {
	mines := 0
	for y, line := range g.cells {
		for x, v := range line {
			nrMine := 0
			if v == flagged {
				mines++
			}
			if isRevealedValue(v) {
				for _, n := range neighbors {
					yn := y + n.y
					xn := x + n.x
					if check(g.h, g.w, yn, xn) && g.get(yn, xn) == flagged {
						nrMine++
					}
				}
				if nrMine != v {
					return false
				}
			}
		}
	}
	return mines <= totMine
}

// Aggregate the solution found to the probabilistic grid.
func aggregateSolution(g, p *grid) {
	for y, line := range g.cells {
		for x, v := range line {
			if v == flagged {
				p.cells[y][x]++
			}
		}
	}
}

// Depth-first search possibles solutions
func dfs(g, p *grid, unreveal []cell, totMine int) int {

	if len(unreveal) == 0 {
		if checkGrid(g, totMine) {
			aggregateSolution(g, p)
			return 1
		}
		return 0
	}

	n := 0
	for _, v := range []int{flagged, 0} {
		c := unreveal[0]
		g.cells[c.y][c.x] = v
		n += dfs(g, p, unreveal[1:], totMine)
		g.cells[c.y][c.x] = covered
	}
	return n
}

// Get the best probabilistic empty cell.
func getEmptyProbabilistic(g *grid, unreveal []cell, totMine int) cell {
	p := newGrid(g.h, g.w, 0)
	n := dfs(g, p, unreveal, totMine)
	for y, line := range p.cells {
		for x, v := range line {
			p.cells[y][x] = v * 100 / n
		}
	}
	minCellMine := cell{-1, -1}
	minProbMine := 100
	for _, c := range unreveal {
		if p.cells[c.y][c.x] < minProbMine {
			minCellMine = c
			minProbMine = p.cells[c.y][c.x]
		}
	}
	log.Printf("[probability] set empty cell {%v,%v} <%v%%>",
		minCellMine.y, minCellMine.x,
		p.cells[minCellMine.y][minCellMine.x])
	return minCellMine
}
