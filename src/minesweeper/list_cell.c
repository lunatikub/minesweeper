#include <stdlib.h>

#include <minesweeper/list_cell.h>

struct cell
{
  LIST_ENTRY(cell) next;
  struct coord coord;
};

struct list_cell
{
  LIST_HEAD(, cell) head;
  unsigned nr;
};

static inline struct cell*
cell_new(struct coord* coord)
{
  struct cell* cell = malloc(sizeof(*cell));
  cell->coord.y = coord->y;
  cell->coord.x = coord->x;
  return cell;
}

struct list_cell*
list_cell_create(void)
{
  struct list_cell* cells = calloc(1, sizeof(*cells));
  LIST_INIT(&cells->head);
  cells->nr = 0;
  return cells;
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
  free(cells);
}

void
list_cell_add_head(struct list_cell* cells, struct coord coord)
{
  struct cell* cell = cell_new(&coord);
  LIST_INSERT_HEAD(&cells->head, cell, next);
  ++cells->nr;
}

struct cell*
list_cell_get_nth(struct list_cell* cells, unsigned n)
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
list_cell_remove(struct list_cell* cells, struct cell* cell)
{
  LIST_REMOVE(cell, next);
  --cells->nr;
  free(cell);
}

unsigned
list_cell_get_nr(list_cell_t* cells)
{
  return cells->nr;
}

struct coord*
list_cell_get_coord(struct cell* cell)
{
  return &cell->coord;
}

bool
list_cell_exist(struct list_cell* cells, struct coord coord)
{
  struct cell* cell;
  LIST_FOREACH(cell, &cells->head, next)
  {
    if (cell->coord.x == coord.x && cell->coord.y == coord.y) {
      return true;
    }
  }
  return false;
}

void
list_cell_foreach(struct list_cell* cells, list_cell_cb cb, void* arg)
{
  struct cell* cell;
  LIST_FOREACH(cell, &cells->head, next) { cb(cell, arg); }
}
