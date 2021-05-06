#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void calcSimd(double *a, double * b, double *c, int size, long repetitions) {
	for(long run = 0; run < repetitions; ++run) {
        #pragma omp simd aligned(a,b,c : 16)
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}
}

void calc(double *a, double * b, double *c, int size, long repetitions) {
	for(int run = 0; run < repetitions; ++run) {
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}
}

double *init(int size, int value){
    double *array = aligned_alloc(16, size*sizeof(double));
    for(int i = 0; i < size; i++){
        array[i] = value < 0 ? i : value;
    }
    return array;
}

int compare(double *a, double *b, int size){
    for(int i = 0; i < size; i++){
        if (fabs(a[i] - b[i]) > 0.001){
            return 0;
        }
    }
    return 1;
}

int main(void){
    long repetitions = 1e6;
    int vectorSize = 2048;
    double *a = init(vectorSize, 0);
    double *a2 = init(vectorSize, 0);
    double *b = init(vectorSize, 1);
    double *c = init(vectorSize, -1);
    double startTime;
	double endTime;
    startTime = omp_get_wtime();
    calcSimd(a, b, c, vectorSize, repetitions);
    endTime = omp_get_wtime();
	printf("%f\n", endTime - startTime);
    calc(a2, b, c, vectorSize, repetitions);
    printf("Check %s\n", compare(a, a2, vectorSize) ? "true" : "false");
    free(a);
    free(a2);
    free(b);
    free(c);
    return EXIT_SUCCESS;
}