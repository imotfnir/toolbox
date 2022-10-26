#!/usr/bin/env bash

if [ -n "${__STRESS_LIB_SH+_}" ]; then
    return
else
    readonly __STRESS_LIB_SH=1
fi

# shellcheck source-path=src
source "${SOURCE_DIR}/error_handling_lib.sh"

is_argument_valid() {
    if [ "${CYCLE}" -le "0" ]; then
        debug_print 2 "Test cycle can not less than of equal to 0"
        return 1
    fi

    ${TEST_MEMORY_READ} && return 0
    ${TEST_MEMORY_WRITE} && return 0
    ${TEST_STORAGE_READ} && return 0
    ${TEST_STORAGE_WRITE} && return 0
    debug_print 2 "Please specify at least one type of test"
    return 1
}
