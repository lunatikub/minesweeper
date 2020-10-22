package bot

import "testing"

func TestNewGrid(t *testing.T) {
	cells := [][]int{
		{0, 1, 9},
		{0, 1, 9},
		{1, 1, 9},
		{9, 9, 9}}

	g := newGrid(4, 3, covered)
	g.setGrid(cells)

	for y, line := range cells {
		for x, v := range line {
			if v != g.get(y, x) {
				t.Errorf("[setGrid] expected:%d, got:%d", v, g.get(y, x))
			}
		}
	}
}
