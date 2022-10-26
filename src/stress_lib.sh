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
    if [ "${CYCLE}" -lt "0" ]; then
        debug_print 2 "Test cycle can not less than 0"
        return 1
    fi

    ${TEST_MEMORY_READ} && return 0
    ${TEST_MEMORY_WRITE} && return 0
    ${TEST_STORAGE_READ} && return 0
    ${TEST_STORAGE_WRITE} && return 0
    ${TEST_CPU_READ} && return 0
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

_fio_test() {
    local size="${1}"
    local thread="${2}"
    local type="${3}"
    local cmd

    trap 'command rm -rf ${TEST_DIR}/*' RETURN
    cmd="fio -directory=${TEST_DIR} -direct=1 -iodepth=128 -thread -rw=${type} -filesize=${size} -ioengine=libaio -bs=4k -numjobs=${thread} -refill_buffers -group_reporting -name=fio_test"
    popup_message "fio ${type} test"
    debug_print 3 "fio ${type} test"
    debug_print 4 "${cmd}"

    if ! eval "${cmd}"; then
        debug_print 1 "Fail to run fio test"
        return 1
    fi

    return 0
}

_sysbench_test() {
    local size="${1}"
    local thread="${2}"
    local type="${3}"
    local cmd

    trap 'command rm -rf ${TEST_DIR}/*' RETURN
    cmd="sysbench --test=fileio --num-threads=${thread} --file-total-size=${size} --file-io-mode=sync --file-test-mode=${type}"
    popup_message "sysbench ${type} test"
    debug_print 3 "sysbench ${type} test"
    debug_print 4 "${cmd}"

    cd "${TEST_DIR}" || return 1
    if ! eval "${cmd} prepare"; then
        debug_print 1 "Fail to run sysbench test"
        return 1
    fi
    if ! eval "${cmd} run"; then
        debug_print 1 "Fail to run sysbench test"
        return 1
    fi
    if ! eval "${cmd} cleanup"; then
        debug_print 1 "Fail to run sysbench test"
        return 1
    fi

    return 0
}

_dd_test() {
    local ddcount="${1}"
    local type="${2}"
    local cmd

    trap 'command rm -rf ${TEST_DIR}/*' RETURN
    case "${type}" in
    read)
        cmd="dd if=/dev/random of=${TEST_DIR}/tempfile bs=4K count=${ddcount} conv=fdatasync,notrunc"
        ;;
    write)
        cmd="dd if=${TEST_DIR}/tempfile of=/dev/null bs=4K count=${ddcount}"
        ;;
    esac

    popup_message "dd ${type} test"
    debug_print 3 "dd ${type} test"
    debug_print 4 "${cmd}"

    if ! eval "${cmd} cleanup"; then
        debug_print 1 "Fail to run dd test"
        return 1
    fi

    return 0
}

_test_list() {
    #TODO:
    return 0
}

stress_test() {
    debug_print 3 "Test begin"
    if "${IS_CYCLE_FOREVER}"; then
        while true; do
            _test_list
        done
        return 0
    fi

    local _
    for _ in $(seq 1 "${CYCLE}"); do
        _test_list
    done

    return 0
}
