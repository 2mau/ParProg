#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 500000000


void monteCarlo() {
	size_t count = 0;
	double pi;
	#pragma omp parallel
	{
	double x, y;
	double z;
	size_t local_count = 0;
	unsigned int seed = time(NULL);

	#pragma omp for
	for(size_t i = 0; i < ITERATIONS; i++) {
		x = (double)rand_r(&seed) / RAND_MAX;
		y = (double)rand_r(&seed) / RAND_MAX;
		z = x * x + y * y;
		if(z <= 1) local_count++;
	}
	
	#pragma omp atomic
		count += local_count;
	}
	pi = (double)count / ITERATIONS * 4;
	printf("%g ", pi);
}

int main() {
	double start,end;
	start = omp_get_wtime();
	//struct timeval start, end;
	//gettimeofday(&start, NULL);

	monteCarlo();

	//gettimeofday(&end, NULL);
	//double elapsed_time = (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6);
	end = omp_get_wtime();
	double elapsed_time = end - start;
	printf("%f\n", elapsed_time);

	exit(0);
}
