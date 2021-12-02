/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

#define TEST_SOLVE(W, H, GRID_INIT, EE, ME)                                    \
  do {                                                                         \
    static const unsigned w = W;                                               \
    static const unsigned h = H;                                               \
    struct grid* grid = grid_create(w, h);                                     \
    CELLS_SET(grid, GRID_INIT);                                                \
    struct solution* solution = solve(grid);                                   \
    EXPECT_TRUE(solution != NULL);                                             \
    EXPECT_TRUE(solution->nr_empty == sizeof(EE) / sizeof(struct coord));      \
    EXPECT_TRUE(solution->nr_mine == sizeof(ME) / sizeof(struct coord));       \
    unsigned i;                                                                \
    for (i = 0; i < solution->nr_empty; ++i) {                                 \
      const struct coord* c1 = &EE[i];                                         \
      const struct coord* c2 = &solution->empty[i];                            \
      EXPECT_TRUE(c1->x == c2->x && c1->y == c2->y);                           \
    }                                                                          \
    for (i = 0; i < solution->nr_mine; ++i) {                                  \
      const struct coord* c1 = &ME[i];                                         \
      const struct coord* c2 = &solution->mines[i];                            \
      EXPECT_TRUE(c1->x == c2->x && c1->y == c2->y);                           \
    }                                                                          \
    grid_destroy(grid);                                                        \
    solution_destroy(solution);                                                \
  } while (0)

TEST_F(solver, simple)
{
  /* clang-format off */
  static const unsigned grid_init[] = {
    1, C, 0,
    C, 1, 0,
    1, C, 0,
  };
  static const struct coord empty_expected[] = {
    { 1, 0 },
    { 1, 2 },
  };
  static const struct coord mines_expected[] = {
    { 0, 1 },
  };
  /* clang-format on */

  TEST_SOLVE(3, 3, grid_init, empty_expected, mines_expected);
  return true;
}

TEST_F(solver, already_resolved)
{
  CFG(3, 3, 0);
  struct grid* grid = grid_create(w, h);
  /* clang-format off */
  static const unsigned grid_init[] = {
    1, C, 0,
    F, 1, 0,
    1, C, 0,
  };
  /* clang-format on */
  CELLS_SET(grid, grid_init);

  struct solution* solution = solve(grid);
  EXPECT_TRUE(solution == NULL);

  grid_destroy(grid);
  return true;
}

TEST_F(solver, post)
{
  /* clang-format off */
  static const unsigned grid_1[] = {
    0, 1, C, C,
    0, 1, C, C,
    0, 1, 2, C,
    0, 0, 2, C,
    1, 1, 2, C,
    C, C, C, C,
  };
  static const struct coord empty_expected_1[] = {
    { 2, 0 }, { 3, 1 }, { 2, 5 },
  };
  static const struct coord mines_expected_1[] = {
    { 2, 1 }, { 3, 4 },
  };
  /* clang-format on */

  TEST_SOLVE(4, 6, grid_1, empty_expected_1, mines_expected_1);

  return true;
}
