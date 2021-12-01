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
 * Create a new grid of size 'width x height'.
 */
struct grid*
grid_create(unsigned width, unsigned height);

/**
 * Destroy a grid previously allocated by 'grid_create'.
 */
void
grid_destroy(struct grid* grid);

/**
 * Fill the adjacent mines grid given in argument with the number
 * of mines in the neighborhood for each cell.
 */
void
grid_adjacents(const struct grid* grid, struct grid* adjacents);

#endif /* !__GRID_H__ */
