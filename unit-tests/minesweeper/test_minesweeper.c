#include "common.h"
#include "minesweeper_unit-test.h"
#include "utest.h"
#include <minesweeper.h>

/** List of sub-section tests **/
#include "test_adjacent.h"

const static struct test minesweeper_tests[] = {
  TEST(adjacent, simple),
  TEST(adjacent, advanced),
};

TEST_SUITE(minesweeper);
