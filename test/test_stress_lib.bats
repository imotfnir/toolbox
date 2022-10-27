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
    [[ "${stderr}" != *"ERROR:"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _fio_test 10M 2 write
    [[ "${output}" == *"fio write test"* ]]
    [[ "${stderr}" == *"INFO: fio write test"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_sysbench_test" {
    TEST_DIR="/tmp/stress_test"
    OVERRIDE="true"
    run --separate-stderr -0 _sysbench_test 10M 2 seqrewr
    [[ "${output}" == *"sysbench seqrewr test"* ]]
    [[ "${stderr}" == *"INFO: sysbench seqrewr test"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _sysbench_test 10M 2 rndrw
    [[ "${output}" == *"sysbench rndrw test"* ]]
    [[ "${stderr}" == *"INFO: sysbench rndrw test"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_dd_test" {
    TEST_DIR="/tmp/stress_test"
    OVERRIDE="true"
    run --separate-stderr -0 _dd_test 262144 read
    [[ "${output}" == *"dd read test"* ]]
    [[ "${stderr}" == *"INFO: dd read test"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _dd_test 262144 write
    [[ "${output}" == *"dd write test"* ]]
    [[ "${stderr}" == *"INFO: dd write test"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}
