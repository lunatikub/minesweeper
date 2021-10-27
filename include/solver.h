#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <sys/queue.h>

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

/**
 * Coordinates of a cell in the grid.
 */
struct coord
{
  int x;
  int y;
};

/* Get the value of a cell from the coordinates */
#define GET(G, X, Y) (G)->cells[(Y) * (G)->width + (X)]

/* Set the value of a cell from the coordinates */
#define SET(G, X, Y, V) GET(G, X, Y) = (V)

/**
 * List of mines and empty cells for a static grid.
 */
struct solution
{
  SLIST_HEAD(, coord) mines;
  SLIST_HEAD(, coord) empty;
  unsigned nr_mine;
  unsigned nr_empty;
};

/**
 * Solve a minesweeper grid.
 *
 * @param grid Grid to solve.
 * @return List of mines and empty cells to discover.
 */
struct solution*
minesweeper_solve(struct grid* grid);

#endif /* !__SOLVER_H__ */
