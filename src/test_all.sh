#!/bin/bash
# Full test suite — normal simulation + accuracy comparison

echo "Starting full test suite..."

# Normal simulation mode
echo "→ Normal mode: Dormand-Prince"
./run.sh dp 0.01 10 0 > dp_normal.txt

echo "→ Normal mode: Runge-Kutta 4"
./run.sh rk4 0.001 10 0 > rk4_normal.txt

echo "→ Normal mode: Midpoint"
./run.sh mid 0.001 10 0 > mid_normal.txt

# Calculus accuracy mode
echo "→ Calculus accuracy test"
./run.sh dp 4e-2 10 1 > calculus_report.txt

echo "Test suite completed."
echo "Generated files:"
ls -lh dp_normal.txt rk4_normal.txt calculus_report.txt 2>/dev/null
