/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(swap_row, 3x3)
{
  matrix_t* A = matrix_new(3, 3);
  matrix_t* B = matrix_new(3, 3);

  const static int elts[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9,
  };

  const static int expected[] = {
    7, 8, 9, 4, 5, 6, 1, 2, 3,
  };

  matrix_set(A, elts);
  matrix_set(B, expected);

  swap_row(A, 0, 2);

  EXPECT_TRUE(matrix_eq(A, B));

  matrix_destroy(A);
  matrix_destroy(B);
  return true;
}

TEST_F(swap_row, 2x3)
{
  matrix_t* A = matrix_new(2, 3);
  matrix_t* B = matrix_new(2, 3);

  const static int elts[] = {
    1, 2, 3, 4, 5, 6,
  };

  const static int expected[] = {
    4, 5, 6, 1, 2, 3,
  };

  matrix_set(A, elts);
  matrix_set(B, expected);

  swap_row(A, 0, 1);

  EXPECT_TRUE(matrix_eq(A, B));

  matrix_destroy(A);
  matrix_destroy(B);
  return true;
}
