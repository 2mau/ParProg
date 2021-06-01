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

echo "snippet a"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_a a.c &&  ./snippet_a
perf stat -e r01C7 ./snippet_a >> analysis_a

echo ""
echo "snippet b"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_b b.c &&  ./snippet_b

echo ""
echo "snippet c"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_c c.c &&  ./snippet_c

echo ""
echo "snippet d"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_d d.c &&  ./snippet_d

echo ""
echo "snippet e"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_e e.c &&  ./snippet_e

echo ""
echo "snippet f"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_f f.c &&  ./snippet_f

echo ""
echo "snippet g"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_g g.c &&  ./snippet_g

echo ""
echo "snippet h"
gcc -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_h h.c &&  ./snippet_h

rm snippet_a snippet_b snippet_c  snippet_d snippet_e snippet_f  snippet_g  snippet_h
