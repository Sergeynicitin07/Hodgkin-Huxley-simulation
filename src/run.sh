#!/bin/bash
METHOD=${1:-dp}
H=${2:-0.1}
IEXT=${3:-10}
CALC=${4:-0}
TEND=${5:-10.0}
HK=${6:-0.01}
AS=${7:-1e-10}

IEXT_NEG=$(( -IEXT ))

if [ $CALC -eq 1 ]; then
    echo "Calculus mode | method=$METHOD | tol=$AS | hk=$HK | Iext=$IEXT | t_end=$TEND"
    ./hh_sim "$METHOD" "$H" "$IEXT_NEG" 1 "$TEND" "$HK" "$AS"
else
    echo "Normal mode | method=$METHOD | h=$H | Iext=$IEXT | t_end=$TEND"
    ./hh_sim "$METHOD" "$H" "$IEXT_NEG" 0 "$TEND" "$HK" "$AS" > "${METHOD}.dat"
    echo "Data saved → ${METHOD}.dat"
fi
