#include <stdlib.h>

#include <minesweeper.h>

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
