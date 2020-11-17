package solver

import (
	"testing"
)

func listEq(l1, l2 list) bool {
	if len(l1) != len(l2) {
		return false
	}
	for _, iter := range l1 {
		if !l2.exist(iter.y, iter.x) {
			return false
		}
	}
	return true
}

func TestSubConfiguration(t *testing.T) {
	grid := [][]int{
		{10, 0, 0, 10, 9},
		{1, 0, 0, 2, 0},
		{0, 1, 0, 1, 9},
		{0, 9, 5, 1, 0},
		{0, 0, 9, 0, 10}}

	cfg := getSubConfiguration(grid)

	unsolvedExpected := list{{2, 1}, {3, 2}, {3, 3}, {2, 3}, {1, 3}}
	if !listEq(unsolvedExpected, cfg.unsolved) {
		t.Errorf("[configuration] unsolved expected:%v, got:%v",
			unsolvedExpected, cfg.unsolved)
	}

	coveredExpected := list{{3, 1}, {4, 2}, {2, 4}, {0, 4}}
	if !listEq(coveredExpected, cfg.covered) {
		t.Errorf("[configuration] covered expected:%v, got:%v",
			coveredExpected, cfg.covered)
	}

	edgesExpected := [][]cell{
		{{2, 4}, {0, 4}},
		{{2, 4}},
		{{4, 2}, {2, 4}},
		{{4, 2}, {3, 1}},
		{{3, 1}}}

	for i := range cfg.unsolved {
		for j, e := range cfg.edges[i] {
			if cfg.covered[e].y != edgesExpected[i][j].y ||
				cfg.covered[e].x != edgesExpected[i][j].x {
				t.Errorf("[configuration] edges expected:%v", edgesExpected)
			}
		}
	}
}
