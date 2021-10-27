#include "common.h"
#include "grid.h"
#include "test.h"

TEST_F(basic)
{
  const static unsigned w = 2;
  const static unsigned h = 2;

  struct grid* grid = grid_new(w, h);
  struct grid* adjacent = grid_new(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    0, 0,
    0, M,
  };

  static const unsigned expected_adjacent[] = {
    1, 1,
    1, 0,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);
  grid_get_adjacent_mines(grid, adjacent);

  EXPECT_TRUE(CELLS_EQ(expected_adjacent, adjacent->cells, CELLS_SZ(adjacent)));

  grid_destroy(grid);
  grid_destroy(adjacent);
  return true;
}

TEST_F(advanced)
{
  struct grid* grid = grid_new(5, 5);
  struct grid* adjacent = grid_new(5, 5);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    0, 0, 0, 0, 0,
    0, M, M, 0, 0,
    0, M, 0, 0, M,
    0, M, 0, M, 0,
    M, 0, 0, M, 0,
  };

  static const unsigned expected_adjacent[] = {
    1, 2, 2, 1, 0,
    2, 0, 0, 2, 1,
    3, 0, 5, 3, 0,
    3, 0, 4, 0, 3,
    0, 2, 3, 0, 2,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);
  grid_get_adjacent_mines(grid, adjacent);

  EXPECT_TRUE(CELLS_EQ(expected_adjacent, adjacent->cells, CELLS_SZ(adjacent)));

  grid_destroy(grid);
  grid_destroy(adjacent);
  return true;
}

const static struct test adjacent_mines_tests[] = {
  TEST(basic),
  TEST(advanced),
};

TEST_SUITE(adjacent_mines);
