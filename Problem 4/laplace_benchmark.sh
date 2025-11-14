#!/bin/bash
#SBATCH --job-name=laplace_omp_benchmark
#SBATCH --output=laplace_benchmark.out
#SBATCH --error=laplace_benchmark.err
#SBATCH --time=00:15:00
#SBATCH --cpus-per-task=16

# Load required modules
module load StdEnv/2023 gcc/12.3 rarray/2.8.0 netcdf/4.9.2 netcdf-cxx4/4.3.1

EXE=./laplace

# Output file for timing results
OUTFILE=timing_results.txt

echo "Threads   Runtime(s)" > $OUTFILE

# Run the Laplace solver for 1–16 threads
for t in {1..16}
do
    export OMP_NUM_THREADS=$t
    echo "Running with $t threads..."

    start=$(date +%s.%N)
    $EXE > /dev/null 2>&1
    end=$(date +%s.%N)

    runtime=$(echo "$end - $start" | bc)
    printf "%-8d %s\n" $t $runtime >> $OUTFILE
done

echo "Benchmark complete. Results saved to $OUTFILE"

