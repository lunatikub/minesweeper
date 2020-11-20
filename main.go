package main

import (
	"flag"
	"fmt"
	"math/rand"
	"time"

	"github.com/lunatikub/minesweeper/solver"
)

type options struct {
	mines  int // number total of mines
	width  int // width of the grid
	height int // height of the grid
}

func getOptions() *options {
	opts := new(options)
	flag.IntVar(&opts.mines, "mines", 10, "number of mines")
	flag.IntVar(&opts.width, "width", 8, "width of the grid")
	flag.IntVar(&opts.height, "height", 8, "heigh of the grid")
	flag.Parse()
	return opts
}

const (
	mine = -1
)

func dump(grid [][]int, name string) {
	fmt.Println(name)
	for _, row := range grid {
		for _, v := range row {
			if v == mine {
				fmt.Printf(" M ")
			} else if v == solver.Flagged {
				fmt.Printf(" F ")
			} else {
				fmt.Printf("%2v ", v)
			}
		}
		fmt.Println()
	}
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	opts := getOptions()
	solution := generateSolution(opts.width, opts.height, opts.mines)
	grid := solver.NewGrid(opts.width, opts.height, solver.Covered)

	dump(solution, "solution")
	setEmpty(solution, grid, []solver.Cell{{Y: 1, X: 1}})
	dump(grid, "grid")

	n := 0
	for {
		fmt.Println()
		empty, mines := solver.Solve(grid)
		fmt.Println(empty)
		fmt.Println(mines)

		if len(empty) == 0 && len(mines) == 0 {
			panic("need prob")
		}

		setEmpty(solution, grid, empty)
		setMines(grid, mines)
		dump(solution, "solution")
		dump(grid, "grid")
		n += len(mines)
		fmt.Println("flagged", n)
		if n == opts.mines {
			break
		}
	}
	fmt.Println("win")
}
