#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdbool.h>

struct matrix
{
  unsigned m;      /* rows */
  unsigned n;      /* columns */
  long double** e; /* elements */
};

/**
 * Create a matrix.
 *
 * @param m Number of rows.
 * @param n Number of colums.
 * @return Matrix handle allocated.
 */
struct matrix*
matrix_new(unsigned m, unsigned n);

/**
 * Destroy a matrix previously allocated by @c matrix_new.
 *
 * @param A Matrix handle.
 */
void
matrix_destroy(struct matrix* A);

/**
 * GaussJordan process in place the reduced
 * row echelon form of a matrix.
 *
 * @param A matrix handle.
 */
void
matrix_gauss_jordan(struct matrix* A);

/**
 * Compare two matrixs, return true if equal,
 * otherwise return false.
 */
bool
matrix_eq(const struct matrix* A, const struct matrix* B);

/**
 * Set the elements of the matrix A with
 * the elements given in argument.
 */
void
matrix_set(struct matrix* A, const long double* e);

#endif /* !__MATRIX_H__ */
