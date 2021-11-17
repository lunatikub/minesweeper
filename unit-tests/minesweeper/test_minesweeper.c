#include <minesweeper/minesweeper.h>

#include "common.h"
#include "minesweeper_unit-test.h"
#include "utest.h"

/** List of sub-section tests **/
#include "test_adjacent.h"

/* clang-format off */
const static struct test minesweeper_tests[] = {
  TEST(adjacent, simple),
  TEST(adjacent, advanced),
};
/* clang-format on */

TEST_SUITE(minesweeper);
