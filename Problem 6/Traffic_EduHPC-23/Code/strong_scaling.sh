#!/bin/bash
#SBATCH --job-name=traffic-strong
#SBATCH --output=strong_scaling.out
#SBATCH --error=strong_scaling.err
#SBATCH --time=00:10:00
#SBATCH --cpus-per-task=16

module load gcc
module load openmp

EXE=./traffic
INI=largetest.ini

OUTFILE=strong_scaling_results.txt

echo "Strong scaling results" > $OUTFILE
echo "Using largetest.ini with per=0" >> $OUTFILE
echo "" >> $OUTFILE
echo "Threads   Runtime(s)" >> $OUTFILE
echo "---------------------" >> $OUTFILE

# Run for these thread counts
THREADS="1 2 4 8 12 16"

for t in $THREADS; do
    echo "Running with $t threads..."
    export OMP_NUM_THREADS=$t

    RUNTIME=$(/usr/bin/time -f "%e" $EXE $INI 2>&1 > /dev/null)

    echo "$t        $RUNTIME" >> $OUTFILE
done

