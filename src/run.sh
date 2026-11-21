#!/bin/bash
set -o pipefail

CALC=${1:-2}

if [ "$CALC" -eq 2 ]; then
    : > rk4.txt
    ./hh_sim 2 "${@:2}" | awk '
        /^[[:space:]]*[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?[[:space:]]+[-+]?[0-9]/ {
            print > "rk4.txt"
            next
        }
        { print; fflush() }
    '
elif [ "$CALC" -eq 1 ]; then
    ./hh_sim 1 "${2:-dp}" "${3:-10}" "${4:-10.0}" "${5:-0.1}" "${6:-1e-1}" "${7:-1e-10}"
else
    METHOD=${2:-dp}
    ./hh_sim 0 "$METHOD" "${3:-10}" "${4:-10.0}" "${5:-0.1}" "${6:-1e-1}" "${7:-1e-10}" > "${METHOD}.txt"
fi
