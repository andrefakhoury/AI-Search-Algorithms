#!/usr/bin/gnuplot -c 

set term png
set output "../graphs/result/maze".ARG1.".png"
set yrange [0:ARG2+0.0]
set boxwidth 0.5
set style fill solid
set xtics format ""
set grid ytics
set title "Runtime of each algorithm on Maze ".ARG1
set ylabel "Time (s)"
unset key
plot "../graphs/data/m".ARG1.".dat" u 1:3:($1+1):xtic(2) with boxes linecolor variable
