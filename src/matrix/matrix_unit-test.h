#ifndef __MATRIX_UNIT_TEST_H__
#define __MATRIX_UNIT_TEST_H__

#include <matrix.h>
#include <stdbool.h>
#include <unit-test.h>

/**
 * This file defines all prototypes needed for the unit-tests
 * of this matrix module.
 */

PROTOTYPE_FOR_UNIT_TEST(void swap_row(matrix_t* A, unsigned i, unsigned j));

PROTOTYPE_FOR_UNIT_TEST(void matrix_set(struct matrix* A,
                                        const long double* e));

PROTOTYPE_FOR_UNIT_TEST(bool matrix_eq(const struct matrix* A,
                                       const struct matrix* B));

PROTOTYPE_FOR_UNIT_TEST(void mult_row(struct matrix* A,
                                      unsigned i,
                                      long double lambda));

PROTOTYPE_FOR_UNIT_TEST(
  void add_row(struct matrix* A, unsigned i, unsigned j, long double lambda));

#endif /* !__MATRIX_UNIT_TEST_H__ */
