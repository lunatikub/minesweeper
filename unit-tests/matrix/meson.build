test_name='test-matrix'

test_matrix_src = files(
  'test_matrix.c',
)

test_matrix = executable(
  test_name,
  '../utest.c',
  test_matrix_src,
  matrix_src,
  minesweeper_src,
  include_directories: [
    inc,
    unit_test_inc,
    matrix_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
)

test(test_name, test_matrix)
