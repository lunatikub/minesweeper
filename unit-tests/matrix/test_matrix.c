#include <matrix/matrix.h>

#include "operation.h"
#include "test_common.h"
#include "utest.h"

#define TEST_MATRIX(R, C, ELTS, EXPECTED, CODE)                                \
  struct matrix* A = matrix_new((R), (C));                                     \
  struct matrix* B = matrix_new((R), (C));                                     \
  matrix_set(A, (ELTS));                                                       \
  matrix_set(B, (EXPECTED));                                                   \
  CODE;                                                                        \
  EXPECT_TRUE(matrix_eq(A, B));                                                \
  matrix_destroy(A);                                                           \
  matrix_destroy(B);

/** List of sub-section tests **/
#include "test_add_row.h"
#include "test_gauss_jordan.h"
#include "test_mult_row.h"
#include "test_swap_row.h"

/* clang-format off */
const static struct test matrix_tests[] = {
  TEST(swap_row, 3x3),
  TEST(swap_row, 2x3),
  TEST(mult_row, 1x3),
  TEST(add_row, 2x3),
  TEST(gauss_jordan, 2x3),
  TEST(gauss_jordan, 3x4_1),
  TEST(gauss_jordan, 3x4_2),
};
/* clang-format on */

TEST_SUITE(matrix);
