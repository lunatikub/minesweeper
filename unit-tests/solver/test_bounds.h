/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(bounds, simple)
{
  /* clang-format off */
  const static unsigned m = 3;
  const static unsigned n = 4;
  const static long double elts[] = {
    1, -1, -1, 1,
    1,  1,  1, 2,
    1, -3,  2, 3,
  };
  const static int lower_expected[] = {
    -2,
     0,
    -3,
  };
  const static int upper_expected[] = {
    1,
    3,
    3,
  };
  /* clang-format on */

  struct matrix* A = matrix_new(m, n);
  matrix_set(A, elts);
  struct bounds* bounds = compute_bounds(A);
  for (unsigned i = 0; i < m; i++) {
    EXPECT_TRUE(bounds->lower[i] == lower_expected[i]);
    EXPECT_TRUE(bounds->upper[i] == upper_expected[i]);
  }
  destroy_bounds(bounds);
  matrix_destroy(A);

  return true;
}
