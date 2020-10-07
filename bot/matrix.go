package bot

import "fmt"

// structure used to manipulate simplified matrix
type matrix struct {
	A    [][]int
	n, m int // dims
}

// create a new matrix of dims (n x m)
func newMatrix(n, m int) *matrix {
	newM := new(matrix)
	newM.A = make([][]int, n)
	for i := range newM.A {
		newM.A[i] = make([]int, m)
	}
	newM.n = n
	newM.m = m
	return newM
}

// set a cell of the matrix
func (m *matrix) set(y, x, v int) {
	m.A[y][x] = v
}

// set a line of the matrix
func (m *matrix) setLine(y int, line []int) {
	copy(m.A[y], line)
}

// set the entire matrix
func (m *matrix) setMatrix(A [][]int) {
	for y, line := range A {
		m.setLine(y, line)
	}
}

// return true if the matrix are equal, otherwise return false
func eq(m *matrix, A [][]int) bool {
	for y, line := range A {
		for x, v := range line {
			if m.A[y][x] != v {
				return false
			}
		}
	}
	return true
}

func (m *matrix) dump() {
	for _, line := range m.A {
		for _, v := range line {
			fmt.Printf("%3v", v)
		}
		fmt.Printf("\n")
	}
}

// find the line index of the maximum for the colomn 'x'
func (m *matrix) findMax(x, r int) int {
	max := -1
	k := 0
	for y := r; y < m.n; y++ {
		if m.A[y][x] > max {
			max = m.A[y][x]
			k = y
		}
	}
	return k
}

// swap line 'y1' and 'y2'
func (m *matrix) swap(y1, y2 int) {
	line := make([]int, m.m)
	copy(line, m.A[y1])
	copy(m.A[y1], m.A[y2])
	copy(m.A[y2], line)
}

// return a line equal of the line 'y'
// where each member is multiply by 'v'
func (m *matrix) mult(y, v int) []int {
	line := make([]int, m.m)
	copy(line, m.A[y])
	for x := 0; x < m.m; x++ {
		line[x] *= v
	}
	return line
}

// substract line y with 'line'
func (m *matrix) sub(y int, line []int) {
	for x := 0; x < m.m; x++ {
		m.A[y][x] -= line[x]
	}
}

// Gaussian or Gauss-Jordan elimination, also known as row reduction,
// is an algorithm in linear algebra for solving a system of linear equations.
// We simplify the algorithm:
//  1 - Updated member type from float to integer because we don't need float operations.
//  2 - Removed the divide operation because the pivot is always equal to 1.
func (m *matrix) rowReduction() {
	r := -1 // row index of the last pivot
	for x := 0; x < m.m-1; x++ {
		k := m.findMax(x, r+1) // k is the line's index of the maximum
		if m.A[k][x] != 0 {    // pivot
			r++
			if k != r {
				m.swap(k, r) // swap line k and r (pivot's line)
			}
			for y := 0; y < m.n; y++ { // simplify other lines
				if y != r {
					m.sub(y, m.mult(r, m.A[y][x])) // cancel A[y][x]
				}
			}
		}
	}
}
