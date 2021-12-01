#include <stdlib.h>

#include <minesweeper/grid.h>
#include <minesweeper/neighbors.h>

struct grid*
grid_create(unsigned width, unsigned height)
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

void
grid_adjacents(const struct grid* grid, struct grid* adjacents)
{
  for (unsigned y = 0; y < grid->height; ++y) {
    for (unsigned x = 0; x < grid->width; ++x) {
      if (GET(grid, x, y) != FLAGGED) {
        /* clang-format off */
        FOREACH_NEIGHBORS(
          grid, x, y,
          if (GET(grid, neighbor.x, neighbor.y) == FLAGGED) {
            unsigned v = GET(adjacents, x, y) + 1;
            SET(adjacents, x, y, v);
          });
        /* clang-format on */
      }
    }
  }
}
