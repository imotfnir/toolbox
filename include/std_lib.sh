#!/bin/bash

if [ -n "${__STD_LIB_SH+_    }" ]; then
    return
else
    readonly __STD_LIB_SH=1
fi

# shellcheck source-path=include
source "${INCLUDE_DIR}/error_handling_lib.sh"

get_cpu_model() {
    local model

    if model=$(lscpu | grep "Model name" | awk -F ": *" '{print $2}'); then
        echo "${model}"
        return 0
    else
        echo "unknown"
        debug_print 2 "Unknown CPU model"
        return 1
    fi
}

get_root_ssd() {
    local ssd
    if ssd=$(mount | grep "on / type" | awk '{printf $1}'); then
        debug_print 1 "Can not detect main sdd"
        return 1
    fi
    echo "${ssd}"
    return 0
}

popup_message() {
    echo "==============================================================="
    echo "    $*"
    echo "==============================================================="
}
