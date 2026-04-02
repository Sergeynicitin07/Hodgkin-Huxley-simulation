set xlabel "t (ms)"
set ylabel "Membrane potential V (mV)"
set title "Hodgkin-Huxley model with different Iext"

plot "t.txt" using 1:2 with lines title "rk4 Iext = 10" lc rgb "red"
pause -1
