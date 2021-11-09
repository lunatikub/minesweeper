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

void
minesweeper_set_adjacent(const struct grid* grid, struct grid* adjacent)
{
  for (unsigned y = 0; y < grid->height; ++y) {
    for (unsigned x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) != FLAGGED) {
        /* clang-format off */
        FOREACH_NEIGHBORS(
          grid, x, y,
          if (GET(grid, neighbor.x, neighbor.y) == FLAGGED) {
            unsigned v = GET(adjacent, x, y) + 1;
            SET(adjacent, x, y, v);
          });
        /* clang-format on */
      }
    }
  }
}
