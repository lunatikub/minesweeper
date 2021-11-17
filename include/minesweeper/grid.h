#ifndef __GRID_H__
#define __GRID_H__

/**
 * In the game, the mines are scattered throughout a grid.
 * This grid is divided into cells.
 */
struct grid
{
  /* dimensions of the grid. */
  unsigned width;
  unsigned height;
  /* width * height cells. */
  unsigned* cells;
};

/* Get the value of a cell from the coordinates */
#define GET(G, X, Y) (G)->cells[(Y) * (G)->width + (X)]

/* Set the value of a cell from the coordinates */
#define SET(G, X, Y, V) GET(G, X, Y) = (V)

/**
 * Create a new grid of size specified in parameters.
 *
 * @param width Width of the grid.
 * @param height Height of the grid.
 * @return The new grid allocated.
 */
struct grid*
minesweeper_grid_new(unsigned width, unsigned height);

/**
 * Destroy a grid previously allocated by @c minesweeper_grid_new.
 *
 * @param grid Grid to destroy.
 */
void
minesweeper_grid_destroy(struct grid* grid);

/**
 * Fill the adjacent mines grid given in argument with the number
 * of mines in the neighborhood for each cell.
 *
 * @param grid Grid to browse.
 * @param adjacent Grid to fill with the number of adjacent mines.
 */
void
minesweeper_set_adjacent(const struct grid* grid, struct grid* adjacent);

#endif /* !__GRID_H__ */
