test_name='test-solver'

test_solver_src = files(
  'test_solver.c',
)

test_solver = executable(
  test_name,
  '../utest.c',
  test_solver_src,
  matrix_src,
  solver_src,
  minesweeper_src,
  include_directories: [
    inc,
    unit_test_inc,
    solver_inc,
    matrix_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
)

test(test_name, test_solver)
