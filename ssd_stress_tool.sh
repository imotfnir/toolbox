#!/bin/bash

DEBUG=6
VERSION="0.1.0"
ROOT_DIR=$(
    cd "$(dirname "${0}")" || exit
    echo "${PWD}"
)
SOURCE_DIR="${ROOT_DIR}/src"
TEST_DIR="${ROOT_DIR}/test"
export ROOT_DIR
export SOURCE_DIR
export TEST_DIR

# Global Variable
TEST_MEMORY_READ="false"
TEST_MEMORY_WRITE="false"
TEST_STORAGE_READ="false"
TEST_STORAGE_WRITE="false"
TEST_CPU_READ="false"
CYCLE="10"
IS_CYCLE_FOREVER="false"
TEST_MODE="stress"

# shellcheck source-path=src
source "${SOURCE_DIR}/error_handling_lib.sh"
# shellcheck source-path=src
source "${SOURCE_DIR}/stress_lib.sh"

#TODO: trap EXIT, run show_error before exit

if [ "${#}" = 0 ]; then
    show_help
    exit 0
fi

for i in $(seq 1 "${#}"); do
    if [ "${!i}" = "-d" ] || [ "${!i}" = "--debug" ]; then
        i=$((i + 1))
        if [ $(("${!i}")) != "${!i}" ]; then
            show_error 1
            exit 1
        fi
        DEBUG="${!i}"
        color_print green "DEBUG ENABLE"
        break
    fi
done

if [ $(("${DEBUG}")) -ge 255 ]; then
    set -x
fi

# Handle option
while [ ${#} -gt 0 ]; do
    case "${1}" in
    -d | --debug)
        shift 2
        ;;
    -v | --version)
        show_version
        exit 0
        ;;
    -h | --help)
        show_help
        exit 0
        ;;
    -c | --cycle)
        if [ ${#} -lt 2 ]; then
            show_error 1
            exit 1
        fi
        if [ "${2}" -eq "0" ]; then
            IS_CYCLE_FOREVER="true"
        fi
        CYCLE="${2}"
        shift 2
        ;;
    -m | --memory)
        if [ ${#} -lt 2 ]; then
            show_error 1
            exit 1
        fi
        case "${2}" in
        r)
            TEST_MEMORY_READ="true"
            ;;
        w)
            TEST_MEMORY_WRITE="true"
            ;;
        rw)
            TEST_MEMORY_READ="true"
            TEST_MEMORY_WRITE="true"
            ;;
        *)
            show_error 1
            ;;
        esac
        shift 2
        ;;
    -s | --storage)
        if [ ${#} -lt 2 ]; then
            show_error 1
            exit 1
        fi
        case "${2}" in
        r)
            TEST_STORAGE_READ="true"
            ;;
        w)
            TEST_STORAGE_WRITE="true"
            ;;
        rw)
            TEST_STORAGE_READ="true"
            TEST_STORAGE_WRITE="true"
            ;;
        *)
            show_error 1
            ;;
        esac
        shift 2
        ;;
    --cpu)
        TEST_CPU_READ="true"
        shift 1
        ;;
    --all)
        TEST_MEMORY_READ="true"
        TEST_MEMORY_WRITE="true"
        TEST_STORAGE_READ="true"
        TEST_STORAGE_WRITE="true"
        TEST_CPU_READ="true"
        shift 1
        ;;
    --mode)
        if [ ${#} -lt 2 ]; then
            show_error 1
            exit 1
        fi
        case "${2}" in
        s | stress)
            TEST_MODE="stress"
            ;;
        p | performance)
            TEST_MODE="performance"
            ;;
        *)
            show_error 1
            exit 1
            ;;
        esac
        shift 2
        ;;
    *)
        show_error 1
        exit 1
        ;;
    esac
done

#!Main function
is_argument_valid || exit 1
run_test "$@" || exit 1

#TODO; trap INT and EXIT to gene rate test report
exit 0
