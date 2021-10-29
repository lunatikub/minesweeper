#ifndef __GRID_H__
#define __GRID_H__

#include <assert.h>
#include <stdint.h>

/* 0 to 8 are used for uncovered cell */
enum
{
  COVERED = 9,
  FLAGGED = 10,
};

/**
 * Assert if the both grid have not the same dimensions.
 */
#define ASSERT_DIM_NOT_EQ(G1, G2)                                              \
  do {                                                                         \
    assert(G1->width == G2->width);                                            \
    assert(G1->height == G2->height);                                          \
  } while (0)

/**
 * Create a new grid of size specified in parameters.
 *
 * @param width Width of the grid.
 * @param height Height of the grid.
 * @return The new grid allocated.
 */
struct grid*
grid_new(unsigned width, unsigned height);

/**
 * Destroy a grid previously allocated by @c grid_new.
 *
 * @param grid Grid to destroy.
 */
void
grid_destroy(struct grid* grid);

/**
 * Fill the adjacent mines grid given in argument with the number
 * of mines in the neighborhood for each cell.
 *
 * @param grid Grid to browse.
 * @param adjacent Grid to fill with the number of adjacent mines.
 */
void
grid_get_adjacent_mines(const struct grid* grid, struct grid* adjacent);

#endif /* !__GRID_H__ */
