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

static inline unsigned
coord_find_idx(const struct coord* l, unsigned n, const struct coord* c)
{
  for (unsigned i = 0; i < n; ++i) {
    const struct coord* _c = &l[i];
    if (_c->x == c->x && _c->y == c->y) {
      return i;
    }
  }
  return -1;
}

#define TEST_CFG_UNSOLVED(CFG, UNSOLVED)                                       \
  for (unsigned i = 0; i < CFG->nr_unsolved; ++i) {                            \
    EXPECT_TRUE(coord_exist(cfg->unsolved, cfg->nr_unsolved, &UNSOLVED[i]));   \
  }

#define TEST_CFG_COVERED(CFG, COVERED)                                         \
  for (unsigned i = 0; i < CFG->nr_covered; ++i) {                             \
    EXPECT_TRUE(coord_exist(cfg->covered, cfg->nr_covered, &COVERED[i]));      \
  }

#define TEST_CFG_EDGES(CFG, UNSOLVED, COVERED, NR_EDGE)                        \
  for (unsigned i = 0; i < cfg->nr_unsolved; ++i) {                            \
    unsigned idx_unsolved =                                                    \
      coord_find_idx(cfg->unsolved, cfg->nr_unsolved, &UNSOLVED[i]);           \
    EXPECT_UINT_EQ(cfg->nr_edge[idx_unsolved], NR_EDGE[i]);                    \
  }

#define TEST_CONFIGURATION(GRID, UNSOLVED, COVERED, NR_EDGE)                   \
  do {                                                                         \
    struct configuration* cfg = configuration_get(GRID);                       \
    unsigned nr_unsolved = sizeof(UNSOLVED) / sizeof(struct coord);            \
    unsigned nr_covered = sizeof(COVERED) / sizeof(struct coord);              \
    EXPECT_UINT_EQ(cfg->nr_unsolved, nr_unsolved);                             \
    EXPECT_UINT_EQ(cfg->nr_covered, nr_covered);                               \
    TEST_CFG_UNSOLVED(cfg, UNSOLVED);                                          \
    TEST_CFG_COVERED(cfg, COVERED);                                            \
    TEST_CFG_EDGES(cfg, UNSOLVED, COVERED, NR_EDGE);                           \
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
    {0,0}, {1,1}, {0,2},
  };
  static const struct coord covered_expected[] = {
    {1,0}, {0,1}, {1,2},
  };
  static const unsigned nr_edge_expected[] = {
    2, 3, 2,
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  TEST_CONFIGURATION(
    grid, unsolved_expected, covered_expected, nr_edge_expected);

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
    {1,2}, {2,3}, {3,1}, {3,2}, {3,3},
  };
  static const struct coord covered_expected[] = {
    {1,3}, {2,2}, {4,0}, {4,1}, {4,2},
  };
  static const unsigned nr_edge_expected[] = {
    2, 2, 4, 3, 2,
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  TEST_CONFIGURATION(
    grid, unsolved_expected, covered_expected, nr_edge_expected);

  minesweeper_grid_destroy(grid);
  return true;
}

TEST_F(configuration, post)
{
  CFG(4, 6, 0);
  struct grid* grid = minesweeper_grid_new(w, h);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    0, 1, C, C,
    0, 1, C, C,
    0, 1, 2, C,
    0, 0, 2, C,
    1, 1, 2, C,
    C, C, C, C,
  };
  static const struct coord unsolved_expected[] = {
    {1,0}, {1,1}, {1,2}, {2,2}, {2,3}, {0,4}, {1,4}, {2,4},
  };
  static const struct coord covered_expected[] = {
    {2,0}, {2,1}, {3,1}, {3,2}, {3,3}, {3,4},
    {3,5}, {2,5}, {1,5}, {0,5},
  };
  static const unsigned nr_edge_expected[] = {
    2, 2, 1, 4, 3, 2, 3, 5,
  };
  /* clang-format on */
  CELLS_SET(grid, initial_setup);

  TEST_CONFIGURATION(
    grid, unsolved_expected, covered_expected, nr_edge_expected);

  minesweeper_grid_destroy(grid);
  return true;
}
