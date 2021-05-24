#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	int n = strtol(argv[1], NULL, 10);
	double *x = malloc(n * sizeof(double));
	double *y = malloc(n * sizeof(double));
	double *twiceArr = calloc(n, sizeof(double));

	double start;
	double end;
	start = omp_get_wtime();

	x[0] = x[0] + 5 * y[0];

	#pragma omp parallel for
	for(int i = 1; i < n; i++) {
		x[i] = x[i] + 5 * y[i];
		unsigned int seed = omp_get_thread_num();
		int twice = rand_r(&seed)%2;
		if(twice) {
			twiceArr[i-1] = 1;
		}
	}

	#pragma omp parallel for
	for(int i=1; i<n; i++){
		if(twiceArr[i] == 1){
			x[i] = x[i] * 2;
		}
	}


	end = omp_get_wtime();
	printf("%f\n", end - start);

	free(x);
	free(y);
	free(twiceArr);

	return EXIT_SUCCESS;
}