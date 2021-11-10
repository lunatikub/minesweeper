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
 * @param grid Matrix handle.
 */
void
matrix_destroy(struct matrix* A);

#endif /* !__MATRIX_H__ */
