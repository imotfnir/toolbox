#!/usr/bin/env bats
bats_require_minimum_version 1.5.0

load "${SOURCE_DIR}/stress_lib.sh"

DEBUG=6

@test "is_argument_valid" {
    CYCLE=1
    TEST_MEMORY_READ="false"
    TEST_MEMORY_WRITE="false"
    TEST_STORAGE_READ="false"
    TEST_STORAGE_WRITE="true"
    TEST_CPU_READ="false"
    run --separate-stderr -0 is_argument_valid
    [ "${output}" = "" ]
    TEST_STORAGE_WRITE="false"
    run --separate-stderr -1 is_argument_valid
    [ "${output}" = "" ]
    [ "${stderr}" = "WARNING: Please specify at least one type of test" ]
    CYCLE=-2
    run --separate-stderr -1 is_argument_valid
    [ "${output}" = "" ]
    [ "${stderr}" = "WARNING: Test cycle can not less than 0" ]
}

@test "_fio_test" {
    TEST_DIR="/tmp/stress_test"
    OVERRIDE="true"
    run --separate-stderr -0 _fio_test 10M 2 read
    [[ "${output}" == *"fio read test"* ]]
    [[ "${stderr}" == *"INFO: fio read test"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _fio_test 10M 2 write
    [[ "${output}" == *"fio write test"* ]]
    [[ "${stderr}" == *"INFO: fio write test"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}
