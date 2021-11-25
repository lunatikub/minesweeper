#include <stdlib.h>

#include <matrix/matrix.h>

#include "matrix_unit-test.h"

void
matrix_set(struct matrix* A, const long double* e)
{
  for (unsigned i = 0; i < A->m; ++i) {
    for (unsigned j = 0; j < A->n; ++j) {
      A->e[i][j] = e[i * A->n + j];
    }
  }
}

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
mult_row(struct matrix* A, unsigned i, long double lambda)
{
  for (unsigned k = 0; k < A->n; ++k) {
    A->e[i][k] *= lambda;
  }
}

/** Add to a row the product of another row
    multiply by a constant. */
PRIVATE_EXCEPT_UNIT_TEST
void
add_row(struct matrix* A, unsigned i, unsigned j, long double lambda)
{
  for (unsigned k = 0; k < A->n; ++k) {
    A->e[i][k] += lambda * A->e[j][k];
  }
}

/** Return the index of the first pivot not null found
    in the column j from row i to m-1, otherwise return -1. */
static inline int
pivot(struct matrix* A, unsigned i, unsigned j)
{
  unsigned k = i;
  while (k < A->m && A->e[k][j] == 0) {
    ++k;
  }
  return k == A->m ? -1 : k;
}

void
matrix_gauss_jordan(struct matrix* A)
{
  unsigned i = 0;
  unsigned j = 0;

  while (i < A->m && j < A->n) {
    int r = pivot(A, i, j);
    if (r != -1) {
      if (r != i) {
        swap_row(A, i, r);
      }
      if (A->e[i][j] != 1) {
        mult_row(A, i, 1 / A->e[i][j]);
      }
      for (unsigned k = 0; k < A->m; ++k) {
        if (k != i && A->e[k][j] != 0) {
          add_row(A, k, i, -A->e[k][j]);
        }
      }
      ++i;
      ++j;
    } else {
      ++j;
    }
  }
}

struct matrix*
matrix_new(unsigned m, unsigned n)
{
  struct matrix* A = calloc(1, sizeof(*A));

  A->m = m;
  A->n = n;
  A->e = calloc(m, sizeof(long double*));
  for (unsigned i = 0; i < m; ++i) {
    A->e[i] = calloc(n, sizeof(long double));
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
