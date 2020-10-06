package bot

import "fmt"

type matrix struct {
	A    [][]float64
	n, m int // dims
}

func newMatrix(n, m int) *matrix {
	newM := new(matrix)
	newM.A = make([][]float64, n)
	for i := range newM.A {
		newM.A[i] = make([]float64, m)
	}
	newM.n = n
	newM.m = m
	return newM
}

func (m *matrix) set(y, x int, v float64) {
	m.A[y][x] = v
}

func (m *matrix) setLine(y int, line []float64) {
	copy(m.A[y], line)
}

func (m *matrix) setMatrix(A [][]float64) {
	for y, line := range A {
		m.setLine(y, line)
	}
}

func (m *matrix) dump() {
	for _, line := range m.A {
		for _, v := range line {
			fmt.Printf("%6.2f", v)
		}
		fmt.Println()
	}
}

func (m *matrix) findPivot(x, r int) int {
	max := -1.0
	k := 0
	for y := r; y < m.n; y++ {
		if m.A[y][x] > max {
			max = m.A[y][x]
			k = y
		}
	}
	return k
}

func (m *matrix) div(y int, v float64) {
	for x := 0; x < m.m; x++ {
		m.A[y][x] /= v
	}
}

func (m *matrix) swap(y1, y2 int) {
	line := make([]float64, m.m)
	copy(line, m.A[y1])
	copy(m.A[y1], m.A[y2])
	copy(m.A[y2], line)
}

func (m *matrix) mult(y int, v float64) []float64 {
	line := make([]float64, m.m)
	copy(line, m.A[y])
	for x := 0; x < m.m; x++ {
		line[x] *= v
	}
	return line
}

func (m *matrix) sub(y int, line []float64) {
	for x := 0; x < m.m; x++ {
		m.A[y][x] -= line[x]
	}
}

func (m *matrix) gaussJordan() {
	m.dump()
	r := -1 // row index of the last pivot
	for x := 0; x < m.m-1; x++ {
		k := m.findPivot(x, r+1)
		fmt.Printf("Pivot: r:%d, x:%d, k:%d\n", r, x, k)
		if m.A[k][x] != 0 {
			r++
			fmt.Printf("A[%d][%d]:%f != 0\n", k, x, m.A[k][x])
			fmt.Printf("dive line:%d by %f\n", k, m.A[k][x])
			m.div(k, m.A[k][x])
			m.dump()
			if k != r {
				fmt.Printf("Swap k:%d, r:%d\n", k, r)
				m.swap(k, r)
				m.dump()
			}
			for y := 0; y < m.n; y++ {
				if y != r {
					fmt.Printf("line %d - line %d * %f\n", y, r, m.A[y][x])
					fmt.Println("new line:", m.mult(r, m.A[y][x]))
					m.sub(y, m.mult(r, m.A[y][x]))
					m.dump()
				}
			}
		}
	}

}
