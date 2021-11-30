#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <minesweeper/grid.h>
#include <minesweeper/list_cell.h>
#include <unit-test.h>

/**
 * A configuration is a list of unsolved cells.
 * Each cell has a list of edges to the covered adjacent cells.
 */
struct configuration
{
  struct coord* unsolved; /* list of unsolved cells. */
  struct coord* covered;  /* list of covered adjacent cells. */
  unsigned** edges;       /* edge from unsolved to covered adjacent cells. */
  unsigned* nr_edge;      /* number of edge. */
  unsigned nr_unsolved;   /* number of unsolved cells. */
  unsigned nr_covered;    /* number of covered adjacent cells. */
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

/**
 * Map a configuration into a matrix.
 */
struct matrix*
configuration_map(struct configuration* cfg,
                  const struct grid* grid,
                  const struct grid* adjacents);

/**
 * All following structures and prototypes are needed
 * for the unit-tests of this module.
 */

/**
 * Find the first unsolved cell in the grid 'grid'.
 * An unsolved cell is:
 *   + an uncovered cell between 1 and 8.
 *   + has almost one covered neighboor.
 * Return true if found, otherwise return false.
 */
PROTOTYPE_FOR_UNIT_TEST(bool find_unsolved(const struct grid* grid,
                                           struct coord* unsolved));

#endif /* !__CONFIGURATION_H__ */
