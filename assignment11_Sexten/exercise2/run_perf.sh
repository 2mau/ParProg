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
#module load gcc/8.2.0

# Set up any environment variables
# export ENVIRONMENT_VARIABLE=foobar

# ./path/to/application <command> <line> <arguments>

for task in a b c d e f g h
do
    rm $task
    echo "Snippet $task"
    gcc -g -std=gnu11 -Wall -Wextra -O3 -fopenmp ${task}.c -o ${task}
    perf stat -e task-clock,cycles,instructions,branch-instructions,branch-misses,cache-references,cache-misses ./$task
    perf stat -e task-clock,cycles,instructions,branch-instructions,branch-misses,cache-references,cache-misses ./$task 1
echo "------------------"
done