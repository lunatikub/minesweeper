#ifndef __MATRIX_H__
#define __MATRIX_H__

/** Opaque structure of a matrix */
typedef struct matrix matrix_t;

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

#endif /* !__MATRIX_H__ */
