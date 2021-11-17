#ifndef __SOLVER_UNIT_TEST_H__
#define __SOLVER_UNIT_TEST_H__

#include <stdbool.h>

#include <minesweeper/grid.h>
#include <unit-test.h>

/**
 * This file defines all prototypes needed for the unit-tests
 * of this solver module.
 */

PROTOTYPE_FOR_UNIT_TEST(bool solver_find_unsolved(const struct grid* grid,
                                                  struct coord* unsolved));

PROTOTYPE_FOR_UNIT_TEST(void solver_adjacent_mines(const struct grid* grid,
                                                   struct grid* adjacent));

#endif /* !__SOLVER_UNIT_TEST_H__ */
