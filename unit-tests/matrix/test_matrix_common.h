#ifndef __TEST_MATRIX_COMMON_H__
#define __TEST_MATRIX_COMMON_H__

#define TEST_MATRIX(R, C, ELTS, EXPECTED, CODE)                                \
  matrix_t* A = matrix_new((R), (C));                                          \
  matrix_t* B = matrix_new((R), (C));                                          \
  matrix_set(A, (ELTS));                                                       \
  matrix_set(B, (EXPECTED));                                                   \
  CODE;                                                                        \
  EXPECT_TRUE(matrix_eq(A, B));                                                \
  matrix_destroy(A);                                                           \
  matrix_destroy(B);

#endif /* !__TEST_MATRIX_COMMON_H__ */
