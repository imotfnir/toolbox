#!/usr/bin/env bats
bats_require_minimum_version 1.5.0

load "${SOURCE_DIR}/stress_lib.sh"

DEBUG=6
RUN_COMMAND="./ssd_stress_tool.sh"

@test "Main" {
    run --separate-stderr -0 ${RUN_COMMAND}
    [[ "${output}" == *"Usage : ssd_stress_tool.sh"* ]]
    run --separate-stderr -1 ${RUN_COMMAND} --mode a
    [ "${output}" = "" ]
    [ "${stderr}" = "Invalid arguments. See ./ssd_stress_tool.sh --help" ]
    run --separate-stderr -127 ${RUN_COMMAND} --mode p
    [ "${output}" = "" ]
    [ "${stderr}" = "WARNING: Please specify at least one type of test" ]
}
