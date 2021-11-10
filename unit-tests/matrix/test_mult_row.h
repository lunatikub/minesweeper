/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(mult_row, 1x3)
{
  matrix_t* A = matrix_new(1, 3);
  matrix_t* B = matrix_new(1, 3);

  const static float elts[] = {
    1, 2, 3,
  };

  const static float expected[] = {
    2, 4, 6,
  };

  matrix_set(A, elts);
  matrix_set(B, expected);

  mult_row(A, 0, 2);

  EXPECT_TRUE(matrix_eq(A, B));

  matrix_destroy(A);
  matrix_destroy(B);
  return true;
}
