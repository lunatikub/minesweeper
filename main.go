package main

import (
	"log"

	bot "github.com/lunatikub/botMinesweeper/bot"
)

func main() {
	b := bot.NewBot(1, 10)
	b.FirstRdmMove()

	for {
		b.GetConfiguration()
		b.SolveConfiguration()
		if b.IsMoveAvailable() {
			if win := b.Move(); win {
				log.Printf("Win !")
				break
			}
		} else {
			log.Printf("Cannot find solution with this grid !")
			b.Debug()
			break
		}
		b.HideCursor()
	}
}
