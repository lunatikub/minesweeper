package bot

import "log"

type matrix struct {
	M          [][]int
	upperBound []int
	lowerBound []int
}

// create a new matrix of dims (n x m)
func newMatrix(h, w int) *matrix {
	m := new(matrix)
	m.M = make([][]int, h)
	for i := range m.M {
		m.M[i] = make([]int, w)
	}
	m.upperBound = make([]int, h)
	m.lowerBound = make([]int, h)
	return m
}

// Get bounds should be done after rowReduction
func (m *matrix) getBounds() {
	for y, line := range m.M {
		upperBound := 0
		lowerBound := 0
		// don't process the augmented column
		for _, v := range line[:len(line)-1] {
			if v > 0 {
				upperBound += v
			} else if v < 0 {
				lowerBound += v
			}
		}
		m.upperBound[y] = upperBound
		m.lowerBound[y] = lowerBound
	}
}

// Swap lines 'i' and 'j'
func swapLine(M [][]int, i, j int) {
	for k := 0; k < len(M[i]); k++ {
		M[i][k], M[j][k] = M[j][k], M[i][k]
	}
}

// Multilply each element of the line 'i' by lambda
func multLine(M [][]int, i, lambda int) {
	for k := 0; k < len(M[i]); k++ {
		M[i][k] *= lambda
	}
}

// Add to each element of the line 'i' the element of the line 'j'
// with same index mutiply by lambda.
func addLine(M [][]int, i, j, lambda int) {
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

// Gauss-Jordan elimination can solve a system of equations AX = B,
// where A is an (n × m) matrix of rank r, B is a fixed vector,
// and X the unknown vector. We create a table with n rows and m + 1 columns
// by bordering the matrix A by the vector B. We reduce the matrix in
// a row-echelon form.
func gaussJordan(M [][]int) {
	log.Printf("[matrix] gauss-jordan row-echelon form")
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
				swapLine(M, i, r)
			}
			if M[i][j] != 1 {
				multLine(M, i, 1/M[i][j])
			}
			for k := 0; k < len(M); k++ {
				if k != i && M[k][j] != 0 {
					addLine(M, k, i, -M[k][j])
				}
			}
		}
		i++
		j++
	}
}

// Return true if the matrix are equal, otherwise return false
func eq(M1, M2 [][]int) bool {
	for y, line := range M1 {
		for x, v := range line {
			if M2[y][x] != v {
				return false
			}
		}
	}
	return true
}
