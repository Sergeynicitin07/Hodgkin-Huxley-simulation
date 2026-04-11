#!/bin/bash
# Запуск всех методов с большим шагом 0.1 и положительным током
H=0.1
IEXT=${1:-10}

echo "Running all methods with h=$H | Iext=$IEXT"

./run.sh rk4 "$H" "$IEXT" 0 10.0 0.01 1e-14
./run.sh dp  "$H" "$IEXT" 0 10.0 0.01 1e-10
./run.sh mid "$H" "$IEXT" 0 10.0 0.01 1e-14

./plot.sh
echo "All done. Graph opened."
