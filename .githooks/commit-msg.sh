#!/bin/bash
echo "Runing $(basename "${0}")"

# This is .git/COMMIT_EDITMSG
INPUT_FILE="${1}"
# Commit type define in this repo
type_list="build chore ci docs feat fix perf refactor revert style test merge"

is_commit_validated() {
    local input_file=$*
    local first_line
    local item=""
    first_line=$(head -n 1 "${input_file}")
    for item in ${type_list}; do
        if echo "${first_line}" | grep -o "^${item}" >/dev/null; then
            echo "Commit type is ${item}"
            return 0
        fi
    done
    return 1
}

if ! is_commit_validated "${INPUT_FILE}"; then
    cat <<EOF
Commit message type not found
The commit message should be structured as follows

    <type>[optional scope]: <description>

    [optional body]

    [optional footer(s)]

Commit type define in this repo: "${type_list}"
EOF
    exit 1
fi

# This example catches duplicate Signed-off-by lines.
test "" = "$(grep '^Signed-off-by: ' "$1" |
    sort | uniq -c | sed -e '/^[ 	]*1[ 	]/d')" || {
    echo >&2 Duplicate Signed-off-by lines.
    exit 1
}
