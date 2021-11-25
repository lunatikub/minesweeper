#ifndef __MATRIX_UNIT_TEST_H__
#define __MATRIX_UNIT_TEST_H__

#include <stdbool.h>

#include <matrix/matrix.h>
#include <unit-test.h>

/**
 * This file defines all prototypes needed for the unit-tests
 * of this matrix module.
 */

PROTOTYPE_FOR_UNIT_TEST(void swap_row(struct matrix* A,
                                      unsigned i,
                                      unsigned j));

PROTOTYPE_FOR_UNIT_TEST(void mult_row(struct matrix* A,
                                      unsigned i,
                                      long double lambda));

PROTOTYPE_FOR_UNIT_TEST(
  void add_row(struct matrix* A, unsigned i, unsigned j, long double lambda));

#endif /* !__MATRIX_UNIT_TEST_H__ */
