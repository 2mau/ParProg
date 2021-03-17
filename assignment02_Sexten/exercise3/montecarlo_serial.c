#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 500000000

void monteCarlo() {
	double x, y;
	size_t count = 0;
	double z, pi;

	for(size_t i = 0; i < ITERATIONS; i++) {

		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = x * x + y * y;
		if(z <= 1) count++;
	}
	pi = (double)count / ITERATIONS * 4;
	printf("Amount of trials= %d , pi is %g \n", ITERATIONS, pi);
}

int main() {
	struct timeval start, end;
	gettimeofday(&start, NULL);

	monteCarlo();

	gettimeofday(&end, NULL);
	double elapsed_time = (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6);
	printf("calculation took: %f seconds.\n", elapsed_time);

	exit(0);
}
