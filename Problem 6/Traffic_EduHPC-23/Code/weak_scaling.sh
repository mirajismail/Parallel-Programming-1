#!/bin/bash
#SBATCH --job-name=traffic-weak
#SBATCH --output=weak_scaling.out
#SBATCH --error=weak_scaling.err
#SBATCH --time=01:00:00
#SBATCH --cpus-per-task=16

module load gcc
module load openmp

EXE=./traffic

# Each ini file corresponds to a scaled problem size:
# weak1.ini  -> base case
# weak2.ini  -> 2× bigger
# weak4.ini  -> 4× bigger
# weak8.ini  -> 8× bigger
# weak12.ini -> 12× bigger
# weak16.ini -> 16× bigger

# Define the thread counts and matching ini files:
THREADS=(1 2 4 8 12 16)
INIFILES=(weak1.ini weak2.ini weak4.ini weak8.ini weak12.ini weak16.ini)

OUTFILE=weak_scaling_results.txt

echo "Weak scaling results" > $OUTFILE
echo "Using proportionally scaled L and N, and per=0" >> $OUTFILE
echo "" >> $OUTFILE
echo "Threads   Runtime(s)" >> $OUTFILE
echo "---------------------" >> $OUTFILE

for i in ${!THREADS[@]}; do
    t=${THREADS[$i]}
    ini=${INIFILES[$i]}

    echo "Running with $t threads, input=$ini ..."
    export OMP_NUM_THREADS=$t

    echo "Checking file: $ini"
    head -n 5 $ini

    RUNTIME=$(/usr/bin/time -f "%e" $EXE $ini 2>&1 > /dev/null)

    echo "$t        $RUNTIME" >> $OUTFILE
done
