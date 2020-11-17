package solver

// Map a configuration and a grid to a matrix.
func getMatrix(grid [][]int, cfg *configuration,
	adjacentMines [][]int) [][]int {
	N := len(cfg.unsolved)
	M := len(cfg.covered)
	A := newMatrix(N, M+1) // augmented matrix

	for i, u := range cfg.unsolved {
		for _, e := range cfg.edges[i] {
			A[i][e] = 1
		}
		A[i][M] = grid[u.y][u.x] - adjacentMines[u.y][u.x]
	}
	return A
}

// Return true if the matrix are equal, otherwise return false
func eqMatrix(M1, M2 [][]int) bool {
	for y, line := range M1 {
		for x, v := range line {
			if M2[y][x] != v {
				return false
			}
		}
	}
	return true
}

// Swap rows 'i' and 'j'
func swapRow(M [][]int, i, j int) {
	for k := 0; k < len(M[i]); k++ {
		M[i][k], M[j][k] = M[j][k], M[i][k]
	}
}

// Multilply each element of the row 'i' by lambda
func multiplyRow(M [][]int, i, lambda int) {
	for k := 0; k < len(M[i]); k++ {
		M[i][k] *= lambda
	}
}

// Add to each element of the row 'i' the element of the line 'j'
// mutiply by lambda.
func addRow(M [][]int, i, j, lambda int) {
	for k := 0; k < len(M[i]); k++ {
		M[i][k] += lambda * M[j][k]
	}
}

// Return the index of the first pivot not null in the column 'j'
// from line 'i'.
func pivot(M [][]int, i, j int) int {
	k := i
	for {
		if !(k < len(M) && M[k][j] == 0) {
			break
		}
		k++
	}
	if k == len(M) {
		return -1
	}
	return k
}

// Gauss-Jordan elimination can solve a  ystem of linear equations AX = B,
// where A is an (n × m) matrix of rank r, B is a fixed vector,
// and X the unknown vector. We create a table with n rows and m + 1 columns
// by bordering the matrix A by the vector B and we reduce the matrix in
// a row-echelon form.
func gaussJordan(M [][]int) {
	i := 0
	j := 0
	for {
		if !(i < len(M) && j < len(M[0])) {
			break
		}
		r := pivot(M, i, j)
		if r == -1 {
			j++
		} else {
			if r != i {
				swapRow(M, i, r)
			}
			if M[i][j] != 1 {
				multiplyRow(M, i, 1/M[i][j])
			}
			for k := 0; k < len(M); k++ {
				if k != i && M[k][j] != 0 {
					addRow(M, k, i, -M[k][j])
				}
			}
		}
		i++
		j++
	}
}
