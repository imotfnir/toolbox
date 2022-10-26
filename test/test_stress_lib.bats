#!/usr/bin/env bats
bats_require_minimum_version 1.5.0

load "${SOURCE_DIR}/stress_lib.sh"

@test "is_argument_valid" {
    CYCLE=1
    TEST_MEMORY_READ="false"
    TEST_MEMORY_WRITE="false"
    TEST_STORAGE_READ="false"
    TEST_STORAGE_WRITE="true"
    run --separate-stderr -0 is_argument_valid
    [ "${output}" = "" ]
    TEST_STORAGE_WRITE="false"
    run --separate-stderr -1 is_argument_valid
    [ "${output}" = "" ]
    CYCLE=0
    run --separate-stderr -1 is_argument_valid
    [ "${output}" = "" ]
}
