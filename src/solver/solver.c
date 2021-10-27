#include <stdlib.h>

#include "grid.h"
#include <solver.h>

struct solution*
minesweeper_solve(struct grid* grid)
{
  struct grid* adjacent = grid_new(grid->width, grid->height);

  grid_destroy(adjacent);
  return NULL;
}
