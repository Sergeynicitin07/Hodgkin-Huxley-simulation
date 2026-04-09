#!/bin/bash
# Usage: ./run.sh <method> [step] [Iext] [calculus]
# method: dp | rk4 | mid
# calculus: 0 = normal mode, 1 = accuracy test (calculus)

METHOD=${1:-dp}
STEP=${2:-0.01}
IEXT=${3:--10}
CALCULUS=${4:-0}

if [ $CALCULUS -eq 1 ]; then
    echo "Running in calculus comparison mode..."
    ./hh_sim "$METHOD" "$STEP" "$IEXT" 1
else
    echo "Running $METHOD method (normal simulation)"
    echo "Step: $STEP | Iext: $IEXT | t_end = 100.0"
    ./hh_sim "$METHOD" "$STEP" "$IEXT" 0
fi
