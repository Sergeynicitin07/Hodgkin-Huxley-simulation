#!/bin/bash

FILE1=${1:-dp.dat}
FILE2=${2:-rk4.dat}
TITLE=${3:-"Difference $FILE1 - $FILE2"}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    echo "Error!"
    exit 1
fi

gnuplot -persist << EOF
set multiplot layout 2,1 title "$TITLE" scale 1,0.95

set title "Two trajectories"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
plot "$FILE1" using 1:2 with lines lc rgb "blue" lw 2 title "$FILE1", \
     "$FILE2" using 1:2 with lines lc rgb "red"  lw 2 title "$FILE2"

set title "Difference (V1 - V2)"
set xlabel "Time (ms)"
set ylabel "ΔV (mV)"
set grid
plot "$FILE1" using 1:(\$2 - column(2) from "$FILE2") with lines lc rgb "black" lw 2 title "Difference"

unset multiplot
EOF
