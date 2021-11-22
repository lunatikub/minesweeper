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

struct context
{
  const struct grid* grid;
  list_cell_t* unsolved;
  list_cell_t* covered;
  struct configuration* cfg;
};

static inline struct context*
context_create(const struct grid* grid, struct configuration* cfg)
{
  struct context* ctx = calloc(1, sizeof(*ctx));
  ctx->cfg = cfg;
  ctx->grid = grid;
  ctx->unsolved = list_cell_create();
  ctx->covered = list_cell_create();
  return ctx;
}

static inline void
context_destroy(struct context* ctx)
{
  list_cell_destroy(ctx->unsolved);
  list_cell_destroy(ctx->covered);
  free(ctx);
}

/* Depth-first search of each unsolved cell. */
static inline void
configuration_get_unsolved(struct context* ctx, struct coord unsolved_cell)
{
  if (is_solved(ctx->grid, unsolved_cell.x, unsolved_cell.y) == false) {
    list_cell_add_head(ctx->unsolved, unsolved_cell);
  }

  /* clang-format off */
  /* for each neighbors not visited, not covered, not flagged, not empty:
     call recursively the function */
  FOREACH_NEIGHBORS(
    ctx->grid, unsolved_cell.x, unsolved_cell.y,
    unsigned v = GET(ctx->grid, neighbor.x, neighbor.y);
    if (v >= 1 && v <= 8 &&
        list_cell_exist(ctx->unsolved, neighbor) == false) {
      configuration_get_unsolved(ctx, neighbor);
    });
  /* clang-format on */
}

static inline void
configuration_get_covered(struct context* ctx)
{
  struct configuration* cfg = ctx->cfg;

  for (unsigned i = 0; i < cfg->nr_unsolved; ++i) {
    struct coord* unsolved = &cfg->unsolved[i];
    /* clang-format off */
    /* add each adjacent covered cell of the unsolved cell. */
    FOREACH_NEIGHBORS(
      ctx->grid, unsolved->x, unsolved->y,
      if (GET(ctx->grid, neighbor.x, neighbor.y) == COVERED &&
          list_cell_exist(ctx->covered, neighbor) == false) {
        list_cell_add_head(ctx->covered, neighbor);
      });
    /* clang-format on */
  }
}

struct configuration*
configuration_get(const struct grid* grid)
{
  struct configuration* cfg = calloc(1, sizeof(struct configuration));
  struct context* ctx = context_create(grid, cfg);

  struct coord unsolved_cell;
  if (find_unsolved(grid, &unsolved_cell) == false) {
    return NULL;
  }
  configuration_get_unsolved(ctx, unsolved_cell);
  cfg->unsolved = list_cell_to_array(ctx->unsolved, &cfg->nr_unsolved);
  configuration_get_covered(ctx);
  cfg->covered = list_cell_to_array(ctx->covered, &cfg->nr_covered);

  context_destroy(ctx);
  return cfg;
}

void
configuration_destroy(struct configuration* cfg)
{
  free(cfg->covered);
  free(cfg->unsolved);
  free(cfg);
}
