package solver

func getBounds(M [][]int) ([]int, []int) {
	upper := []int{}
	lower := []int{}
	for _, row := range M {
		u := 0
		l := 0
		// don't process the augmented column
		for _, v := range row[:len(row)-1] {
			if v > 0 {
				u += v
			} else if v < 0 {
				l += v
			}
		}
		upper = append(upper, u)
		lower = append(lower, l)
	}
	return lower, upper
}

func getEmpty(M [][]int, lower, upper *[]int) []int {
	empty := []int{}
	for i, row := range M {
		r := row[len(row)-1]
		for j, v := range row[:len(row)-1] {
			if (r == (*lower)[i] && v > 0) || (r == (*upper)[i] && v < 0) {
				empty = append(empty, j)
			}
		}
	}
	return empty
}

func getMines(M [][]int, lower, upper *[]int) []int {
	mines := []int{}
	for i, row := range M {
		r := row[len(row)-1]
		for j, v := range row[:len(row)-1] {
			if (r == (*upper)[i] && v > 0) || (r == (*lower)[i] && v < 0) {
				mines = append(mines, j)
			}
		}
	}
	return mines
}
