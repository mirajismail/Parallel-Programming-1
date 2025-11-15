set terminal pngcairo size 1200,800
set output "weak_scaling.png"

set xlabel "Threads"
set ylabel "Runtime (s)"
set title "Weak Scaling Runtime"
set grid

plot \
    "weak_scaling_results.txt" using 1:2 with linespoints title "Measured"

