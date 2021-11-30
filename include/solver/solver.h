#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <sys/queue.h>

#include <minesweeper/grid.h>

/**
 * List of mines and empty cells for a static grid.
 */
struct solution
{
  struct coord* mines;
  struct coord* empty;
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
minesweeper_solve(const struct grid* grid);

#endif /* !__SOLVER_H__ */
