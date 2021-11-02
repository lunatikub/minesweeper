#include <stdlib.h>

#include "solver_unit-test.h"
#include <minesweeper.h>
#include <neighbors.h>
#include <solver.h>

struct solution*
minesweeper_solve(struct grid* grid)
{
  struct grid* adjacent = minesweeper_grid_new(grid->width, grid->height);

  minesweeper_grid_destroy(adjacent);
  return NULL;
}
