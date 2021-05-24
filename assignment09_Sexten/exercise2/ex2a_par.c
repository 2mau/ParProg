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
	#pragma omp parallel for firstprivate(factor)
	for(int i = 0; i < n; i++) {
		x[i] = (factor/(2^i)) * y[i];
	}

	//Time
	//0.002979

	end = omp_get_wtime();
	printf("%f\n", end - start);

	free(x);
	free(y);

	return EXIT_SUCCESS;
}