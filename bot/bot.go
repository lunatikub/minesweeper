package bot

const (
	unreveal = 9
	mine     = 10
)

// B Bot minesweeper
type B struct {
	r recognition // recognition of the form/values/...
	g *grid       // cells
}

// New Create a new bot Minesweeper
func New(screenID int) (*B, error) {
	b := new(B)
	b.r.getBounds(screenID)
	if err := b.r.getDims(); err != nil {
		return nil, err
	}
	b.g = newGrid(b.r.h, b.r.w)
	return b, nil
}
