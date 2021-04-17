#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100000000
#define SWAP(a, b) \
	{ \
		int32_t temp = a; \
		a = b; \
		b = temp; \
	}

double startTime, endTime;
int num_threads;
unsigned int seed;

void merge(int32_t a[], int32_t size, int32_t temp[]) {
	int32_t i1 = 0;
	int32_t i2 = size / 2;
	int32_t it = 0;

	while(i1 < size / 2 && i2 < size) {
		if(a[i1] <= a[i2]) {
			temp[it] = a[i1];
			i1 += 1;
		} else {
			temp[it] = a[i2];
			i2 += 1;
		}
		it += 1;
	}

	while(i1 < size / 2) {
		temp[it] = a[i1];
		i1++;
		it++;
	}
	while(i2 < size) {
		temp[it] = a[i2];
		i2++;
		it++;
	}

	memcpy(a, temp, size * sizeof(int32_t));
}

void mergesort_serial(int32_t a[], int32_t size, int32_t temp[]) {
	if(size == 2) {
		if(a[0] <= a[1])
			return;
		else {
			SWAP(a[0], a[1]);
			return;
		}
	}

	size_t sizeH = size / 2;
	if(sizeH > 1) mergesort_serial(a, sizeH, temp);
	if(size - sizeH > 1) mergesort_serial(a + sizeH, size - sizeH, temp);

	merge(a, size, temp);
}

void mergesort_parallel_omp(int32_t a[], int32_t size, int32_t temp[]) {
	if(size < 75000) {
		mergesort_serial(a, size, temp);
		return;
	}

	int32_t sizeH = size / 2;
#pragma omp taskgroup
	{
#pragma omp task
		mergesort_parallel_omp(a, sizeH, temp);
#pragma omp task
		mergesort_parallel_omp(a + sizeH, size - sizeH, temp + sizeH);
	}

	merge(a, size, temp);
}

void tearDown(int32_t a[]) {
	printf("threads: %d, ", num_threads);
	// printf("ArraySize: %d\n", SIZE);
	printf("time: %f ", endTime - startTime);
	printf("proc bind %d, ", omp_get_proc_bind());

	for(int32_t i = 0; i < SIZE - 1; ++i) {
		if(!(a[i] <= a[i + 1])) {
			printf("Array not sorted!");
			break;
		}
	}
	printf("\n");
}

int main() {
	int32_t* a = (int32_t*)malloc(SIZE * sizeof(int32_t));
	int32_t* temp = (int32_t*)malloc(SIZE * sizeof(int32_t));
	seed = time(NULL);
	num_threads = omp_get_max_threads();

#pragma omp parallel for default(none) shared(seed, a, temp)
	for(int32_t i = 0; i < SIZE; i++) {
		a[i] = rand_r(&seed) % SIZE;
		temp[i] = 0;
	}

	startTime = omp_get_wtime();

#pragma omp parallel
	{
#pragma omp master
		mergesort_parallel_omp(a, SIZE, temp);
	}

	endTime = omp_get_wtime();

	tearDown(a);

	free(a);
	free(temp);
}
