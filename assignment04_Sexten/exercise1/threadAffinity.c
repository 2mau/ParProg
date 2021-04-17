#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100000000
int main (){

    int sum = 0;

    double startTime = omp_get_wtime();

    #pragma omp parallel for
	for(int i = 0; i < N; ++i) {
		#pragma omp atomic
		sum++;
	}

    double endTime = omp_get_wtime();

    printf("sum: %d, time: %2.4f seconds\n", sum, endTime-startTime);

    return EXIT_SUCCESS;
}