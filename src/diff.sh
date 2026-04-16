#!/bin/bash

FILE1=${1:-dp.dat}
FILE2=${2:-rk4.dat}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    exit 1
fi

awk 'NR==FNR {a[NR]=$2; next} {print $1, a[NR]-$2}' "$FILE1" "$FILE2" > diff.tmp

gnuplot -persist << EOF
set multiplot layout 2,1 title "Comparison" scale 1,0.92

set title "Trajectories"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
plot "$FILE1" using 1:2 with lines lc rgb "blue" lw 2, \
     "$FILE2" using 1:2 with lines lc rgb "red"  lw 2

set title "Difference (V1 - V2)"
set xlabel "Time (ms)"
set ylabel "ΔV (mV)"
set grid
plot "diff.tmp" using 1:2 with lines lc rgb "black" lw 2

unset multiplot
EOF

rm -f diff.tmp
