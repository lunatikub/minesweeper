#include <solver/solver.h>

#include "common.h"
#include "configuration.h"
#include "solver_unit-test.h"
#include "utest.h"

/** List of sub-section tests **/
#include "test_configuration.h"
#include "test_find_unsolved.h"
#include "test_map.h"
#include "test_solver.h"

/* clang-format off */
const static struct test solver_tests[] = {
  TEST(find_unsolved, simple),
  TEST(find_unsolved, not_found),
  TEST(configuration, simple),
  TEST(configuration, advanced),
  TEST(configuration, post),
  TEST(map, simple),
  TEST(map, advanced),
  TEST(map, post),
  TEST(solver, simple),
};
/* clang-format on */

TEST_SUITE(solver);
