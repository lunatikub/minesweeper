/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(swap_row, 3x3)
{
  /* clang-format off */
  const static long double elts[] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9,
  };
  const static long double expected[] = {
    7, 8, 9,
    4, 5, 6,
    1, 2, 3,
  };
  /* clang-format on */

  TEST_MATRIX(3, 3, elts, expected, swap_row(A, 0, 2));
  return true;
}

TEST_F(swap_row, 2x3)
{
  /* clang-format off */
  const static long double elts[] = {
    1, 2, 3,
    4, 5, 6,
  };

  const static long double expected[] = {
    4, 5, 6,
    1, 2, 3,
  };
  /* clang-format on */

  TEST_MATRIX(2, 3, elts, expected, swap_row(A, 0, 1));
  return true;
}
