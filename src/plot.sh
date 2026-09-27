#!/bin/bash

if [ "$1" = "2" ]; then

    gnuplot -persist << EOF
set title "HH model and experiment"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
set key top right

plot \
    "experiment.txt" using 1:2 with lines title "Experiment", \
    "rk4.txt" using 1:2 with lines title "RK4"
EOF

elif [ -z "$1" ]; then

    gnuplot -persist << EOF
set title "Hodgkin-Huxley V(t)"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid
set key top right

plot \
    "rk4.txt" using 1:2 with lines title "RK4", \
    "dp.txt" using 1:2 with lines title "Dormand-Prince", \
    "mid.txt" using 1:2 with lines title "Midpoint"
EOF

else

    gnuplot -persist << EOF
set title "Hodgkin-Huxley V(t) — $1"
set xlabel "Time (ms)"
set ylabel "V (mV)"
set grid

plot "$1.txt" using 1:2 with lines title "$1"
EOF

fi
