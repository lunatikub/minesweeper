/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(adjacent_mine, simple)
{
  const static unsigned w = 2;
  const static unsigned h = 2;

  struct grid* grid = minesweeper_grid_new(w, h);
  struct grid* adjacent = minesweeper_grid_new(w, h);

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
  solver_adjacent_mines(grid, adjacent);

  EXPECT_TRUE(CELLS_EQ(expected_adjacent, adjacent->cells, CELLS_SZ(adjacent)));

  minesweeper_grid_destroy(grid);
  minesweeper_grid_destroy(adjacent);
  return true;
}

TEST_F(adjacent_mine, advanced)
{
  const static unsigned w = 5;
  const static unsigned h = 5;

  struct grid* grid = minesweeper_grid_new(w, h);
  struct grid* adjacent = minesweeper_grid_new(w, h);

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
  solver_adjacent_mines(grid, adjacent);

  EXPECT_TRUE(CELLS_EQ(expected_adjacent, adjacent->cells, CELLS_SZ(adjacent)));

  minesweeper_grid_destroy(grid);
  minesweeper_grid_destroy(adjacent);
  return true;
}
