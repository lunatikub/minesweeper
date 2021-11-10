/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(operation, swap)
{
  matrix_t* A = matrix_new(3, 3);
  (void)A;
  matrix_destroy(A);
  return true;
}
