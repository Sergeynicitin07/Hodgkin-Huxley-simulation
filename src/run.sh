#!/bin/bash

CALC=${1:-2}

if [ "$CALC" -eq 2 ]; then

    GNA=${2:-120}
    GK=${3:-36}
    GL=${4:-0.3}

    VNA=${5:--115}
    VK=${6:-12}
    VL=${7:--10.613}

    SN=${8:-1}
    SM=${9:-1}
    SH=${10:-1}

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
