#!/bin/bash
IEXT=${1:-10}
H=${2:-0.01}
TOL=${3:-1e-10}

./run.sh rk4  "$H" "$IEXT" 1e-14 0.01 0
./run.sh dp   "$H" "$IEXT" "$TOL" "$H" 0
./run.sh mid  "$H" "$IEXT" 1e-14 0.01 0

gnuplot -persist << EOF
set title "Hodgkin-Huxley V(t) — Iext = $IEXT"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
set key top right
plot "rk4.dat"  u 1:2 w l lc rgb "red"    title "RK4", \
     "dp.dat"   u 1:2 w l lc rgb "blue"   title "Dormand-Prince", \
     "mid.dat"  u 1:2 w l lc rgb "green"  title "Midpoint"
EOF
