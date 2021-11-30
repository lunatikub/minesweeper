#ifndef __MATRIX_UNIT_TEST_H__
#define __MATRIX_UNIT_TEST_H__

#include <stdbool.h>

#include <matrix/matrix.h>
#include <unit-test.h>

/**
 * All following structures and prototypes are needed
 * for the unit-tests of this module.
 */

/**
 * Swap tow rows 'i' and 'j'.
 */
PROTOTYPE_FOR_UNIT_TEST(void swap_row(struct matrix* A,
                                      unsigned i,
                                      unsigned j));

/**
 * Multiply a row 'i' by a constant 'lambda'.
 */
PROTOTYPE_FOR_UNIT_TEST(void mult_row(struct matrix* A,
                                      unsigned i,
                                      long double lambda));

/**
 * Add to the row 'i' the product of the other row 'j'
 * multiply by a constant 'lambda'.
 */
PROTOTYPE_FOR_UNIT_TEST(
  void add_row(struct matrix* A, unsigned i, unsigned j, long double lambda));

#endif /* !__MATRIX_UNIT_TEST_H__ */
