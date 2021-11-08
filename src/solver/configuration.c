#include <stdbool.h>
#include <stdlib.h>

#include "configuration.h"
#include "solver_unit-test.h"
#include <neighbors.h>
#include <solver.h>

/**
 * An unsolved cell:
 *   + is a uncovered cell between 1 and 8.
 *   + has almost one covered neighboor.
 */
PRIVATE_EXCEPT_UNIT_TEST
bool
solver_find_unsolved(const struct grid* grid, struct coord* unsolved)
{
  for (unsigned y = 0; y < grid->height; ++y) {
    for (unsigned x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) >= 1 && GET(grid, x, y) <= 8) {
        bool covered_neighboor = false;
        /* clang-format off */
        FOREACH_NEIGHBORS(
          grid, x, y,
          if (GET(grid, neighbor.x, neighbor.y) == COVERED) {
            covered_neighboor = true;
          });
        /* clang-format on */
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
solver_configuration_get(const struct grid* grid)
{
  struct coord unsolved;
  if (solver_find_unsolved(grid, &unsolved) == false) {
    return NULL;
  }
  return NULL;
}
