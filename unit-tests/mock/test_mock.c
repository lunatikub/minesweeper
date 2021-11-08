#include "common.h"
#include "game.h"
#include "list_cell.h"
#include "mock_unit-test.h"
#include "utest.h"
#include <mock.h>

/** List of sub-section tests **/
#include "test_game.h"
#include "test_list_cell.h"

const static struct test mock_tests[] = {
  TEST(list_cell, simple),
  TEST(list_cell, unbound),
  TEST(game, lost),
};

TEST_SUITE(mock);