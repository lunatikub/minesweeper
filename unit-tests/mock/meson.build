test_name='test-mock'

test_mock_src = files(
  'test_mock.c',
)

test_mock = executable(
  test_name,
  '../utest.c',
  test_mock_src,
  mock_src,
  minesweeper_src,
  include_directories: [
    inc,
    unit_test_inc,
    mock_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
)

test(test_name, test_mock)
