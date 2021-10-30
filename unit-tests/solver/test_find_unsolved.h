/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(find_unsolved, simple)
{
  const static unsigned w = 3;
  const static unsigned h = 3;

  struct grid* grid = minesweeper_grid_new(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    0, 0, 0,
    0, C, 2,
    0, 0, M,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);

  struct coord unsolved;
  EXPECT_TRUE(solver_find_unsolved(grid, &unsolved));

  EXPECT_UINT_EQ(unsolved.x, 2);
  EXPECT_UINT_EQ(unsolved.y, 1);

  minesweeper_grid_destroy(grid);
  return true;
}

TEST_F(find_unsolved, not_found)
{
  const static unsigned w = 3;
  const static unsigned h = 3;

  struct grid* grid = minesweeper_grid_new(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    C, 0, 0,
    0, M, 2,
    0, 0, M,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);

  struct coord unsolved;
  EXPECT_FALSE(solver_find_unsolved(grid, &unsolved));

  minesweeper_grid_destroy(grid);
  return true;
}
