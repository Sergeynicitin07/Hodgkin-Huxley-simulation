#!/bin/bash
FILE1=${1:-rk4.txt}
FILE2=${2:-mid.txt}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    exit 1
fi

rm -f diff.txt

awk '
BEGIN {
    while ((getline < "'"$FILE2"'") > 0) {
        t2[++n2] = $1
        v2[n2] = $2
    }
    close("'"$FILE2"'")
}
{
    t1 = $1
    v1 = $2

    if (t1 < t2[1] || t1 > t2[n2]) {
        printf "Warning: t=%.6f out of range [%.6f, %.6f] WE SHOULD DIED!!!\n", t1, t2[1], t2[n2] > "/dev/stderr"
        next
    }

    lo = 1; hi = n2
    while (hi - lo > 1) {
        mid = int((lo + hi) / 2)
        if (t2[mid] <= t1) lo = mid
        else hi = mid
    }

    v2_interp = v2[lo] + (v2[hi] - v2[lo]) * (t1 - t2[lo]) / (t2[hi] - t2[lo])
    diff = v1 - v2_interp
    print t1, diff
}' "$FILE1" > diff.txt

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

set title "Difference ($NAME1 - $NAME2) interpolated on $NAME1 grid"
set xlabel "Time (ms)"
set ylabel "ΔV (mV)"
set grid
plot "diff.txt" using 1:2 with lines lc rgb "black" lw 2 title "diff"

unset multiplot
EOF

rm -f diff.txt
