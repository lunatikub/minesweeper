package solver

import "fmt"

// Value from 0 to 8 are used for uncovered cell
const (
	Covered = 9
	Flagged = 10
)

// Cell of the grid
type Cell struct{ Y, X int }

// Neighbors relative coordinate of neighbors
//  [-1, -1] [-1,  0] [-1, 1]
//  [ 0, -1] < Cell > [ 0, 1]
//  [ 1, -1] [ 1,  0] [ 1, 1]
var Neighbors = []Cell{
	{0, 1}, {1, 1}, {1, 0}, {1, -1},
	{0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
}

// CheckCoord if the coordinates are not out of bounds.
func CheckCoord(grid [][]int, y, x int) bool {
	return (y >= 0 && y < len(grid)) && (x >= 0 && x < len(grid[0]))
}

// NewGrid create a grid of size width * height
func NewGrid(height, width int, initValue int) [][]int {
	grid := make([][]int, height)
	for i := range grid {
		grid[i] = make([]int, width)
	}
	for i, row := range grid {
		for j := range row {
			grid[i][j] = initValue
		}
	}
	return grid
}

func getAdjacentMines(grid [][]int) [][]int {
	adjacentMines := NewGrid(len(grid), len(grid[0]), 0)
	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[0]); j++ {
			if grid[i][j] != Flagged {
				for _, n := range Neighbors {
					y := i + n.Y
					x := j + n.X
					if CheckCoord(grid, y, x) && grid[y][x] == Flagged {
						adjacentMines[i][j]++
					}
				}
			}
		}
	}
	return adjacentMines
}

// Solve a static grid configuration.
// Return the list of empty cells and mines to flag.
func Solve(grid [][]int) ([]Cell, []Cell) {
	adjacentMines := getAdjacentMines(grid)
	fmt.Println("adjacent")
	for _, row := range adjacentMines {
		for _, v := range row {
			if v == Flagged {
				fmt.Printf(" F ")
			} else {
				fmt.Printf("%2v ", v)
			}
		}
		fmt.Println()
	}
	cfg := getSubConfiguration(grid)
	A := getMatrix(grid, cfg, adjacentMines)
	gaussJordan(A)
	lower, upper := getBounds(A)
	empty := getEmpty(A, cfg, &lower, &upper)
	mines := getMines(A, cfg, &lower, &upper)
	return empty, mines
}
