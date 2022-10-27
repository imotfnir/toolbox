#!/usr/bin/env bash

if [ -n "${__ERROR_HANDLING_LIB_SH+_}" ]; then
    return
else
    readonly __ERROR_HANDLING_LIB_SH=1
fi
##############################
# Show usage for this tool
# GLOBALS:
#    none
# ARGUMENTS:
#    none
# OUTPUTS:
#    none
# RETURN:
#    none
##############################
show_help() {
    cat <<EOF
Usage : $(basename "${0}") [-hv]  [-c <Integer>] [-m <Memory test type>] [-s <Storage test type>]

General Option:
    -v, --version
        Display version information and exit
    -h, --help
        Display this help text and exit
    -d, --debug
        Enable debug mode
    --mode [s|stress|p|performance]
        stress:      No report
        performance: Generate test report
    -c, --cycle <integer>
        Repeat the test

Performance mode option:
    -m, --memory <type>
        Memory test type, [r|w|rw]
    -s, --storage <type>
        Storage test type, [r|w|rw]
    --cpu
        Enable CPU stress test
    --all
        Memory and storage read/write test

Example:
    $(basename "${0}") -d -c 3 -m r -s rw

EOF
}

##############################
# Show version for this tool
# GLOBALS:
#    VERSION
# ARGUMENTS:
#    none
# OUTPUTS:
#    none
# RETURN:
#    none
##############################
show_version() {
    echo "$(basename "${0}") version v${VERSION}"
    return 0
}

##############################
# Show error for some return code
# GLOBALS:
#    none
# ARGUMENTS:
#    exit code
# OUTPUTS:
#    error message
# RETURN:
#    none
##############################
show_error() {
    local exit_code="${1}"

    case "${exit_code}" in
    0)
        :
        ;;
    1)
        error_print "Invalid arguments. See ./$(basename "${0}") --help"
        ;;
    *)
        error_print "undefine error"
        ;;
    esac
}

##############################
# Show message if debug mode enable
# GLOBALS:
#    DEBUG
# ARGUMENTS:
#    Debug level
#        0: Fatal
#        1: Error
#        2: Warning
#        3: Info
#        4: Debug
#        5: Trace
#        6: All
#    Message
# OUTPUTS:
#    Message
# RETURN:
#    none
##############################
debug_print() {
    local debug_level="${1}"
    shift

    if [ $(("${DEBUG}")) -lt $(("${debug_level}")) ]; then
        return 0
    fi

    case "${debug_level}" in
    0)
        error_print "FATAL: ${*}"
        ;;
    1)
        error_print "ERROR: ${*}"
        ;;
    2)
        error_print "WARNING: ${*}"
        ;;
    3)
        error_print "INFO: ${*}"
        ;;
    4)
        error_print "DEBUG: ${*}"
        ;;
    5)
        error_print "TRACE: ${*}"
        ;;
    esac

    return 0
}

##############################
# Redirect message to stderr
# GLOBALS:
#    none
# ARGUMENTS:
#    Message
# OUTPUTS:
#    Message
# RETURN:
#    none
##############################
error_print() {
    echo >&2 "$*"
}

##############################
# Show message in color test mode
# GLOBALS:
#    none
# ARGUMENTS:
#    Color
#    Message
# OUTPUTS:
#    Message with color
# RETURN:
#    none
##############################
color_print() {
    _set_color_to "${1}"
    shift 1
    command printf %b\\n "$*" 2>/dev/null
    _set_color_to empty
}

##############################
# Set color form the next stdin
# GLOBALS:
#    none
# ARGUMENTS:
#    Color
# OUTPUTS:
#    none
# RETURN:
#    none
##############################
_set_color_to() {
    color="${1}"

    # Color code
    # BLACK="30"
    RED="31"
    GREEN="32"
    YELLOW="33"
    # BLUE="34"
    # MAGENTA="35"
    # CYAN="36"
    # LIGHTGRAY="37"
    # GRAY="90"
    # Fonts code
    NORMAL="0"
    BOLD="1"
    ITALICS="3"
    # UNDERLINE="4"

    END_COLOR="\e[0m"

    case "${color}" in
    red) printf "\e[%b;%bm" "${NORMAL}" "${RED}" ;;
    green) printf "\e[%b;%bm" "${NORMAL}" "${GREEN}" ;;
    yellow) printf "\e[%b;%bm" "${NORMAL}" "${YELLOW}" ;;
    bold_red) printf "\e[%b;%bm" "${BOLD}" "${RED}" ;;
    bold_green) printf "\e[%b;%bm" "${BOLD}" "${GREEN}" ;;
    italics_red) printf "\e[%b;%bm" "${ITALICS}" "${RED}" ;;
    italics_green) printf "\e[%b;%bm" "${ITALICS}" "${GREEN}" ;;
    empty) printf "%b" "${END_COLOR}" ;;
    esac
}

##############################
# Print message in stderr with color
# GLOBALS:
#    none
# ARGUMENTS:
#    Message
# OUTPUTS:
#    Message with color
# RETURN:
#    none
##############################
color_error_print() {
    color_print >&2 "$@"
}
