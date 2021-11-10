#include <stdlib.h>

#include <matrix.h>

struct matrix
{
  unsigned m; /* rows */
  unsigned n; /* colums */
  int* e;     /* elements */
};

struct matrix*
matrix_new(unsigned m, unsigned n)
{
  struct matrix* A = calloc(1, sizeof(*A));

  A->m = m;
  A->n = n;
  A->e = calloc(m * n, sizeof(int));

  return A;
}

void
matrix_destroy(struct matrix* A)
{
  free(A->e);
  free(A);
}
