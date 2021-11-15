/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(add_row, 2x3)
{
  matrix_t* A = matrix_new(2, 3);
  matrix_t* B = matrix_new(2, 3);

  const static float elts[] = {
    1, 2, 3, 3, 4, 5,
  };
  const static float expected[] = {
    1, 2, 3, 5, 8, 11,
  };

  matrix_set(A, elts);
  matrix_set(B, expected);

  add_row(A, 1, 0, 2);
  EXPECT_TRUE(matrix_eq(A, B));

  matrix_destroy(A);
  matrix_destroy(B);
  return true;
}
