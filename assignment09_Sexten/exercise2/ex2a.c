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


	double factor = 1;
	for(int i = 0; i < n; i++) {
		x[i] = factor * y[i];
		factor = factor / 2;
	}
	//Dependency: 
		// Anti Dependence; first read then write in 18 - 19
		// True Dependence: first write then read in 19 - 18
	
    //Loop carried dependence
	//Cannot be parallelized trivialy by the compiler.

	end = omp_get_wtime();
	printf("%f,", end - start);

	free(x);
	free(y);

	return EXIT_SUCCESS;
}