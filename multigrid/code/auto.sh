#!/bin/bash
make main
declare -i n=30
declare -i nu1=2
declare -i nu2=2
declare -i k=0

for k in 4 7; do
    for ((i = 1; i <= nu1; i++)); do
        for ((j = 1; j <= nu2; j++)); do
            ./main $k $n $i $j
            mv data "n"$k"nu1"$i"nu2"$j
            echo "n"$k"nu1"$i"nu2"$j | python plot.py
            rm "n"$k"nu1"$i"nu2"$j
            echo "plot is being generated for n"$k"nu1"$i"nu2"$j
        done
    done
done

mv *.pdf ../PLOTS/
make clean
