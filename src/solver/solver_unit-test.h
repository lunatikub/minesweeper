#ifndef __SOLVER_UNIT_TEST_H__
#define __SOLVER_UNIT_TEST_H__

#include <stdbool.h>

#include <matrix/matrix.h>
#include <minesweeper/grid.h>
#include <unit-test.h>

#include "configuration.h"

/**
 * This file defines all prototypes needed for the unit-tests
 * of this solver module.
 */

PROTOTYPE_FOR_UNIT_TEST(bool find_unsolved(const struct grid* grid,
                                           struct coord* unsolved));

PROTOTYPE_FOR_UNIT_TEST(
  struct matrix* configuration_map(struct configuration* cfg,
                                   const struct grid* grid,
                                   const struct grid* adjacents));

#endif /* !__SOLVER_UNIT_TEST_H__ */
