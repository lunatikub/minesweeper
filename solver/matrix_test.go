package solver

import (
	"testing"
)

func TestGetMatrix(t *testing.T) {
	grid := [][]int{
		{0, 1, 9, 9},
		{0, 1, 9, 9},
		{0, 1, 2, 9},
		{0, 0, 2, 9},
		{1, 1, 2, 9},
		{9, 9, 9, 9}}
	adjacentMines := NewGrid(len(grid), len(grid[0]), 0)
	cfg := getSubConfiguration(grid)
	A := getMatrix(grid, cfg, adjacentMines)

	if !eqMatrix(A, [][]int{
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2},
		{0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2},
		{0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}}) {
		t.Errorf("GaussJordan")
	}
}

func TestSwapLine(t *testing.T) {
	M := [][]int{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}}
	swapRow(M, 0, 2)
	if M[0][0] != 7 || M[0][1] != 8 || M[0][2] != 9 ||
		M[2][0] != 1 || M[2][1] != 2 || M[2][2] != 3 {
		t.Errorf("swapLine")
	}
}

func TestMultLine(t *testing.T) {
	M := [][]int{
		{1, 2, 3}}
	multiplyRow(M, 0, 2)
	if M[0][0] != 2 || M[0][1] != 4 || M[0][2] != 6 {
		t.Errorf("multLine")
	}
}

func TestAddLine(t *testing.T) {
	M := [][]int{
		{1, 2, 3},
		{3, 4, 5}}
	addRow(M, 1, 0, 2)
	if M[1][0] != 5 || M[1][1] != 8 || M[1][2] != 11 {
		t.Errorf("addLine")
	}
}

func TestPivot(t *testing.T) {
	M := [][]int{
		{1, 0},
		{0, 1},
		{0, 0},
		{0, 2}}
	p := pivot(M, 2, 1)
	if p != 3 {
		t.Errorf("pivot")
	}
}

func TestGaussJordan(t *testing.T) {
	M := [][]int{
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2},
		{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 2},
		{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}}
	gaussJordan(M)
	if !eqMatrix(M, [][]int{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 1, 0, 0, -1, 0, 0, 0, 0, -1},
		{0, 0, 0, 1, 0, 0, -1, 0, 0, 1, 1},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, -1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}}) {
		t.Errorf("GaussJordan")
	}
}
