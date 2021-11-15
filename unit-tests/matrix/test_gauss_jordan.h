/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(gauss_jordan, 2x3)
{
  /* clang-format off */
  const static long double elts[] = {
    1, 3, 7,
    3, 4, 11,
  };
  const static long double expected[] = {
    1, 0, 1,
    0, 1, 2,
  };
  /* clang-format on */

  TEST_MATRIX(2, 3, elts, expected, matrix_gauss_jordan(A));
  return true;
}

TEST_F(gauss_jordan, 3x4_1)
{
  /* clang-format off */
  const static long double elts[] = {
    1, -1,  2,  5,
    3,  2,  1,  10,
    2, -3, -2, -10,
  };
  const static long double expected[] = {
    1, 0, 0, 1,
    0, 1, 0, 2,
    0, 0, 1, 3,
  };
  /* clang-format on */

  TEST_MATRIX(3, 4, elts, expected, matrix_gauss_jordan(A));
  return true;
}

TEST_F(gauss_jordan, 3x4_2)
{
  /* clang-format off */
  const static long double elts[] = {
    2, 1, 2, 10,
    1, 2, 1, 8,
    3, 1, -1, 2,
  };
  const static long double expected[] = {
    1, 0, 0, 1,
    0, 1, 0, 2,
    0, 0, 1, 3,
  };
  /* clang-format on */

  TEST_MATRIX(3, 4, elts, expected, matrix_gauss_jordan(A));
  return true;
}
