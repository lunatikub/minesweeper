#include <minesweeper/list_cell.h>

#include "common.h"
#include "minesweeper_unit-test.h"
#include "utest.h"

/** List of sub-section tests **/
#include "test_adjacent.h"
#include "test_list_cell.h"

/* clang-format off */
const static struct test minesweeper_tests[] = {
  TEST(list_cell, simple),
  TEST(list_cell, unbound),
  TEST(list_cell, exist),
  TEST(adjacent, simple),
  TEST(adjacent, advanced),
};
/* clang-format on */

TEST_SUITE(minesweeper);
