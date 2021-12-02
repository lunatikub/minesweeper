#include <stdlib.h>

#include <debug.h>
#include <matrix/matrix.h>
#include <minesweeper/grid.h>
#include <minesweeper/neighbors.h>
#include <solver/solver.h>

#include "configuration.h"
#include "solution.h"

#define MODULE "solver"

struct solution*
solve(const struct grid* grid)
{
  DBG_GRID(grid, "main");

  struct grid* adjacents = grid_create(grid->width, grid->height);
  grid_adjacents(grid, adjacents);
  DBG_GRID(adjacents, "adjacents");

  struct configuration* cfg = configuration_create(grid);
  if (cfg == NULL) {
    grid_destroy(adjacents);
    return NULL;
  }
  DBG_CFG(cfg);

  struct matrix* A = configuration_map(cfg, grid, adjacents);
  DBG_MATRIX(A, "mapped from configuration");

  matrix_gauss_jordan(A);
  DBG_MATRIX(A, "row reduced echelon form");

  struct solution* solution = solution_deduce(cfg, A);
  DBG_SOLUTION(solution);

  matrix_destroy(A);
  grid_destroy(adjacents);
  configuration_destroy(cfg);

  return solution;
}
