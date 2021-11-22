/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

#define TEST_UNSOLVED(CFG, EXPECTED)                                           \
  do {                                                                         \
    unsigned nr_expected = sizeof(EXPECTED) / sizeof(struct coord);            \
    EXPECT_UINT_EQ((CFG)->nr_unsolved, nr_expected);                           \
    for (unsigned i = 0; i < nr_expected; ++i) {                               \
      const struct coord* c1 = &EXPECTED[i];                                   \
      const struct coord* c2 = &(CFG)->unsolved[i];                            \
      EXPECT_TRUE(c1->x == c2->x && c1->y == c2->y);                           \
    }                                                                          \
  } while (0)

TEST_F(configuration, simple)
{
  CFG(3, 3, 0);
  struct grid* grid = minesweeper_grid_new(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    1, C, 0,
    C, 1, 0,
    1, C, 0,

  };
  static const struct coord unsolved_expected[] = {
    { 0, 2 }, { 1, 1 }, { 0, 0 },
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  struct configuration* cfg = configuration_get(grid);
  TEST_UNSOLVED(cfg, unsolved_expected);

  configuration_destroy(cfg);
  minesweeper_grid_destroy(grid);
  return true;
}

TEST_F(configuration, advanced)
{
  CFG(5, 5, 0);
  struct grid* grid = minesweeper_grid_new(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    M, 0, 0, M, C,
    1, 0, 0, 2, C,
    0, 1, C, 1, C,
    0, C, 2, 2, 1,
    0, 0, 0, 0, M,
  };
  static const struct coord unsolved_expected[] = {
    { 3, 3 }, { 1, 2 }, { 2, 3 }, { 3, 2 }, { 3, 1 },
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  struct configuration* cfg = configuration_get(grid);
  TEST_UNSOLVED(cfg, unsolved_expected);

  configuration_destroy(cfg);
  minesweeper_grid_destroy(grid);
  return true;
}
