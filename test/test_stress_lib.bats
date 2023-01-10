#!/usr/bin/env bats
bats_require_minimum_version 1.5.0

load "${INCLUDE_DIR}/stress_lib.sh"

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
    run --separate-stderr -0 _fio_test size=10M thread=2 type=read cmd="true"
    [[ "${output}" == *"fio size=10M thread=2 type=read"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    run --separate-stderr -1 _fio_test size=10M thread=2 type=write cmd="false"
    [[ "${output}" == *"fio size=10M thread=2 type=write"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_sysbench_test" {
    TEST_DIR="/tmp/stress_test"
    run --separate-stderr -0 _sysbench_test size=10M thread=2 type=seqrewr cmd="true"
    [[ "${output}" == *"sysbench size=10M thread=2 type=seqrewr"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    run --separate-stderr -1 _sysbench_test size=10M thread=2 type=rndrw cmd="false"
    [[ "${output}" == *"sysbench size=10M thread=2 type=rndrw"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_dd_test" {
    TEST_DIR="/tmp/stress_test"
    run --separate-stderr -0 _dd_test size=10M thread=2 type=read cmd="true"
    [[ "${output}" == *"dd size=10M thread=2 type=read"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    run --separate-stderr -1 _dd_test size=10M thread=2 type=write cmd="false"
    [[ "${output}" == *"dd size=10M thread=2 type=write"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_single_test" {
    TEST_DIR="/tmp/stress_test"

    run --separate-stderr -0 _single_test tool=fio size=1024M thread=8 type=read cmd="true"
    [[ "${output}" == *"tool=fio size=1024M thread=8 type=read"* ]]
    [[ "${stderr}" == *"tool=fio size=1024M thread=8 type=read"* ]]
    run --separate-stderr -0 _single_test tool=dd size=1024M thread=16 type=write cmd="true"
    [[ "${output}" == *"tool=dd size=1024M thread=16 type=write"* ]]
    [[ "${stderr}" == *"tool=dd size=1024M thread=16 type=write"* ]]
    run --separate-stderr -1 _single_test tool=dd size=1024M thread=16 type=write cmd="false"
    [[ "${output}" == *"tool=dd size=1024M thread=16 type=write"* ]]
    [[ "${stderr}" == *"tool=dd size=1024M thread=16 type=write"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}
