#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <sys/queue.h>

#include <minesweeper/grid.h>

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
 * Solve a minesweeper grid configuration.
 *
 * @param grid Grid to solve.
 * @return List of mines and empty cells to discover.
 */
struct solution*
minesweeper_solve(struct grid* grid);

#endif /* !__SOLVER_H__ */
