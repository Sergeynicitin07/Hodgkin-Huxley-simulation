#!/bin/bash

METHOD=${1:-dp}
CALC=${2:-2}

if [ "$CALC" -eq 2 ]; then

    GNA=${3:-120}
    GK=${4:-36}
    GL=${5:-0.3}
    VNA=${6:--115}
    VK=${7:-12}
    VL=${8:--10.613}
    SN=${9:-1}
    SM=${10:-1}
    SH=${11:-1}

    echo "Inverse problem mode"
    echo "gNa = $GNA | gK = $GK | gL = $GL"
    echo "VNa = $VNA | VK = $VK | VL = $VL"
    echo "sn = $SN | sm = $SM | sh = $SH"

    ./hh_sim "$CALC" \
        "$GNA" "$GK" "$GL" \
        "$VNA" "$VK" "$VL" \
        "$SN" "$SM" "$SH" > fit.txt

    echo "Data saved → fit.txt"
    echo "Experimental data saved → experiment.txt"

elif [ "$CALC" -eq 1 ]; then

    IEXT=${3:-10}
    TEND=${4:-10.0}
    H=${5:-0.1}
    TOL=${6:-1e-1}
    AS=${7:-1e-10}

    echo "Calculus mode"

    echo "method = $METHOD | h = $H | Iext = $IEXT | t_end = $TEND | tol = $TOL | tol_for_dp = $AS"

    ./hh_sim "$CALC" "$METHOD" "$IEXT" "$TEND" "$H" "$TOL" "$AS"

else

    IEXT=${3:-10}
    TEND=${4:-10.0}
    H=${5:-0.1}
    TOL=${6:-1e-1}
    AS=${7:-1e-10}

    echo "Normal mode"

    echo "method = $METHOD | h = $H | Iext = $IEXT | t_end = $TEND | tol = $TOL | tol_for_dp = $AS"

    ./hh_sim "$CALC" "$METHOD" "$IEXT" "$TEND" "$H" "$TOL" "$AS" > "${METHOD}.txt"

    echo "Data saved → ${METHOD}.txt"

fi
