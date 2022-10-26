#!/usr/bin/env bash

if [ -n "${__STRESS_LIB_SH+_}" ]; then
    return
else
    readonly __STRESS_LIB_SH=1
fi

# shellcheck source-path=src
source "${SOURCE_DIR}/std_lib.sh"
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

init_and_check_current_environment() {
    local cpu_model
    local product_name
    local log_file

    #TODO: product name
    #TODO: ssd fw, sn etc
    cpu_model=$(get_cpu_model)
    product_name=$(dmidecode -t 1 | grep "Product Name" | awk -F " " '{printf $3}')
    log_file="ssd_stress_test_${product_name}_${cpu_model}_$(date "+%Y%m%d_+%H%M%S").log"

    #  shellcheck disable=SC2034
    CPU_MODEL="${cpu_model}"
    #  shellcheck disable=SC2034
    LOG_FILE="${log_file}"
    return 0
}
