#!/bin/bash

CALC=${1:-2}

if [ "$CALC" -eq 2 ]; then

    GNA=${2:-78}
    GK=${3:-2.85}
    GL=${4:-2.4}

    VNA=${5:--118}
    VK=${6:-13}
    VL=${7:--10.613}

    SN=${8:-0.006}
    SM=${9:-1.2}
    SH=${10:-0.21}

    echo "Inverse problem mode"
    echo "gNa=$GNA gK=$GK gL=$GL"
    echo "VNa=$VNA VK=$VK VL=$VL"
    echo "sn=$SN sm=$SM sh=$SH"

    ./hh_sim 2 \
        "$GNA" \
        "$GK" \
        "$GL" \
        "$VNA" \
        "$VK" \
        "$VL" \
        "$SN" \
        "$SM" \
        "$SH" > rk4.txt

    echo "Data saved -> rk4.txt"
    echo "Experimental data saved -> experiment.txt"

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
