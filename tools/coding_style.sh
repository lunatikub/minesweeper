#!/bin/bash

SCRIPT_DIR=$(dirname $(readlink -f $0))
ROOT_DIR=${SCRIPT_DIR}/..

CLANG_FMT=$(which clang-format-10)
[ $? -ne 0 ] && exit 1

# Directories of the sources to check
src_list=(
    src
    include
    unit-tests
)

ret=0
for dir in ${src_list[@]}
do
    for file in $(find ${ROOT_DIR}/${dir} -regex ".*\.[c|h]")
    do
        echo " - apply coding-style: $file"
        ${CLANG_FMT} -style=Mozilla -i $file
    done
done

exit 0
