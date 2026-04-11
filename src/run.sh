#!/bin/bash
METHOD=$1
H=$2
IEXT=${3:-10}
CALC=${4:-0}
AS=${5:-1e-10}
HK=${6:-0.01}

IEXT_NEG=$(( -IEXT ))

if [ $CALC -eq 1 ]; then
    echo "Calculus mode → $METHOD | tol=$AS | hk=$HK | Iext=$IEXT"
    ./hh_sim "$METHOD" "$H" "$IEXT_NEG" 1 "$AS" "$HK"
else
    echo "Normal mode → $METHOD | h=$H | Iext=$IEXT"
    ./hh_sim "$METHOD" "$H" "$IEXT_NEG" 0 "$AS" "$HK" > "${METHOD}.dat"
    echo "Saved → ${METHOD}.dat"
fi
