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

for i in 1 8; do
  export OMP_NUM_THREADS=$i
  ./eight_queens
done
OMP_NUM_THREADS=1

make clean
