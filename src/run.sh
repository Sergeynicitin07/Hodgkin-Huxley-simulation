#!/bin/bash
METHOD=${1:-dp}
H=${2:-0.1}
IEXT=${3:-10}
CALC=${4:-0}
TEND=${5:-10.0}
HK=${6:-0.01}
AS=${7:-1e-10}

if [ $CALC -eq 1 ]; then
    echo "Calculus mode
    echo "method=$METHOD | h=$H | Iext=$IEXT | t_end=$TEND | tol=$AS | hk=$HK"
    ./hh_sim "$METHOD" "$H" "$IEXT" 1 "$TEND" "$HK" "$AS"
else
    echo "Normal mode"
    echo "method=$METHOD | h=$H | Iext=$IEXT | t_end=$TEND"
    ./hh_sim "$METHOD" "$H" "$IEXT" 0 "$TEND" "$HK" "$AS" > "${METHOD}.dat"
    echo "Saved → ${METHOD}.dat"
fi
