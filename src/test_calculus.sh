#!/bin/bash
IEXT=${1:-10}
TOL=${2:-1e-10}
./run.sh dp 0.01 "$IEXT" 1 "$TOL" 0.01
