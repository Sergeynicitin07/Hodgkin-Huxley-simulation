#!/bin/bash

if [ -z "$1" ]; then
    gnuplot -persist << EOF
    set title "Hodgkin-Huxley V(t)"
    set xlabel "Time (ms)"
    set ylabel "V (mV)"
    set grid
    set key top right

    plot "rk4.txt" u 1:2 w l title "RK4", \
         "dp.txt"  u 1:2 w l title "Dormand-Prince", \
         "mid.txt" u 1:2 w l title "Midpoint"
EOF

else

    gnuplot -persist << EOF
    set title "Hodgkin-Huxley V(t) — $1"
    set xlabel "Time (ms)"
    set ylabel "V (mV)"
    set grid

    plot "$1.txt" u 1:2 w l title "$1"
EOF

fi
