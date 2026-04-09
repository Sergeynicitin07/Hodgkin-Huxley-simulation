#!/bin/bash
# Plot V(t) from the last normal simulation

if [ ! -f dp_normal.txt ]; then
    echo "Error: dp_normal.txt not found. Run ./test_all.sh first."
    exit 1
fi

echo "Plotting V(t) using gnuplot..."
gnuplot -persist << EOF
set title "Hodgkin-Huxley Model — Membrane Potential V(t)"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
plot "dp_normal.txt" using 1:2 with lines title "V(t)" lw 2 lc rgb "blue"
EOF




