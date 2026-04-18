#!/bin/bash
FILE1=${1:-rk4.txt}
FILE2=${2:-dp.txt}
if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then
    echo "Error/Please save yourself!"
    exit 1
fi

python3 -c '
import sys
import bisect

def load_file(filename):
    times = []
    vs = []
    with open(filename) as f:
        for line in f:
            parts = line.split()
            if len(parts) >= 2:
                times.append(float(parts[0]))
                vs.append(float(parts[1]))
    return times, vs

def interp(x_new, xs, ys):
    result = []
    for x in x_new:
        if x <= xs[0]:
            result.append(ys[0])
            continue
        if x >= xs[-1]:
            result.append(ys[-1])
            continue
        i = bisect.bisect_right(xs, x) - 1
        frac = (x - xs[i]) / (xs[i + 1] - xs[i])
        result.append(ys[i] + frac * (ys[i + 1] - ys[i]))
    return result

file2 = sys.argv[1]
file1 = sys.argv[2]
t1, v1 = load_file(file1)
t2, v2 = load_file(file2)
v2i = interp(t1, t2, v2)
for tt, vv, vvi in zip(t1, v1, v2i):
    print("{} {}".format(tt, vv - vvi))
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
     "$FILE2" using 1:2 with lines lc rgb "red" lw 2 title "$NAME2"
set title "Difference ($NAME1 - $NAME2)"
set xlabel "Time (ms)"
set ylabel "ΔV (mV)"
set grid
plot "diff.txt" using 1:2 with lines lc rgb "black" lw 2 title "diff"
unset multiplot
EOF
rm -f diff.txt
echo "Same."
