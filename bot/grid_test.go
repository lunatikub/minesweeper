package bot

import "testing"

func TestSetGrid(t *testing.T) {
	g := newGrid(4, 4)

	cells := [][]int{
		{0, 1, 9},
		{0, 1, 9},
		{1, 1, 9},
		{9, 9, 9}}

	g.setGrid(cells)

	for y, line := range cells {
		for x, v := range line {
			if v != g.get(y, x) {
				t.Errorf("[setGrid] expected:%d, got:%d", v, g.get(y, x))
			}
		}
	}
}
