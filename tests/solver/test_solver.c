#include "common.h"
#include "grid.h"
#include "test.h"
#include <solver.h>

/** List of sub-section tests **/
#include "test_adjacent_mine.h"
#include "test_solver.h"

const static struct test solver_tests[] = {
  /* adjacent_mine */
  TEST(adjacent_mine, simple),
  TEST(adjacent_mine, advanced),
  /* solver */
  TEST(solver, simple),
};

TEST_SUITE(solver);
