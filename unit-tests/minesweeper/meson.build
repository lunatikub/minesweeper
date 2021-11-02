test_name='test-minesweeper'

test_minesweeper_src = files(
  'test_minesweeper.c',
)

test_minesweeper = executable(
  test_name,
  '../utest.c',
  test_minesweeper_src,
  minesweeper_src,
  include_directories: [
    inc,
    unit_test_inc,
    minesweeper_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
)

test(test_name, test_minesweeper)
