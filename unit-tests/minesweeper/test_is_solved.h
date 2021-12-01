/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(is_solved, solved)
{
  CFG(2, 2, 0);

  struct grid* grid = grid_create(w, h);
  /* clang-format off */
  static const unsigned initial_setup[] = {
    F, 2,
    2, F,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);

  EXPECT_TRUE(is_solved(grid, 0, 1));
  EXPECT_TRUE(is_solved(grid, 1, 0));

  EXPECT_FALSE(is_solved(grid, 0, 0));
  EXPECT_FALSE(is_solved(grid, 1, 1));

  grid_destroy(grid);
  return true;
}

TEST_F(is_solved, unsolved)
{
  CFG(3, 3, 0);

  struct grid* grid = grid_create(w, h);
  /* clang-format off */
  static const unsigned initial_setup[] = {
    C, 2, M,
    C, C, 3,
    C, C, C,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);

  EXPECT_FALSE(is_solved(grid, 1, 0));
  EXPECT_FALSE(is_solved(grid, 2, 1));

  grid_destroy(grid);
  return true;
}
