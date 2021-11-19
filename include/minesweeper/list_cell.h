#ifndef __LIST_CELL_H__
#define __LIST_CELL_H__

#include <stdbool.h>
#include <sys/queue.h>

#include <minesweeper/minesweeper.h>

/** Opaque structure of a list of cells */
typedef struct list_cell list_cell_t;

/** Opaque structure of a cell */
typedef struct cell cell_t;

/**
 * Create a list of cells.
 */
list_cell_t*
list_cell_create(void);

/**
 * Destroy a list of cells.
 */
void
list_cell_destroy(list_cell_t* cells);

/**
 * Add a cell to the list at head.
 */
void
list_cell_add_head(list_cell_t* cells, struct coord coord);

/**
 * Get the nth cell of the list.
 */
cell_t*
list_cell_get_nth(list_cell_t* cells, unsigned n);

/**
 * Remove the cell given in argument.
 */
void
list_cell_remove(list_cell_t* cells, cell_t* cell);

/**
 * Get the number of cells in the list.
 */
unsigned
list_cell_get_nr(list_cell_t* cells);

/**
 * Get the coordinate of a cell.
 */
struct coord
list_cell_get_coord(cell_t* cell);

/**
 * Return true if the cell exist, otherwise return false.
 */
bool
list_cell_exist(list_cell_t* cells, struct coord coord);

#endif /* !__LIST_CELL_H__ */
