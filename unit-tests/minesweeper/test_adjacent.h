/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(adjacent, simple)
{
  CFG(2, 2, 0);

  struct grid* grid = grid_create(w, h);
  struct grid* adjacents = grid_create(w, h);

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
  grid_adjacents(grid, adjacents);

  EXPECT_TRUE(
    CELLS_EQ(expected_adjacent, adjacents->cells, CELLS_SZ(adjacents)));

  grid_destroy(grid);
  grid_destroy(adjacents);
  return true;
}

TEST_F(adjacent, advanced)
{
  CFG(5, 5, 0);
  struct grid* grid = grid_create(w, h);
  struct grid* adjacents = grid_create(w, h);

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
  grid_adjacents(grid, adjacents);

  EXPECT_TRUE(
    CELLS_EQ(expected_adjacent, adjacents->cells, CELLS_SZ(adjacents)));

  grid_destroy(grid);
  grid_destroy(adjacents);
  return true;
}
