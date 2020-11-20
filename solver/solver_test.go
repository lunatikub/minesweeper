package solver

import (
	"testing"
)

func TestSolve(t *testing.T) {

	M := -1

	solution := [][]int{
		{0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 1, 1, 1, M},
		{0, 0, 0, 1, M, 1, 2, 2},
		{0, 0, 1, 2, 2, 1, 2, M},
		{1, 1, 2, M, 1, 0, 2, M},
		{1, M, 3, 3, 2, 1, 1, 1},
		{2, 3, M, 2, M, 1, 0, 0},
		{1, M, 2, 2, 1, 1, 0, 0},
	}

	grid := [][]int{
		{0, 0, 0, 0, 0, 0, 1, 9},
		{0, 0, 0, 1, 1, 1, 1, 9},
		{0, 0, 0, 1, 9, 9, 9, 9},
		{0, 0, 1, 2, 9, 9, 9, 9},
		{1, 1, 2, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9},
		{9, 9, 9, 9, 9, 9, 9, 9},
	}

	empty, mines := Solve(grid)

	for _, m := range mines {
		if solution[m.Y][m.X] != M {
			t.Errorf("Expected a mine at %v, get %v",
				m, solution[m.Y][m.X])
		}
	}
	for _, e := range empty {
		if solution[e.Y][e.X] == M {
			t.Errorf("Expected an empty at %v, get a mine", e)
		}
	}
}

func TestAdjacentMines(t *testing.T) {

	F := Flagged

	grid := [][]int{
		{0, 0, 0, 0, 0},
		{0, F, F, 0, 0},
		{0, F, 0, 0, F},
		{0, F, 0, F, 0},
		{F, 0, 0, F, 0},
	}

	expectedAdjacent := [][]int{
		{1, 2, 2, 1, 0},
		{2, 0, 0, 2, 1},
		{3, 0, 5, 3, 0},
		{3, 0, 4, 0, 3},
		{0, 2, 3, 0, 2},
	}

	adjacentMines := getAdjacentMines(grid)

	for i := 0; i < len(adjacentMines); i++ {
		for j := 0; j < len(adjacentMines[0]); j++ {
			if expectedAdjacent[i][j] != adjacentMines[i][j] {
				t.Errorf("Expected adjacent %v, get %v",
					expectedAdjacent, adjacentMines)
			}
		}
	}
}
