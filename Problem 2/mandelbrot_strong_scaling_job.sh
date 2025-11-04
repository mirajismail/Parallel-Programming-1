#!/bin/bash
#SBATCH --job-name=mandelbrot_strong_scaling
#SBATCH --output=strong_scaling_%j.out
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=40
#SBATCH --time=00:30:00
#SBATCH --partition=compute


EXE="./mandelbrot"

THREADS=(1 2 4 8 16 32 40)

echo "Strong scaling analysis for Mandelbrot"
echo "Threads, Time(s)" > scaling_results.csv

for t in "${THREADS[@]}"; do
    export OMP_NUM_THREADS=$t
    echo "Running with $t threads..."

    # append wall clock time to scaling_results.csv
    /usr/bin/time -f "$t, %e" -a -o scaling_results.csv $EXE
done

echo "All runs complete. Results in scaling_results.csv"

