
#!/bin/bash
IEXT=${1:-10}
H=${2:-0.1}

echo "Running all 3 methods | h=$H | Iext=$IEXT"

./run.sh rk4 "$H" "$IEXT" 0 10.0 0.01 1e-14
./run.sh dp  "$H" "$IEXT" 0 10.0 0.01 1e-10
./run.sh mid "$H" "$IEXT" 0 10.0 0.01 1e-14

./plot.sh
echo "Graph opened."
