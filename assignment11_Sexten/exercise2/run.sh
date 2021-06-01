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
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_a a.c &&  ./snippet_a
gprof snippet_a gmon.out > analysis_a.txt
gprof --line snippet_a gmon.out > analysis_a_line.txt

echo ""
echo "snippet b"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_b b.c &&  ./snippet_b
gprof snippet_b gmon.out > analysis_b.txt
gprof --line snippet_b gmon.out > analysis_b_line.txt

echo ""
echo "snippet c"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_c c.c &&  ./snippet_c
gprof snippet_c gmon.out > analysis_c.txt
gprof --line snippet_c gmon.out > analysis_c_line.txt

echo ""
echo "snippet d"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_d d.c &&  ./snippet_d
gprof snippet_d gmon.out > analysis_d.txt
gprof --line snippet_d gmon.out > analysis_d_line.txt

echo ""
echo "snippet e"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_e e.c &&  ./snippet_e
gprof snippet_e gmon.out > analysis_e.txt
gprof --line snippet_e gmon.out > analysis_e_line.txt

echo ""
echo "snippet f"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_f f.c &&  ./snippet_f
gprof snippet_f gmon.out > analysis_f.txt
gprof --line snippet_f gmon.out > analysis_f_line.txt

echo ""
echo "snippet g"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_g g.c &&  ./snippet_g
gprof snippet_g gmon.out > analysis_g.txt
gprof --line snippet_g gmon.out > analysis_g_line.txt

echo ""
echo "snippet h"
gcc -pg -g -std=gnu11 -Wall -Wextra -O3 -lm -fopenmp -o snippet_h h.c &&  ./snippet_h
gprof snippet_h gmon.out > analysis_h.txt
gprof --line snippet_h gmon.out > analysis_h_line.txt

rm snippet_a snippet_b snippet_c  snippet_d snippet_e snippet_f  snippet_g  snippet_h
