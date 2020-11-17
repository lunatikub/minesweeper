package solver

// Value from 0 to 8 are used for uncovered cell
const (
	covered = 9
	flagged = 10
)

type cell struct{ y, x int }

func newMatrix(N, M int) [][]int {
	A := make([][]int, N)
	for i := range A {
		A[i] = make([]int, M)
	}
	return A
}
