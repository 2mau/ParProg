#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	int n = strtol(argv[1], NULL, 10);
	double *x = malloc(n * sizeof(double));
	double *y = malloc(n * sizeof(double));
	double *z = malloc(n * sizeof(double));

	double start;
	double end;
	start = omp_get_wtime();

	for(int i = 1; i < n; i++) {
		x[i] = (x[i] + y[i - 1]) / 2;
		y[i] = y[i] + z[i] * 3;
	}
	// Dependency:
	// True Dependence: first write then read in 
	// S18[1] TD S17[2],...
	// Loop carried dependence

	// Time
	// 0.017029

	end = omp_get_wtime();
	printf("%f,", end - start);


	free(x);
	free(y);
	free(z);
	return EXIT_SUCCESS;
}