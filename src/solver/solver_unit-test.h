#ifndef __SOLVER_UNIT_TEST_H__
#define __SOLVER_UNIT_TEST_H__

#include <stdbool.h>
#include <unit-test.h>

/**
 * This file defines all prototypes needed for the unit-tests.
 */

PROTOTYPE_FOR_UNIT_TEST(bool find_unsolved(const struct grid* grid,
                                           struct coord* unsolved));

#endif /* !__SOLVER_UNIT_TEST_H__ */
