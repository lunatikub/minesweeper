#include "common.h"
#include "configuration.h"
#include "solver_unit-test.h"
#include "utest.h"
#include <solver.h>

/** List of sub-section tests **/
#include "test_find_unsolved.h"
#include "test_solver.h"

const static struct test solver_tests[] = {
  TEST(find_unsolved, simple),
  TEST(find_unsolved, not_found),
  TEST(solver, simple),
};

TEST_SUITE(solver);
