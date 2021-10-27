test_name='test-solver'

test_solver_src = files(
  'test_adjacent_mine.c',
)

test_solver = executable(
  test_name,
  '../test.c',
  test_solver_src,
  solver_src,
  include_directories: [
    inc,
    test_inc,
    solver_inc,
  ],
  c_args: flags,
)

test('test-solver', test_solver)
