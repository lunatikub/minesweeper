#include <stdlib.h>

#include <minesweeper/grid.h>
#include <minesweeper/neighbors.h>
#include <solver/solver.h>

#include "solver_unit-test.h"

/**
 * Map a configuration into a matrix.
 */
PRIVATE_EXCEPT_UNIT_TEST
struct matrix*
configuration_map(struct configuration* cfg,
                  const struct grid* grid,
                  const struct grid* adjacents)
{
  unsigned i, j;
  struct matrix* A = matrix_new(cfg->nr_unsolved, cfg->nr_covered + 1);

  for (i = 0; i < cfg->nr_unsolved; ++i) {
    for (j = 0; j < cfg->nr_edge[i]; ++j) {
      A->e[i][cfg->edges[i][j]] = 1;
    }
    struct coord* c = &cfg->unsolved[i];
    A->e[i][cfg->nr_covered] =
      GET(grid, c->x, c->y) - GET(adjacents, c->x, c->y);
  }

  return A;
}

struct solution*
minesweeper_solve(struct grid* grid)
{
  struct grid* adjacent = minesweeper_grid_new(grid->width, grid->height);
  minesweeper_grid_destroy(adjacent);
  return NULL;
}
