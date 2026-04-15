#!/bin/bash
# Usage: ./diff.sh file1.dat file2.dat [title]

FILE1=${1:-dp.dat}
FILE2=${2:-rk4.dat}
TITLE=${3:-"Difference V($FILE1) - V($FILE2)"}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    echo "Error!"
    exit 1
fi

gnuplot -persist << EOF
set title "$TITLE"
set xlabel "Time (ms)"
set ylabel "ΔV = V1 - V2 (mV)"
set grid
set key top left

plot "$FILE1" using 1:2 with lines lc rgb "blue" lw 2 title "$FILE1", \
     "$FILE2" using 1:2 with lines lc rgb "red"  lw 2 title "$FILE2", \
     "$FILE1" using 1:(column(2) - column(2) from "$FILE2") with lines lc rgb "black" lw 2 title "Difference"
EOF
