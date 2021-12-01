#!/bin/bash

SCRIPT_DIR=$(dirname $(readlink -f $0))
ROOT_DIR=${SCRIPT_DIR}/..

MODULE=$1

[ ! "$MODULE" ] && exit 1

mkdir -p $ROOT_DIR/src/$MODULE
mkdir -p $ROOT_DIR/unit-tests/$MODULE

###
### unit-tests/module/meson.build
###

cat << EOF > $ROOT_DIR/unit-tests/$MODULE/meson.build
test_name='test-${MODULE}'

test_${MODULE}_src = files(
  'test_${MODULE}.c',
)

test_${MODULE} = executable(
  test_name,
  '../utest.c',
  test_${MODULE}_src,
  ${MODULE}_src,
  minesweeper_src,
  include_directories: [
    inc,
    unit_test_inc,
    ${MODULE}_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
)

test(test_name, test_${MODULE})
EOF

###
### unit-tests/module/test_<module>.c
###

cat << EOF > $ROOT_DIR/unit-tests/${MODULE}/test_${MODULE}.c
#include "common.h"
#include "utest.h"
#include <${MODULE}.h>

/** List of sub-section tests **/
// #include "test_1.h"
// #include "test_2.h"

const static struct test ${MODULE}_tests[] = {
      // TEST(sub-module, test_name_1),
      // TEST(sub-module, test_name_2),
};

TEST_SUITE(${MODULE});
EOF

###
### src/<module>/meson.build
###

cat << EOF > $ROOT_DIR/src/${MODULE}/meson.build
${MODULE}_src = files(
  '${MODULE}.c',
)

${MODULE}_inc = include_directories('.')
EOF

###
### src/<module>/module.c
###

cat << EOF > $ROOT_DIR/src/${MODULE}/${MODULE}.c
#include <${MODULE}.h>
EOF

###
### include/<module>.h
###

cat << EOF > $ROOT_DIR/include/${MODULE}.h
#ifndef __${MODULE^^}_H__
#define __${MODULE^^}_H__

#endif /* !__${MODULE^^}_H__ */
EOF

exit 0
