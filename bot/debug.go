package bot

import "fmt"

func debugDumpGrid(g *grid) {
	fmt.Printf("   ")
	for x := 0; x < g.w; x++ {
		fmt.Printf("[%v]", x)
	}
	fmt.Println()
	for y, line := range g.cells {
		fmt.Printf("[%v]", y)
		for _, v := range line {
			if v == covered {
				fmt.Printf("%3s", ".")
			} else if v == flagged {
				fmt.Printf("%3s", "M")
			} else {
				fmt.Printf("%3v", v)
			}
		}
		fmt.Println()
	}
}

func debugDumpConnex(c *connex) {
	fmt.Printf("List of revealed cells:")
	for _, c := range c.listReveal {
		fmt.Printf("{%v,%v},", c.y, c.x)
	}
	fmt.Println()
	fmt.Printf("List of unrevealed cells:")
	for _, c := range c.listUnreveal {
		fmt.Printf("{%v,%v},", c.y, c.x)
	}
	fmt.Println()
	fmt.Printf("List of unresolved cells:")
	for _, c := range c.listUnsolved {
		fmt.Printf("{%v,%v},", c.y, c.x)
	}
	fmt.Println()

}

func debugDumpMatrix(M [][]int) {
	fmt.Printf("Matrix (%v, %v)\n", len(M), len(M[0]))
	for _, line := range M {
		for _, v := range line {
			fmt.Printf("%3v", v)
		}
		fmt.Println()
	}
}

// Debug dump all information to debug a current configuration
func (b *B) Debug() {
	fmt.Println()
	debugDumpGrid(b.grid)
	debugDumpConnex(b.c)
	m := b.c.buildMatrix(b.grid)
	gaussJordan(m.M)
	fmt.Println()
	debugDumpMatrix(m.M)
}
