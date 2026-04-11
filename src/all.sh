#!/bin/bash

IEXT=${1:-10}
H=${2:-0.1}
TEND=${3:-10.0}
HK=${4:-0.01}
AS=${5:-1e-10}

echo "Running all 3 methods | h=$H | Iext=$IEXT | t_end=$TEND"

./run.sh rk4 "$H" "$IEXT" 0 "$TEND" "$HK" "$AS"
./run.sh dp  "$H" "$IEXT" 0 "$TEND" "$HK" "$AS"
./run.sh mid "$H" "$IEXT" 0 "$TEND" "$HK" "$AS"

./plot.sh
echo "Graph opened."
