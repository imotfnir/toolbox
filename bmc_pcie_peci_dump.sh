#!/bin/bash

bus=0
dev=0
fun=0
while [ "${bus}" -lt 256 ]; do
    while [ "${dev}" -lt 32 ]; do
        while [ "${fun}" -lt 8 ]; do
            value=$(peciapp RdPCIConfig "${bus}" "${dev}" "${fun}" 0 | awk '{ print $2 }')
            if [ "$((value))" != "0" ]; then
                echo "B:${bus} D:${dev} F:${fun} = ${value}"
            fi
            fun=$((fun + 1))
        done
        dev=$((dev + 1))
        fun=0
    done
    bus=$((bus + 1))
    dev=0
    fun=0
done
