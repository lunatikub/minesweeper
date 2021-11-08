#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <assert.h>

/* 0 to 8 are used for uncovered cell */
enum
{
  EMPTY = 0,
  COVERED = 9,
  FLAGGED = 10,
  MINE = FLAGGED,
};

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
 * Assert if the both grids have not the same dimensions.
 */
#define ASSERT_DIM_NOT_EQ(G1, G2)                                              \
  do {                                                                         \
    assert(G1->width == G2->width);                                            \
    assert(G1->height == G2->height);                                          \
  } while (0)

/**
 * Coordinates of a cell in the grid.
 */
struct coord
{
  unsigned x;
  unsigned y;
  ;
};

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

#endif /* !__MINESWEEPER_H__ */
