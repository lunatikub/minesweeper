/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

static inline bool
coord_exist(const struct coord* l, unsigned n, const struct coord* c)
{
  for (unsigned i = 0; i < n; ++i) {
    const struct coord* _c = &l[i];
    if (_c->x == c->x && _c->y == c->y) {
      return true;
    }
  }
  return false;
}

#define TEST_CONFIGURATION(GRID, UNSOLVED, COVERED)                            \
  do {                                                                         \
    struct configuration* cfg = configuration_get(GRID);                       \
    unsigned nr_unsolved_expected = sizeof(UNSOLVED) / sizeof(struct coord);   \
    unsigned nr_covered_expected = sizeof(COVERED) / sizeof(struct coord);     \
    EXPECT_UINT_EQ(cfg->nr_unsolved, nr_unsolved_expected);                    \
    EXPECT_UINT_EQ(cfg->nr_covered, nr_covered_expected);                      \
    for (unsigned i = 0; i < nr_unsolved_expected; ++i) {                      \
      const struct coord* c = &UNSOLVED[i];                                    \
      EXPECT_TRUE(coord_exist(cfg->unsolved, cfg->nr_unsolved, c));            \
    }                                                                          \
    for (unsigned i = 0; i < nr_covered_expected; ++i) {                       \
      const struct coord* c = &COVERED[i];                                     \
      EXPECT_TRUE(coord_exist(cfg->covered, cfg->nr_covered, c));              \
    }                                                                          \
    configuration_destroy(cfg);                                                \
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
    { 1, 1 }, { 0, 0 }, { 0, 2 },
  };
  static const struct coord covered_expected[] = {
    { 0, 1 }, { 1, 2 }, { 1, 2 },
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  TEST_CONFIGURATION(grid, unsolved_expected, covered_expected);

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
  static const struct coord covered_expected[] = {
    { 1, 3 }, { 2, 2 }, { 4, 0 }, { 4, 1 }, { 4, 2 },
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  TEST_CONFIGURATION(grid, unsolved_expected, covered_expected);

  minesweeper_grid_destroy(grid);
  return true;
}
