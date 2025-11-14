set terminal pngcairo size 1200,800
set output "speedup.png"

set xlabel "Threads"
set ylabel "Speedup"
set title "Strong Scaling Speedup"
set grid

plot \
    "timing_results.txt" using 1:(52.823693252/$2) every ::1 with linespoints title "Measured", \
    x with lines title "Ideal"


