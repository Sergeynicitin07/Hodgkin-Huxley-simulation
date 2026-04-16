#!/bin/bash

FILE1=${1:-dp.dat}
FILE2=${2:-rk4.dat}

paste -d ' ' "$FILE1" "$FILE2" | awk '{print $1, $2 - $4}' > diff.tmp

gnuplot -persist << EOF
set multiplot layout 2,1 scale 1,0.92

set title "Trajectories"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
plot "$FILE1" using 1:2 with lines lc rgb "blue" lw 2, \
     "$FILE2" using 1:2 with lines lc rgb "red"  lw 2

set title "Difference"
set xlabel "Time (ms)"
set ylabel "ΔV (mV)"
set grid
plot "diff.tmp" using 1:2 with lines lc rgb "black" lw 2

unset multiplot
EOF

rm -f diff.tmp
