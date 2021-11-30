#include <stdlib.h>

#include <minesweeper/grid.h>
#include <minesweeper/neighbors.h>
#include <solver/solver.h>

struct solution*
minesweeper_solve(const struct grid* grid)
{
  struct grid* adjacent = minesweeper_grid_new(grid->width, grid->height);
  minesweeper_grid_destroy(adjacent);
  return NULL;
}
