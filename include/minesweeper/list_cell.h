#ifndef __LIST_CELL_H__
#define __LIST_CELL_H__

#include <sys/queue.h>

#include <minesweeper/minesweeper.h>

/**
 * List of cells.
 */
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

/**
 * Init a list of cells.
 */
void
list_cell_init(struct list_cell* cells);

/**
 * Destroy all elements of a list of cells.
 */
void
list_cell_destroy(struct list_cell* cells);

/**
 * Add a cell to the list at head.
 */
void
list_cell_add_head(struct list_cell* cells, unsigned x, unsigned y);

/**
 * Get the nth cell of the list.
 */
struct cell*
list_cell_get_nth_cell(struct list_cell* cells, unsigned n);

/**
 * Remove the cell given in argument.
 */
void
list_cell_remove_cell(struct list_cell* cells, struct cell* cell);

#endif /* !__LIST_CELL_H__ */
