#include "common.h"
#include "matrix_unit-test.h"
#include "utest.h"
#include <matrix.h>

/** List of sub-section tests **/
#include "test_add_row.h"
#include "test_mult_row.h"
#include "test_swap_row.h"

const static struct test matrix_tests[] = {
  TEST(swap_row, 3x3),
  TEST(swap_row, 2x3),
  TEST(mult_row, 1x3),
  TEST(add_row, 2x3),
};

TEST_SUITE(matrix);
