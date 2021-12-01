#include <stdlib.h>

#include <minesweeper/grid.h>
#include <minesweeper/neighbors.h>
#include <solver/solver.h>

struct solution*
solve(const struct grid* grid)
{
  struct grid* adjacent = grid_create(grid->width, grid->height);
  grid_destroy(adjacent);
  return NULL;
}
