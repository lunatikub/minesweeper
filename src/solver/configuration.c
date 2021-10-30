#include <stdbool.h>
#include <stdlib.h>

#include "configuration.h"
#include "grid.h"
#include "neighbors.h"
#include "solver_unit-test.h"
#include <solver.h>

static inline void
is_covered(const struct grid* grid,
           const struct coord* src __attribute__((unused)),
           const struct coord* dst,
           bool* covered_neighboor)
{
  if (GET(grid, dst->x, dst->y) == COVERED) {
    *covered_neighboor = true;
  }
}

/**
 * An unsolved cell:
 *   + is a uncovered cell between 1 and 8.
 *   + has almost one covered neighboor.
 */
PRIVATE_EXCEPT_UNIT_TEST
bool
find_unsolved(const struct grid* grid, struct coord* unsolved)
{
  for (unsigned y = 0; y < grid->height; ++y) {
    for (unsigned x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) >= 1 && GET(grid, x, y) <= 8) {
        bool covered_neighboor = false;
        FOREACH_NEIGHBORS(grid, x, y, is_covered, &covered_neighboor);
        if (covered_neighboor == true) {
          unsolved->x = x;
          unsolved->y = y;
          return true;
        }
      }
    }
  }
  return false;
}

struct configuration*
configuration_get(const struct grid* grid)
{
  struct coord unsolved;
  if (find_unsolved(grid, &unsolved) == false) {
    return NULL;
  }
  return NULL;
}
