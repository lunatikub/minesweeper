#include "common.h"
#include "matrix_unit-test.h"
#include "utest.h"
#include <matrix.h>

/** List of sub-section tests **/
#include "test_swap_row.h"

const static struct test matrix_tests[] = {
  TEST(swap_row, 3x3),
  TEST(swap_row, 2x3),
};

TEST_SUITE(matrix);
