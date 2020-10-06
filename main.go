package main

import (
	"log"
	"os"
	"time"

	"github.com/lunatikub/botMinesweeper/bot"
)

func main() {
	_, err := bot.New(1)
	if err != nil {
		log.Print(err)
		os.Exit(-1)
	}
	wait := 4
	for t := 0; t < wait; t++ {
		log.Printf("start in %d seconds...", wait-t)
		time.Sleep(1 * time.Second)
	}
}
