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
 * Solve a minesweeper grid.
 */
struct solution*
solve(const struct grid* grid);

/**
 * Destroy a solution previously allocated by 'solve'.
 */
void
solution_destroy(struct solution* solution);

#endif /* !__SOLVER_H__ */
