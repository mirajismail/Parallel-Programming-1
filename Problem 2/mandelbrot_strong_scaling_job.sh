#!/bin/bash
#SBATCH --job-name=mandelbrot_strong_scaling
#SBATCH --output=strong_scaling_%j.out
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=40
#SBATCH --time=00:30:00
#SBATCH --partition=compute

module load intel/2018.2

EXE="./mandelbrot"

THREADS=(1 2 4 8 16 32 40)
RESULTS=scaling_results.csv

printf "%-8s %-10s %-10s %-10s\n" "Threads" "Time(s)" "Speedup" "Efficiency" > $RESULTS
base_time=0

for t in "${THREADS[@]}"; do
    export OMP_NUM_THREADS=$t
    echo "Running with $t threads..."

    # append wall clock time to scaling_results.csv
   runtime=$(/usr/bin/time -f "%e" 2>&1 $EXE | tail -n 1)

    if [ "$t" -eq 1 ]; then
        base_time=$runtime
        speedup=1.0
        efficiency=1.0
    else
        speedup=$(echo "scale=4; $base_time / $runtime" | bc)
        efficiency=$(echo "scale=4; $speedup / $t" | bc)
    fi

    printf "%-8d %-10.4f %-10.4f %-10.4f\n" "$t" "$runtime" "$speedup" "$efficiency" >> $RESULTS
done

echo "Strong scaling complete. Results saved in $RESULTS"
