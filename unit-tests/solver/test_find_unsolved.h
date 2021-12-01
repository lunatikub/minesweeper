/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(find_unsolved, simple)
{
  CFG(3, 3, 0);
  struct grid* grid = grid_create(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    0, 0, 0,
    0, C, 2,
    0, 0, M,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);

  struct coord unsolved;
  EXPECT_TRUE(find_unsolved(grid, &unsolved));

  EXPECT_UINT_EQ(unsolved.x, 2);
  EXPECT_UINT_EQ(unsolved.y, 1);

  grid_destroy(grid);
  return true;
}

TEST_F(find_unsolved, not_found)
{
  CFG(3, 3, 0);
  struct grid* grid = grid_create(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    C, 0, 0,
    0, M, 2,
    0, 0, M,
  };
  /* clang-format on */

  CELLS_SET(grid, initial_setup);

  struct coord unsolved;
  EXPECT_FALSE(find_unsolved(grid, &unsolved));

  grid_destroy(grid);
  return true;
}
