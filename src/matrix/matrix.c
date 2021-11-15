#include <stdlib.h>

#include "matrix_unit-test.h"
#include <matrix.h>

struct matrix
{
  unsigned m; /* rows */
  unsigned n; /* colums */
  float** e;  /* elements */
};

/** Set the elements of the matrix A with
    the elements given in argument. */
PRIVATE_EXCEPT_UNIT_TEST
void
matrix_set(struct matrix* A, const float* e)
{
  for (unsigned i = 0; i < A->m; ++i) {
    for (unsigned j = 0; j < A->n; ++j) {
      A->e[i][j] = e[i * A->n + j];
    }
  }
}

/** Return true if the both matrix are equals,
    otherwise return false. */
PRIVATE_EXCEPT_UNIT_TEST
bool
matrix_eq(const struct matrix* A, const struct matrix* B)
{
  if (A->m != B->m || A->n != B->n) {
    return false;
  }

  for (unsigned i = 0; i < A->m; ++i) {
    for (unsigned j = 0; j < A->n; ++j) {
      if (A->e[i][j] != B->e[i][j]) {
        return false;
      }
    }
  }
  return true;
}

/** Swap two rows. */
PRIVATE_EXCEPT_UNIT_TEST
void
swap_row(struct matrix* A, unsigned i, unsigned j)
{
  for (unsigned k = 0; k < A->n; ++k) {
    unsigned tmp = A->e[i][k];
    A->e[i][k] = A->e[j][k];
    A->e[j][k] = tmp;
  }
}

/** Multiply a row by a constant. */
PRIVATE_EXCEPT_UNIT_TEST
void
mult_row(struct matrix* A, unsigned i, float lambda)
{
  for (unsigned k = 0; k < A->n; ++k) {
    A->e[i][k] *= lambda;
  }
}

/** Add to a row the product of another row
    multiply by a constant. */
PRIVATE_EXCEPT_UNIT_TEST
void
add_row(struct matrix* A, unsigned i, unsigned j, float lambda)
{
  for (unsigned k = 0; k < A->n; ++k) {
    A->e[i][k] += lambda * A->e[j][k];
  }
}

struct matrix*
matrix_new(unsigned m, unsigned n)
{
  struct matrix* A = calloc(1, sizeof(*A));

  A->m = m;
  A->n = n;
  A->e = calloc(m, sizeof(float*));
  for (unsigned i = 0; i < m; ++i) {
    A->e[i] = calloc(n, sizeof(float));
  }

  return A;
}

void
matrix_destroy(struct matrix* A)
{
  for (unsigned i = 0; i < A->m; ++i) {
    free(A->e[i]);
  }
  free(A->e);
  free(A);
}
