/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(mult_row, 1x3)
{
  /* clang-format off */
  const static long double elts[] = {
    1, 2, 3,
  };
  const static long double expected[] = {
    2, 4, 6,
  };
  /* clang-format on */

  TEST_MATRIX(1, 3, elts, expected, mult_row(A, 0, 2));
  return true;
}
