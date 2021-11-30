#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <matrix/matrix.h>
#include <unit-test.h>

/**
 * Deduce the solution from a configuration and
 * the reduced row echelon form of the matrix.
 */
struct solution*
deduce_solution(const struct configuration* cfg, const struct matrix* A);

/**
 * All following structures and prototypes are needed
 * for the unit-tests of this module.
 */

struct bounds
{
  int* lower;
  int* upper;
};

/**
 * For each row of the matrix compute the lower and upper bounds.
 *  + Lower: for each row add the negative values.
 *  + Upper: for each row add the positive values.
 */
PROTOTYPE_FOR_UNIT_TEST(struct bounds* compute_bounds(const struct matrix* A));

/**
 * Free the bounds previously allocated by 'bounds_get'.
 */
PROTOTYPE_FOR_UNIT_TEST(void destroy_bounds(struct bounds* bounds));

/**
 * Set the list the empty cells.
 */
PROTOTYPE_FOR_UNIT_TEST(void set_empty(const struct configuration* cfg,
                                       const struct matrix* A,
                                       const struct bounds* bounds,
                                       struct solution* solution));

/**
 * Set the list of mines in the solution from:
 *  + configuration.
 *  + bounds.
 */
PROTOTYPE_FOR_UNIT_TEST(void set_mines(const struct configuration* cfg,
                                       const struct matrix* A,
                                       const struct bounds* bounds,
                                       struct solution* solution));

#endif /* !__SOLUTION_H__ */
