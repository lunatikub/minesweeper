#!/bin/bash

SCRIPT_DIR=$(dirname $(readlink -f $0))
ROOT_DIR=${SCRIPT_DIR}/..

MODULE=$1

[ ! "$MODULE" ] && exit 1

mkdir -p $ROOT_DIR/src/$MODULE
mkdir -p $ROOT_DIR/unit-tests/$MODULE

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

cat << EOF > $ROOT_DIR/unit-tests/${MODULE}/test_${MODULE}.c
#include "common.h"
#include "${MODULE}_unit-test.h"
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

cat << EOF > $ROOT_DIR/src/${MODULE}/meson.build
${MODULE}_src = files(
)

${MODULE}_inc = include_directories('.')
EOF

cat << EOF > $ROOT_DIR/src/${MODULE}/${MODULE}_unit-test.h
#ifndef __${MODULE}_UNIT_TEST_H__
#define __${MODULE}_UNIT_TEST_H__

#include <unit-test.h>

/**
 * This file defines all prototypes needed for the unit-tests
 * of this ${MODULE} module.
 */

// PROTOTYPE_FOR_UNIT_TEST(proto_1);
// PROTOTYPE_FOR_UNIT_TEST(proto_2);

#endif /* !__${MODULE}_UNIT_TEST_H__ */
EOF

exit 0
