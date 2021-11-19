#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <minesweeper/grid.h>
#include <minesweeper/list_cell.h>

/**
 * A configuration is a list of unsolved cells linked by the edges
 * with the covered adjacent celles.
 */
struct configuration
{
  list_cell_t* unsolved;
};

/**
 * Get a configuration from a grid.
 *
 * @param grid Handle of a grid.
 * @return If succeed return the configuration, othewise return @c NULL.
 */
struct configuration*
configuration_get(const struct grid* grid);

/**
 * Destroy a configuration previously returned by @c configuration_get.
 *
 * @param cfg Configuration to destroy.
 */
void
configuration_destroy(struct configuration* cfg);

#endif /* !__CONFIGURATION_H__ */
