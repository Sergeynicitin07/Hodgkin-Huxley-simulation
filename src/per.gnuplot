
set xlabel "t (ms)"
set ylabel "Membrane potential V (mV)"
set title "Hodgkin-Huxley model with different Iext"

plot "data1.txt" using 1:2 with lines title "rk4 Iext = 10" lc rgb "red", \
     "data2.txt" using 1:2 with lines title "mid Iext = 10" lc rgb "green", \
     "data3.txt" using 1:2 with lines title "dp Iext = 10" lc rgb "blue", \
     "data4.txt" using 1:2 with lines title "trap Iext = 10" lc rgb "yellow"
pause -1
