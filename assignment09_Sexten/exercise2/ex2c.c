#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	int n = strtol(argv[1], NULL, 10);
	double *x = malloc(n * sizeof(double));
	double *y = malloc(n * sizeof(double));

	double start;
	double end;
	start = omp_get_wtime();

	x[0] = x[0] + 5 * y[0];
	for(int i = 1; i < n; i++) {
		x[i] = x[i] + 5 * y[i];
		unsigned int seed = omp_get_thread_num();
		int twice = rand_r(&seed) % 2;
		if(twice) {
			x[i - 1] = 2 * x[i - 1];
		}
	}
	// Dependency:
	// True Dependence: first write then read in
	// S17[1] TD S19[2],...
	// Loop carried dependence
	// S21 is control dependent on S19


	end = omp_get_wtime();
	printf("%f,", end - start);

	free(x);
	free(y);

	return EXIT_SUCCESS;
}