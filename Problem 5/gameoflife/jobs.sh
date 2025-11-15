#!/bin/bash
#SBATCH --job-name=gol_omp_test
#SBATCH --output=gol_omp_test.out
#SBATCH --error=gol_omp_test.err
#SBATCH --time=00:30:00
#SBATCH --cpus-per-task=16

module load gcc openmpi

echo -e "threads\truntime_sec" > timings.txt

for t in {1..16}; do
    export OMP_NUM_THREADS=$t

    runtime=$( /usr/bin/time -f "%e" ./gameoflife 1000 1000 1000 0.183 1 2>&1 >/dev/null )

    echo -e "$t\t$runtime" >> timings.txt
done

