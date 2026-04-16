#!/bin/bash

FILE1=${1:-rk4.txt}
FILE2=${2:-mid.txt}

if [ ! -f "$FILE1" ] || [ ! -f "$FILE2" ]; then

exit 1
fi

paste "$FILE1" "$FILE2" | awk '
{
t = $1
v1 = $2
v2 = $7 # 2-й файл: t v ...
print t, v1 - v2
}
' > diff.txt

NAME1=$(basename "$FILE1" .txt)
NAME2=$(basename "$FILE2" .txt)

gnuplot -persist << EOF
set multiplot layout 2,1

set title "Two solutions"
plot "$FILE1" using 1:2 with lines lc rgb "blue" lw 2 title "$NAME1", \
     "$FILE2" using 1:2 with lines lc rgb "red"  lw 2 title "$NAME2"

set title "Difference ($NAME1 - $NAME2) "
plot "diff.txt" using 1:2 with lines lc rgb "black" lw 2 title "diff"

unset multiplot
EOF
