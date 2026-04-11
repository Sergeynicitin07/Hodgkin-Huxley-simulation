#!/bin/bash
if [ -z "$1" ]; then
    gnuplot -persist << EOF
    set title "Hodgkin-Huxley V(t)"
    set xlabel "Time (ms)"
    set ylabel "V (mV)"
    set grid
    set key top right
    plot "rk4.dat" u 1:2 w l lc rgb "red"    title "RK4", \
         "dp.dat"  u 1:2 w l lc rgb "blue"   title "Dormand-Prince", \
         "mid.dat" u 1:2 w l lc rgb "green"  title "Midpoint"
EOF
else
    gnuplot -persist << EOF
    set title "Hodgkin-Huxley V(t) — $1"
    set xlabel "Time (ms)"
    set ylabel "V (mV)"
    set grid
    plot "$1.dat" u 1:2 w l lc rgb "blue" title "$1"
EOF
fi
