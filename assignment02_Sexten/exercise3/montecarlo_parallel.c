#include <math.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 500000000

#ifndef NUM_THREADS
#define NUM_THREADS 1
#endif

size_t iterations = 0;
_Atomic size_t count = 0;

void* monteCarloP() {
	double x, y, z;
	size_t localCount = 0;
	unsigned int seed = time(NULL);

	for(size_t i = 0; i < iterations; i++) {
		x = (double)rand_r(&seed) / RAND_MAX;
		y = (double)rand_r(&seed) / RAND_MAX;
		z = x * x + y * y;
		if(z <= 1) localCount++;
	}

	count += localCount;
	return NULL;
}

int main(void) {
	pthread_t threadIds[NUM_THREADS];
	iterations = ITERATIONS / NUM_THREADS;

	struct timeval start, end;
	gettimeofday(&start, NULL);

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_create(&threadIds[i], NULL, monteCarloP, NULL);

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threadIds[i], NULL);

	double pi = 4 * (double)count / (iterations * NUM_THREADS);
	gettimeofday(&end, NULL);

	double elapsed_time = (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6);
	printf("calculation took: %f seconds.\n", elapsed_time);
	printf("Amount of trials= %lu, using %d threads, estimate of pi is %g \n",
	       iterations * NUM_THREADS, NUM_THREADS, pi);
	return EXIT_SUCCESS;
}
