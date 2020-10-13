package bot

import (
	"fmt"
	"log"
	"time"
)

const (
	unreveal = 9
	mine     = 10
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
	b.grid = newGrid(b.r.h, b.r.w)
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
func (b *B) findEmpty(m *matrix) {
	for y, line := range m.M {
		r := line[len(line)-1]
		for x, v := range line[:len(line)-1] {
			if (r == m.lowerBound[y] && v > 0) ||
				(r == m.upperBound[y] && v < 0) {
				lookupCreate(&b.empty, x)
			}
		}
	}
}

// Find the mines in a grid from row-echelon form and bounds.
func (b *B) findMines(m *matrix) {
	for y, line := range m.M {
		r := line[len(line)-1]
		for x, v := range line[:len(line)-1] {
			if (r == m.upperBound[y] && v > 0) ||
				(r == m.lowerBound[y] && v < 0) {
				lookupCreate(&b.mines, x)
			}
		}
	}
}

// Find the first unresolved cell of the grid
func findUnresolvedCell(g *grid) (int, int) {
	for y, line := range g.cells {
		for x, v := range line {
			if v >= 1 && v <= 8 {
				for _, n := range neighbors {
					yn := y + n.y
					xn := x + n.x
					if check(g.h, g.w, yn, xn) &&
						g.get(yn, xn) == unreveal {
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
		panic("Cannot find an unresolved cell")
	}
	b.c.revealedUnrevealed(b.grid, y, x)
	b.c.unsolved(b.grid)
	m := b.c.buildMatrix(b.grid)
	gaussJordan(m.M)
	m.getBounds()
	b.findEmpty(m)
	b.findMines(m)
}

// FirstRdmMove First has to be done randomly
func (b *B) FirstRdmMove() {
	b.i.move(1, 1, setEmpty)
}

// HideCursor Move the current cursor to a revealed cell to hide it.
func (b *B) HideCursor() {
	for y := 0; y < b.r.h; y++ {
		for x := 0; x < b.r.w; x++ {
			if b.grid.cells[y][x] >= 1 &&
				b.grid.cells[y][x] <= 8 {
				b.i.move(y, x, focus)
				log.Printf("Hide cursor %v, %v", y, x)
				return
			}
		}
	}
}

// GetConfiguration Get the current configuration of the grid
func (b *B) GetConfiguration() {
	time.Sleep(200 * time.Millisecond) // wait end of animation
	b.r.getConfiguration(b.grid)
}

// IsMoveAvailable if a move is available return true,
// otherwise return false.
func (b *B) IsMoveAvailable() bool {
	log.Printf("[bot] number of empty found: %v", len(b.empty))
	log.Printf("[bot] number of mines found: %v", len(b.mines))
	return len(b.mines) != 0 || len(b.empty) != 0
}

// Move Set the mines and empty cells.
func (b *B) Move() bool {
	for _, e := range b.empty {
		c := b.c.listUnreveal[e]
		log.Printf("[bot] set empty {%v,%v}", c.y, c.x)
		b.i.move(c.y, c.x, setEmpty)
	}
	for _, e := range b.mines {
		c := b.c.listUnreveal[e]
		log.Printf("[bot] set mine {%v,%v}", c.y, c.x)
		b.grid.cells[c.y][c.x] = mine
		b.nrMine++
		b.i.move(c.y, c.x, setMine)
	}
	log.Printf("[bot] mines: %v/%v", b.nrMine, b.totMine)
	return b.nrMine == b.totMine
}

// Debug foo
func (b *B) Debug() {
	fmt.Println()
	fmt.Printf("List of revealed cells:")
	for _, c := range b.c.listReveal {
		fmt.Printf("{%v,%v},", c.y, c.x)
	}
	fmt.Println()
	fmt.Printf("List of unrevealed cells:")
	for _, c := range b.c.listUnreveal {
		fmt.Printf("{%v,%v},", c.y, c.x)
	}
	fmt.Println()
	fmt.Printf("List of unresolved cells:")
	for _, c := range b.c.listUnsolved {
		fmt.Printf("{%v,%v},", c.y, c.x)
	}
	fmt.Println()
	for x := 0; x < b.grid.w; x++ {
		fmt.Printf("[%v]", x)
	}
	fmt.Println()
	for y, line := range b.grid.cells {
		fmt.Printf("[%v]", y)
		for _, v := range line {
			if v == 0 {
				fmt.Printf("   ")
			} else if v == unreveal {
				fmt.Printf("%3s", ".")
			} else if v == mine {
				fmt.Printf("%3s", "X")
			} else {
				fmt.Printf("%3v", v)
			}
		}
		fmt.Println()
	}
	m := b.c.buildMatrix(b.grid)
	gaussJordan(m.M)
	fmt.Println()
	for _, line := range m.M {
		for _, v := range line {
			fmt.Printf("%3v", v)
		}
		fmt.Println()
	}
}
