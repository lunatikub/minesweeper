#include "common.h"
#include "matrix_unit-test.h"
#include "utest.h"
#include <matrix.h>

/** List of sub-section tests **/
#include "test_operation.h"

const static struct test matrix_tests[] = {
  TEST(operation, swap),
};

TEST_SUITE(matrix);
