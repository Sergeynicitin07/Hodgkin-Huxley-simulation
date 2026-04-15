#!/bin/bash

METHOD=${1:-dp}

CALC=${2:-1}  

IEXT=${3:-10}

TEND=${4:-10.0}

H=${5:-0.1}

TOL=${6:-1e-1}

AS=${7:-1e-10}

if [ $CALC -eq 1 ]; then

    echo "Calculus mode"

    echo "method = $METHOD | h = $H | Iext = $IEXT | t_end = $TEND | tol = $TOL | tol_for_dp = $AS"

    ./hh_sim "$METHOD" "$CALC" "$IEXT" "$TEND" "$H" "$TOL" "$AS"

else

    echo "Normal mode"

    echo "method = $METHOD | h = $H | Iext = $IEXT | t_end = $TEND | tol = $TOL | tol_for_dp = $AS"

    ./hh_sim "$METHOD" "$CALC" "$IEXT" "$TEND" "$H" "$TOL" "$AS" > "${METHOD}.dat"

    echo "Data saved → ${METHOD}.dat"

fi
