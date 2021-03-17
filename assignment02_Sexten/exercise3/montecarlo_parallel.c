#include <math.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 500000000
#define NUM_THREADS 8

size_t iterations = 0;

/* a global static variable that is visible by all threads */
_Atomic size_t count = 0;

void* monteCarloP() {
	double x, y, z;
	int localCount = 0;
	pthread_t threadid = pthread_self();

	for(size_t i = 0; i < iterations; i++) {
		printf("Thread: %ld, i: %lu\n",threadid, i);
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = x * x + y * y;
		if(z <= 1) localCount++;
	}

	count += localCount;
	pthread_exit(NULL);
}

int main(void) {
	pthread_t threadIds[NUM_THREADS];
	iterations = ITERATIONS / NUM_THREADS;

	struct timeval start, end;
	gettimeofday(&start, NULL);

	for(int i = 0; i < NUM_THREADS; i++)
		if(pthread_create(&threadIds[i], NULL, monteCarloP, &iterations)){
			printf("Error");
		};

	for(int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threadIds[i], NULL);
		printf("thread %d, done\n", i);
	}

	double pi = 4 * (double)count / (iterations * NUM_THREADS);
	gettimeofday(&end, NULL);

	double elapsed_time = (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6);
	printf("calculation took: %f seconds.\n", elapsed_time);
	printf("Amount of trials= %lu , estimate of pi is %g \n", iterations * NUM_THREADS, pi);
	return EXIT_SUCCESS;
}
