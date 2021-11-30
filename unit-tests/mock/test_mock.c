#include <mock/mock.h>

#include "common.h"
#include "game.h"
#include "utest.h"

/** List of sub-section tests **/
#include "test_game.h"

/* clang-format off */
const static struct test mock_tests[] = {
  TEST(game, lost),
  TEST(game, set_empty),
  TEST(game, flag_unflag),
  TEST(game, win_flagged),
  TEST(game, win_covered),
};
/* clang-format on */

TEST_SUITE(mock);
