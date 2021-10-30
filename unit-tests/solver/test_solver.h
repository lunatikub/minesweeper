/* Warning: has to be included only time in the test suite.
 * No guardians are needed. */

TEST_F(solver, simple)
{
  const static unsigned w = 8;
  const static unsigned h = 8;

  struct grid* solution_grid = minesweeper_grid_new(w, h);
  struct grid* main_grid = minesweeper_grid_new(w, h);

  /* clang-format off */
  static const unsigned init_solution[] = {
    0, 0, 0, 0, 0, 0, 1, 1,
    0, 0, 0, 1, 1, 1, 1, M,
    0, 0, 0, 1, M, 1, 2, 2,
    0, 0, 1, 2, 2, 1, 2, M,
    1, 1, 2, M, 1, 0, 2, M,
    1, M, 3, 3, 2, 1, 1, 1,
    2, 3, M, 2, M, 1, 0, 0,
    1, M, 2, 2, 1, 1, 0, 0,
  };

  static const unsigned init_main[] = {
    0, 0, 0, 0, 0, 0, 1, 9,
    0, 0, 0, 1, 1, 1, 1, 9,
    0, 0, 0, 1, 9, 9, 9, 9,
    0, 0, 1, 2, 9, 9, 9, 9,
    1, 1, 2, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9,
  };
  /* clang-format on */

  CELLS_SET(solution_grid, init_solution);
  CELLS_SET(main_grid, init_main);

  struct solution* solutions = minesweeper_solve(main_grid);
  (void)solutions;

  minesweeper_grid_destroy(main_grid);
  minesweeper_grid_destroy(solution_grid);
  return true;
}
