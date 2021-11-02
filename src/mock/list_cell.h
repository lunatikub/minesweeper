#ifndef __LIST_CELL_H__
#define __LIST_CELL_H__

#include <sys/queue.h>

#include <minesweeper.h>

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
 * Create the entire list of cells from the dimensions.
 */
void
list_cell_create(struct list_cell* cells, unsigned width, unsigned height);

/**
 * Destroy the list of cells previously created
 * from @c mock_list_cell_create.
 */
void
list_cell_destroy(struct list_cell* cells);

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
