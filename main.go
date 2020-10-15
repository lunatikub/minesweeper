package main

import (
	"flag"

	bot "github.com/lunatikub/minesweeper/bot"
)

type options struct {
	screenID int // screen identifier
	mines    int // number total of mines
}

func getOptions() *options {
	opts := new(options)
	flag.IntVar(&opts.screenID, "screen", 0, "identifier of the screen where running gnome-mines")
	flag.IntVar(&opts.mines, "mines", 10, "number of mines")
	flag.Parse()
	return opts
}

func main() {

	opts := getOptions()

	b := bot.NewBot(opts.screenID, opts.mines)
	b.FirstRdmMove()

	for {
		b.GetConfiguration()
		b.SolveConfiguration()
		if b.IsSolutionAvailable() {
			b.Move()
		} else {
			b.SetEmptyProb()
		}
		if b.IsEnd() {
			break
		}
		b.HideCursor()
	}
}
