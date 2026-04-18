#!/bin/bash

FILE1=${1:-rk4.txt}
FILE2=${2:-mid.txt}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    echo "WE SHOULD DIE!"
    exit 1
fi

awk '
    NR==FNR { 
        t2[NR] = $1; 
        v2[NR] = $2; 
        n2 = NR; 
        next 
    }
    {
        t1 = $1
        v1 = $2
        lo = 1; hi = n2
        while (hi - lo > 1) {
            mid = int((lo + hi)/2)
            if (t2[mid] <= t1) lo = mid
            else hi = mid
        }
        if (t1 <= t2[1])      v2_interp = v2[1]
        else if (t1 >= t2[n2]) v2_interp = v2[n2]
        else {
            frac = (t1 - t2[lo]) / (t2[lo+1] - t2[lo])
            v2_interp = v2[lo] + frac * (v2[lo+1] - v2[lo])
        }
        print t1, v1 - v2_interp
    }
' "$FILE2" "$FILE1" > diff.txt

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
echo "Done."
