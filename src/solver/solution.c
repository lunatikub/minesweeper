#include <stdlib.h>

#include <solver/solver.h>

#include "configuration.h"
#include "solution.h"

PRIVATE_EXCEPT_UNIT_TEST
struct bounds*
compute_bounds(const struct matrix* A)
{
  struct bounds* bounds = calloc(1, sizeof(*bounds));

  bounds->lower = calloc(A->m, sizeof(unsigned));
  bounds->upper = calloc(A->m, sizeof(unsigned));

  for (unsigned i = 0; i < A->m; ++i) {
    unsigned u = 0, l = 0;
    /* don't process the augmented column. */
    for (unsigned j = 0; j < A->n - 1; ++j) {
      int v = A->e[i][j];
      u += v > 0 ? v : 0;
      l += v < 0 ? v : 0;
    }
    bounds->lower[i] = l;
    bounds->upper[i] = u;
  }

  return bounds;
}

PRIVATE_EXCEPT_UNIT_TEST
void
destroy_bounds(struct bounds* bounds)
{
  free(bounds->lower);
  free(bounds->upper);
  free(bounds);
}

PRIVATE_EXCEPT_UNIT_TEST
void
set_empty(const struct configuration* cfg,
          const struct matrix* A,
          const struct bounds* bounds,
          struct solution* solution)
{
  list_cell_t* empty = list_cell_create();

  for (unsigned i = 0; i < A->m; ++i) {
    int r = A->e[i][A->n - 1];
    for (unsigned j = 0; j < A->n - 1; ++j) {
      int v = A->e[i][j];
      if ((r == bounds->lower[i] && v > 0) ||
          (r == bounds->upper[i] && v < 0)) {
        list_cell_insert_tail(empty, cfg->covered[j]);
      }
    }
  }

  solution->empty = list_cell_to_array(empty, &solution->nr_mine);
  list_cell_destroy(empty);
}

PRIVATE_EXCEPT_UNIT_TEST
void
set_mines(const struct configuration* cfg,
          const struct matrix* A,
          const struct bounds* bounds,
          struct solution* solution)
{
  list_cell_t* mines = list_cell_create();

  for (unsigned i = 0; i < A->m; ++i) {
    int r = A->e[i][A->n - 1];
    for (unsigned j = 0; j < A->n - 1; ++j) {
      int v = A->e[i][j];
      if ((r == bounds->upper[i] && v > 0) ||
          (r == bounds->lower[i] && v < 0)) {
        list_cell_insert_tail(mines, cfg->covered[j]);
      }
    }
  }

  solution->mines = list_cell_to_array(mines, &solution->nr_mine);
  list_cell_destroy(mines);
}

struct solution*
deduce_solution(const struct configuration* cfg, const struct matrix* A)
{
  struct solution* solution = calloc(1, sizeof(*solution));
  struct bounds* bounds;

  bounds = compute_bounds(A);
  set_empty(cfg, A, bounds, solution);
  set_mines(cfg, A, bounds, solution);
  destroy_bounds(bounds);

  return solution;
}
