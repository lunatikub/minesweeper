#include <stdbool.h>
#include <stdlib.h>

#include <minesweeper/neighbors.h>
#include <solver/solver.h>

#include "configuration.h"
#include "solver_unit-test.h"

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

/**
 * Depth-first search of each unsolved cell.
 */
static void
configuration_get_unsolved(const struct grid* grid,
                           struct configuration* cfg,
                           struct coord unsolved_cell)
{
  if (is_solved(grid, unsolved_cell.x, unsolved_cell.y) == false) {
    list_cell_add_head(cfg->unsolved, unsolved_cell);
  }

  /* clang-format off */
  /* for each neighbors not visited, not covered, not flagged, not empty:
     call recursively the function */
  FOREACH_NEIGHBORS(
    grid, unsolved_cell.x, unsolved_cell.y,
    unsigned v = GET(grid, neighbor.x, neighbor.y);
    if (v >= 1 && v <= 8 &&
        list_cell_exist(cfg->unsolved, neighbor) == false) {
      configuration_get_unsolved(grid, cfg, neighbor);
    });
  /* clang-format on */
}

static inline struct configuration*
configuration_create(void)
{
  struct configuration* cfg = calloc(1, sizeof(*cfg));
  cfg->unsolved = list_cell_create();
  return cfg;
}

struct configuration*
configuration_get(const struct grid* grid)
{
  struct configuration* cfg = configuration_create();

  struct coord unsolved_cell;
  if (find_unsolved(grid, &unsolved_cell) == false) {
    return NULL;
  }

  configuration_get_unsolved(grid, cfg, unsolved_cell);

  return cfg;
}

void
configuration_destroy(struct configuration* cfg)
{
  list_cell_destroy(cfg->unsolved);
  free(cfg);
}
