#include <stdlib.h>

#include "solver_unit-test.h"
#include <minesweeper.h>
#include <neighbors.h>
#include <solver.h>

static inline void
count_adjacent_mines(const struct grid* grid,
                     const struct coord* src,
                     const struct coord* dst,
                     struct grid* adjacent)
{
  if (GET(grid, dst->x, dst->y) == FLAGGED) {
    unsigned v = GET(adjacent, src->x, src->y) + 1;
    SET(adjacent, src->x, src->y, v);
  }
}

/**
 * Fill the adjacent mines grid given in argument with the number
 * of mines in the neighborhood for each cell.
 *
 * @param grid Grid to browse.
 * @param adjacent Grid to fill with the number of adjacent mines.
 */
PRIVATE_EXCEPT_UNIT_TEST
void
solver_adjacent_mines(const struct grid* grid, struct grid* adjacent)
{
  ASSERT_DIM_NOT_EQ(grid, adjacent);

  for (unsigned y = 0; y < grid->height; ++y) {
    for (unsigned x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) != FLAGGED) {
        FOREACH_NEIGHBORS(grid, x, y, count_adjacent_mines, adjacent);
      }
    }
  }
}

struct solution*
minesweeper_solve(struct grid* grid)
{
  struct grid* adjacent = minesweeper_grid_new(grid->width, grid->height);

  minesweeper_grid_destroy(adjacent);
  return NULL;
}
