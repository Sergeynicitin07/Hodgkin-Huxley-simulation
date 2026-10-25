#!/bin/bash

set -o pipefail

CALC=${1:-2}

if [ "$CALC" -eq 2 ]; then

    C=${2:-53.5}
    GNA=${3:-78}
    GK=${4:-2.85}
    GL=${5:-2.4}

    VNA=${6:--118}
    VK=${7:-13}
    VL=${8:--10.613}

    SN=${9:-0.006}
    SM=${10:-1.2}
    SH=${11:-0.21}

    echo "Inverse problem mode"
    echo "Initial c=$C"
    echo "gNa=$GNA gK=$GK gL=$GL"
    echo "VNa=$VNA VK=$VK VL=$VL"
    echo "sn=$SN sm=$SM sh=$SH"

    : > rk4.txt

    ./hh_sim 2 \
        "$C" \
        "$GNA" \
        "$GK" \
        "$GL" \
        "$VNA" \
        "$VK" \
        "$VL" \
        "$SN" \
        "$SM" \
        "$SH" | awk '
        /^Sum of Squared Errors:/ || /^Sum of new Squared Errors:/ {
            print
            fflush()
            next
        }
        /^[[:space:]]*[-+0-9.]/ {
            print > "rk4.txt"
            next
        }
        {
            print
        }
    '

    echo "Data saved -> rk4.txt"
    echo "Experimental data -> experiment.txt"

elif [ "$CALC" -eq 1 ]; then

    METHOD=${2:-dp}
    IEXT=${3:-10}
    TEND=${4:-10.0}
    H=${5:-0.1}
    TOL=${6:-1e-1}
    AS=${7:-1e-10}

    echo "Calculus mode"
    echo "method=$METHOD h=$H Iext=$IEXT t_end=$TEND tol=$TOL tol_for_dp=$AS"

    ./hh_sim 1 \
        "$METHOD" \
        "$IEXT" \
        "$TEND" \
        "$H" \
        "$TOL" \
        "$AS"

else

    METHOD=${2:-dp}
    IEXT=${3:-10}
    TEND=${4:-10.0}
    H=${5:-0.1}
    TOL=${6:-1e-1}
    AS=${7:-1e-10}

    echo "Normal mode"
    echo "method=$METHOD h=$H Iext=$IEXT t_end=$TEND tol=$TOL tol_for_dp=$AS"

    ./hh_sim 0 \
        "$METHOD" \
        "$IEXT" \
        "$TEND" \
        "$H" \
        "$TOL" \
        "$AS" > "${METHOD}.txt"

    echo "Data saved -> ${METHOD}.txt"

fi
