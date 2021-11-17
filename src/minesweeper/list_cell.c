#include <stdlib.h>

#include <minesweeper/list_cell.h>

static inline struct cell*
cell_new(unsigned x, unsigned y)
{
  struct cell* cell = malloc(sizeof(*cell));
  cell->coord.y = y;
  cell->coord.x = x;
  return cell;
}

void
list_cell_create(struct list_cell* cells, unsigned width, unsigned height)
{
  LIST_INIT(&cells->head);
  cells->nr = 0;

  for (unsigned y = 0; y < height; ++y) {
    for (unsigned x = 0; x < width; ++x) {
      struct cell* cell = cell_new(x, y);
      LIST_INSERT_HEAD(&cells->head, cell, next);
      ++cells->nr;
    }
  }
}

void
list_cell_destroy(struct list_cell* cells)
{
  struct cell* cell;
  while (!LIST_EMPTY(&cells->head)) {
    cell = LIST_FIRST(&cells->head);
    LIST_REMOVE(cell, next);
    free(cell);
  }
}

struct cell*
list_cell_get_nth_cell(struct list_cell* cells, unsigned n)
{
  if (n >= cells->nr) {
    return NULL;
  }

  unsigned i = 0;
  struct cell* cell = LIST_FIRST(&cells->head);

  while (i != n) {
    cell = LIST_NEXT(cell, next);
    ++i;
  }

  return cell;
}

void
list_cell_remove_cell(struct list_cell* cells, struct cell* cell)
{
  LIST_REMOVE(cell, next);
  --cells->nr;
  free(cell);
}
