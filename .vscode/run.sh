#!/bin/bash

# Executes job in the queue "lva.q" unless you have special requirements.
#$ -q lva.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N my_test_job

# Redirect output stream to this file.
#$ -o bench.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0

# Set up any environment variables
# export ENVIRONMENT_VARIABLE=foobar

# ./path/to/application <command> <line> <arguments>

make clean
make

for place in threads cores sockets
do
    for n in 1 4
    do
        for proc_bind in 'true' 'false' master close spread
        do
            for i in $(seq 1 5)
            do
                qsub \
                    -N a4_e1_${n}-${place}_${proc_bind}_${i} \
                    # -o stuff/lcc2_logs/${n}-${place}_${proc_bind}_${i}.log \
                    -pe openmp 4 \
                    -v OMP_NUM_THREADS=$n \
                    -v OMP_PLACES=$place \
                    -v OMP_PROC_BIND=$proc_bind \
                    lcc2_base_job.sh
            done
        done
    done
done

make clean
