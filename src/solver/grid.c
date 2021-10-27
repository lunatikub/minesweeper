#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"
#include "neighbors.h"

static inline void
grid_set(struct grid* grid, unsigned x, unsigned y, unsigned v)
{
  grid->cells[y * grid->width + x] = v;
}

static inline unsigned
grid_get(const struct grid* grid, unsigned x, unsigned y)
{
  return grid->cells[y * grid->width + x];
}

static inline void
grid_inc(struct grid* grid, unsigned x, unsigned y, unsigned v)
{
  v += grid_get(grid, x, y);
  grid_set(grid, x, y, v);
}

struct grid*
grid_new(unsigned width, unsigned height)
{
  struct grid* new_grid = malloc(sizeof(*new_grid));

  new_grid->cells = calloc(width * height, sizeof(unsigned));
  new_grid->width = width;
  new_grid->height = height;

  return new_grid;
}

void
grid_destroy(struct grid* grid)
{
  free(grid->cells);
  free(grid);
}

static inline void
grid_count_adjacent_mines(const struct grid* grid,
                          const struct coord* src,
                          const struct coord* dst,
                          struct grid* adjacent)
{
  if (grid_get(grid, dst->x, dst->y) == FLAGGED) {
    grid_inc(adjacent, src->x, src->y, 1);
  }
}

void
grid_get_adjacent_mines(const struct grid* grid, struct grid* adjacent)
{
  ASSERT_DIM_NOT_EQ(grid, adjacent);

  for (unsigned y = 0; y < grid->height; ++y) {
    for (unsigned x = 0; x < grid->width; ++x) {
      if (grid_get(grid, x, y) != FLAGGED) {
        FOREACH_NEIGHBORS(grid, x, y, grid_count_adjacent_mines, adjacent);
      }
    }
  }
}
