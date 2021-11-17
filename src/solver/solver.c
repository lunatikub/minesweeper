#include <stdlib.h>

#include <minesweeper/grid.h>
#include <minesweeper/neighbors.h>
#include <solver/solver.h>

#include "solver_unit-test.h"

struct solution*
minesweeper_solve(struct grid* grid)
{
  struct grid* adjacent = minesweeper_grid_new(grid->width, grid->height);

  minesweeper_grid_destroy(adjacent);
  return NULL;
}
