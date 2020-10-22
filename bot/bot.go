package bot

import (
	"log"
	"time"
)

// Value from 0 to 8 are used for uncovered cell
const (
	covered = 9
	flagged = 10
)

// B Bot minesweeper
type B struct {
	grid    *grid        // current grid
	r       *recognition // recognition module
	i       *interaction // interaction module
	c       *connex      // connex revealed/unrevealed/unsolved cells
	mines   []int        // list of mines
	empty   []int        // list of empty cells
	nrMine  int          // number of revealed mines
	totMine int          // total number of mines
}

func isRevealedValue(v int) bool {
	return v >= 1 && v <= 8
}

// NewBot create and initialize a new bot for gnome-mines game
func NewBot(screenID, totMine int) *B {
	b := new(B)
	b.r = newRecognition(screenID)
	b.totMine = totMine
	wait := 2
	for t := 0; t < wait; t++ {
		log.Printf("[bot] start in %d seconds...", wait-t)
		time.Sleep(1 * time.Second)
	}
	b.i = newInteraction(b.r.h, b.r.w)
	b.grid = newGrid(b.r.h, b.r.w, covered)
	return b
}

func lookupCreate(list *[]int, value int) bool {
	for _, v := range *list {
		if v == value {
			return false
		}
	}
	*list = append(*list, value)
	return true
}

// Find the empty cells in a grid from row-echelon form and bounds.
func findEmpty(m *matrix, empty *[]int) {
	for y, line := range m.M {
		r := line[len(line)-1]
		for x, v := range line[:len(line)-1] {
			if (r == m.lowerBound[y] && v > 0) ||
				(r == m.upperBound[y] && v < 0) {
				lookupCreate(empty, x)
			}
		}
	}
}

// Find the mines in a grid from row-echelon form and bounds.
func findMines(m *matrix, mines *[]int) {
	for y, line := range m.M {
		r := line[len(line)-1]
		for x, v := range line[:len(line)-1] {
			if (r == m.upperBound[y] && v > 0) ||
				(r == m.lowerBound[y] && v < 0) {
				lookupCreate(mines, x)
			}
		}
	}
}

// Find the first unresolved cell of the grid
func findUnresolvedCell(g *grid) (int, int) {
	for y, line := range g.cells {
		for x, v := range line {
			if isRevealedValue(v) {
				for _, n := range neighbors {
					yn := y + n.y
					xn := x + n.x
					if check(g.h, g.w, yn, xn) &&
						g.get(yn, xn) == covered {
						log.Printf("[bot] unresolved cell: {%v,%v}", y, x)
						return y, x
					}
				}
			}
		}
	}
	return -1, -1
}

// SolveConfiguration Solve a configuration by
// finding mines and empty cells.
func (b *B) SolveConfiguration() {
	b.mines = b.mines[:0]
	b.empty = b.empty[:0]
	b.c = new(connex)
	y, x := findUnresolvedCell(b.grid)
	if y == -1 {
		debugDumpGrid(b.grid)
		panic("Cannot find an unresolved cell")
	}
	b.c.revealedUnrevealed(b.grid, y, x)
	b.c.unsolved(b.grid)
	m := b.c.buildMatrix(b.grid)
	gaussJordan(m.M)
	m.getBounds()
	findEmpty(m, &b.empty)
	findMines(m, &b.mines)
}

// FirstRdmMove First has to be done randomly
func (b *B) FirstRdmMove() {
	b.i.move(1, 1, setEmpty)
}

// HideCursor Move the current cursor to a revealed cell to hide it.
func (b *B) HideCursor() {
	for y := 0; y < b.r.h; y++ {
		for x := 0; x < b.r.w; x++ {
			if isRevealedValue(b.grid.cells[y][x]) {
				b.i.move(y, x, focus)
				log.Printf("[bot] hide cursor %v, %v", y, x)
				return
			}
		}
	}
}

// GetConfiguration Get the current configuration of the grid
func (b *B) GetConfiguration() {
	time.Sleep(300 * time.Millisecond) // wait end of animation
	b.r.getConfiguration(b.grid)
}

// IsSolutionAvailable if a solution is available
// return true, otherwise return false.
func (b *B) IsSolutionAvailable() bool {
	log.Printf("[bot] number of empty found: %v", len(b.empty))
	log.Printf("[bot] number of mines found: %v", len(b.mines))
	return len(b.mines) != 0 || len(b.empty) != 0
}

// Move Set the mines and empty cells.
func (b *B) Move() {
	for _, e := range b.mines {
		c := b.c.listUnreveal[e]
		b.grid.cells[c.y][c.x] = flagged
		b.nrMine++
		b.i.move(c.y, c.x, setMine)
	}
	log.Printf("[bot] mines: %v/%v", b.nrMine, b.totMine)
	if b.nrMine == b.totMine {
		return
	}
	for _, e := range b.empty {
		c := b.c.listUnreveal[e]
		b.i.move(c.y, c.x, setEmpty)
	}
}

// SetEmptyProb foo
func (b *B) SetEmptyProb() {
	c := getEmptyProbabilistic(b.grid, b.c.listUnreveal, b.totMine)
	b.i.move(c.y, c.x, setEmpty)
}

// IsEnd return true if the game is end
func (b *B) IsEnd() bool {
	if b.nrMine != b.totMine {
		return false
	}
	for y, line := range b.grid.cells {
		for x, v := range line {
			if v == covered {
				b.i.move(y, x, setEmpty)
			}
		}
	}
	log.Printf("[bot] !!! win !!!")
	return true
}
