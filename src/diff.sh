#!/bin/bash
FILE1=${1:-rk4.txt}
FILE2=${2:-mid.txt}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    exit 1
fi

rm -f diff.txt

paste "$FILE1" "$FILE2" | awk '{print $1, $2 - $7}' > diff.txt

NAME1=$(basename "$FILE1" .txt)
NAME2=$(basename "$FILE2" .txt)

gnuplot -persist << EOF
set multiplot layout 2,1 scale 1,0.92

set title "Two solutions"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
plot "$FILE1" using 1:2 with lines lc rgb "blue" lw 2 title "$NAME1", \
     "$FILE2" using 1:2 with lines lc rgb "red"  lw 2 title "$NAME2"

set title "Difference ($NAME1 - $NAME2)"
set xlabel "Time (ms)"
set ylabel "ΔV (mV)"
set grid
plot "diff.txt" using 1:2 with lines lc rgb "black" lw 2 title "diff"

unset multiplot
EOF

rm -f diff.txt
