package bot

import "testing"

func eq(m *matrix, A [][]float64) bool {
	for y, line := range A {
		for x, v := range line {
			if m.A[y][x] != v {
				return false
			}
		}
	}
	return true
}

func TestFindPivot(t *testing.T) {
	m := newMatrix(2, 2)
	m.setMatrix([][]float64{{1, 4}, {3, 2}})
	e := 1
	if r := m.findPivot(0, 0); r != e {
		t.Errorf("Pivot expected:%d, got:%d", e, r)
	}
	e = 0
	if r := m.findPivot(1, 0); r != e {
		t.Errorf("Pivot expected:%d, got:%d", e, r)
	}
}

func TestDiv(t *testing.T) {
	m := newMatrix(2, 2)
	m.setMatrix([][]float64{{2, 4}, {3, 2}})
	m.div(0, 2)
	if !eq(m, [][]float64{{1, 2}, {3, 2}}) {
		t.Errorf("Div")
	}
}

func TestSwap(t *testing.T) {
	m := newMatrix(2, 2)
	m.setMatrix([][]float64{{2, 4}, {3, 2}})
	m.swap(0, 1)
	if !eq(m, [][]float64{{3, 2}, {2, 4}}) {
		t.Errorf("Swap")
	}
}

func TestMult(t *testing.T) {
	m := newMatrix(2, 2)
	m.setMatrix([][]float64{{2, 4}, {3, 2}})
	l := m.mult(0, -1)
	if l[0] != -2 || l[1] != -4 {
		t.Errorf("Mult")
	}
}

func TestSub(t *testing.T) {
	m := newMatrix(2, 2)
	m.setMatrix([][]float64{{2, 4}, {3, 2}})
	m.sub(0, []float64{1, 1})
	if !eq(m, [][]float64{{1, 3}, {3, 2}}) {
		t.Errorf("Sub")
	}
}

func TestGaussJordan(t *testing.T) {
	// m := newMatrix(3, 3)
	// m.setMatrix([][]float64{
	// 	{2, -1, 0},
	// 	{-1, 2, -1},
	// 	{0, -1, 2}})
	// m.gaussJordan()
	// m := newMatrix(4, 7)
	// m.setMatrix([][]float64{
	// 	{1, 1, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 0, 0, 0, 1},
	// 	{0, 1, 1, 1, 1, 1, 1},
	// 	{0, 0, 0, 0, 1, 1, 1},
	// })
	// m.gaussJordan()
	m := newMatrix(7, 10)
	m.setMatrix([][]float64{
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 2},
		{0, 1, 1, 1, 1, 1, 0, 0, 0, 3},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 1, 1, 1, 1, 2},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	})
	m.gaussJordan()
}
