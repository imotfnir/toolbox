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
    run --separate-stderr -0 _fio_test size=10M thread=2 type=read
    [[ "${output}" == *"_fio_test size=10M thread=2 type=read"* ]]
    [[ "${stderr}" == *"INFO: _fio_test size=10M thread=2 type=read"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _fio_test size=10M thread=2 type=write
    [[ "${output}" == *"_fio_test size=10M thread=2 type=write"* ]]
    [[ "${stderr}" == *"INFO: _fio_test size=10M thread=2 type=write"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_sysbench_test" {
    TEST_DIR="/tmp/stress_test"
    OVERRIDE="true"
    run --separate-stderr -0 _sysbench_test size=10M thread=2 type=seqrewr
    [[ "${output}" == *"_sysbench_test size=10M thread=2 type=seqrewr"* ]]
    [[ "${stderr}" == *"INFO: _sysbench_test size=10M thread=2 type=seqrewr"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _sysbench_test size=10M thread=2 type=rndrw
    [[ "${output}" == *"_sysbench_test size=10M thread=2 type=rndrw"* ]]
    [[ "${stderr}" == *"INFO: _sysbench_test size=10M thread=2 type=rndrw"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}

@test "_dd_test" {
    TEST_DIR="/tmp/stress_test"
    OVERRIDE="true"
    run --separate-stderr -0 _dd_test ddcount=262144 type=read
    [[ "${output}" == *"_dd_test ddcount=262144 type=read"* ]]
    [[ "${stderr}" == *"INFO: _dd_test ddcount=262144 type=read"* ]]
    [[ "${stderr}" != *"ERROR:"* ]]
    OVERRIDE="false"
    run --separate-stderr -1 _dd_test ddcount=262144 type=write
    [[ "${output}" == *"_dd_test ddcount=262144 type=write"* ]]
    [[ "${stderr}" == *"INFO: _dd_test ddcount=262144 type=write"* ]]
    [[ "${stderr}" == *"ERROR: Fail to run stress test"* ]]
}
