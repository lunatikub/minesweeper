/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

#define TEST_MAP                                                               \
  do {                                                                         \
    struct grid* grid = grid_create(w, h);                                     \
    struct grid* adjacents = grid_create(w, h);                                \
    CELLS_SET(grid, initial_setup);                                            \
    struct configuration* cfg = configuration_create(grid);                    \
    struct matrix* A = configuration_map(cfg, grid, adjacents);                \
    struct matrix* B = matrix_new(cfg->nr_unsolved, cfg->nr_covered + 1);      \
    matrix_set(B, expected);                                                   \
    EXPECT_TRUE(matrix_eq(A, B));                                              \
    configuration_destroy(cfg);                                                \
    matrix_destroy(A);                                                         \
    matrix_destroy(B);                                                         \
    grid_destroy(grid);                                                        \
    grid_destroy(adjacents);                                                   \
  } while (0)

TEST_F(map, simple)
{
  CFG(3, 3, 0);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    1, C, 0,
    C, 1, 0,
    1, C, 0,
  };
  const static long double expected[] = {
    1, 1, 0, 1,
    1, 1, 1, 1,
    1, 0, 1, 1,
  };
  /* clang-format on */

  TEST_MAP;
  return true;
}

TEST_F(map, advanced)
{
  CFG(5, 5, 0);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    M, 0, 0, M, C,
    1, 0, 0, 2, C,
    0, 1, C, 1, C,
    0, C, 2, 2, 1,
    0, 0, 0, 0, M,
  };
  const static long double expected[] = {
    1, 1, 1, 1, 0, 2,
    1, 0, 1, 1, 0, 1,
    1, 0, 0, 0, 1, 2,
    1, 0, 0, 0, 1, 1,
    1, 0, 0, 1, 0, 2,
  };
  /* clang-format on */

  TEST_MAP;
  return true;
}

TEST_F(map, post)
{
  CFG(4, 6, 0);

  /* clang-format off */
  static const unsigned initial_setup[] = {
    0, 1, C, C,
    0, 1, C, C,
    0, 1, 2, C,
    0, 0, 2, C,
    1, 1, 2, C,
    C, C, C, C,
  };
  const static long double expected[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
    0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 2,
  };
  /* clang-format on */

  TEST_MAP;
  return true;
}
