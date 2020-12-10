package main

import (
	"math/rand"
	"os"

	"github.com/lunatikub/minesweeper/solver"
)

func getCellList(solution [][]int) []solver.Cell {
	cellList := []solver.Cell{}
	for i := 0; i < len(solution); i++ {
		for j := 0; j < len(solution[0]); j++ {
			if i > 2 || j > 2 {
				cellList = append(cellList, solver.Cell{Y: i, X: j})
			}
		}
	}
	return cellList
}

func initMines(solution [][]int, cellList []solver.Cell, mines int) {
	n := 0
	for {
		if len(cellList) == 0 {
			panic("too much mines for the size of the grid")
		}
		c := rand.Intn(len(cellList))
		solution[cellList[c].Y][cellList[c].X] = mine
		cellList = append(cellList[:c], cellList[c+1:]...)
		n++
		if n == mines {
			break
		}
	}
}

func initAdjacent(solution [][]int) {
	for i := 0; i < len(solution); i++ {
		for j := 0; j < len(solution[0]); j++ {
			if solution[i][j] == 0 {
				for _, n := range solver.Neighbors {
					y := i + n.Y
					x := j + n.X
					if solver.CheckCoord(solution, y, x) && solution[y][x] == mine {
						solution[i][j]++
					}
				}
			}
		}
	}
}

func generateSolution(height, width, mines int) [][]int {
	solution := solver.NewGrid(width, height, 0)
	cellList := getCellList(solution)
	initMines(solution, cellList, mines)
	initAdjacent(solution)
	return solution
}

func setEmptyDFS(solution, grid [][]int, y, x int) {
	if solution[y][x] >= 1 && solution[y][x] <= 8 {
		grid[y][x] = solution[y][x]
		return
	}
	grid[y][x] = 0
	for _, n := range solver.Neighbors {
		yn := y + n.Y
		xn := x + n.X
		if solver.CheckCoord(solution, yn, xn) {
			if grid[yn][xn] == solver.Covered {
				setEmptyDFS(solution, grid, yn, xn)
			}
		}
	}
}

func setEmpty(solution, grid [][]int, empty []solver.Cell) {
	for _, e := range empty {
		if solution[e.Y][e.X] == mine {
			os.Exit(1)
		}
		setEmptyDFS(solution, grid, e.Y, e.X)
	}
}

func setMines(grid [][]int, mines []solver.Cell) {
	for _, m := range mines {
		grid[m.Y][m.X] = solver.Flagged
	}
}
