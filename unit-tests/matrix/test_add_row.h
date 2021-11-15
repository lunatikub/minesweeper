/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(add_row, 2x3)
{
  /* clang-format off */
  const static long double elts[] = {
    1, 2, 3,
    3, 4, 5,
  };
  const static long double expected[] = {
    1, 2, 3,
    5, 8, 11,
  };
  /* clang-format on */

  TEST_MATRIX(2, 3, elts, expected, add_row(A, 1, 0, 2));
  return true;
}
