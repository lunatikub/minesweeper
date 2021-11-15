#include "common.h"
#include "matrix_unit-test.h"
#include "test_matrix_common.h"
#include "utest.h"
#include <matrix.h>

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
