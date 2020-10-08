#!/usr/bin/gnuplot -c

set border linewidth 0
unset key
unset colorbox
unset tics
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.1

set title "Path found using ".ARG1
set term png
set output "../visualize/result/".ARG1.".png"
# set palette mode RGB
set palette grey
set pm3d map
splot "../visualize/data/".ARG1.".dat" matrix with image
