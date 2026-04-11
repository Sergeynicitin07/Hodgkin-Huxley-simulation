#!/bin/bash
METHOD=${1:-dp}
H=${2:-0.01}
IEXT=${3:-10}          # WE WRITE POSITIVE
TOL=${4:-1e-10}
HK=${5:-0.01}
CALC=${6:-0}

IEXT_NEG=$(( -IEXT ))

if [ $CALC -eq 1 ]; then
    echo "Calculus mode"
    ./hh_sim "$METHOD" "$H" "$IEXT_NEG" 1 "$TOL" "$HK"
else
    echo "Normal mode: $METHOD | h=$H | Iext=$IEXT (internal -$IEXT)"
    ./hh_sim "$METHOD" "$H" "$IEXT_NEG" 0 "$TOL" "$HK" > "${METHOD}.dat"
    echo "Saved → ${METHOD}.dat"
fi
