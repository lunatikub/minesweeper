#include <stdlib.h>

#include <minesweeper.h>
#include <neighbors.h>

struct grid*
minesweeper_grid_new(unsigned width, unsigned height)
{
  struct grid* new_grid = malloc(sizeof(*new_grid));

  new_grid->cells = calloc(width * height, sizeof(unsigned));
  new_grid->width = width;
  new_grid->height = height;

  return new_grid;
}

void
minesweeper_grid_destroy(struct grid* grid)
{
  free(grid->cells);
  free(grid);
}

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

void
minesweeper_set_adjacent(const struct grid* grid, struct grid* adjacent)
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
