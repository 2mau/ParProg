#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void calcSimd(float *a, float * b, float *c, int size, long repetitions) {
	for(int run = 0; run < repetitions; ++run) {
        #pragma omp simd aligned(a,b,c : 16)
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}
}

void calc(float *a, float * b, float *c, int size, long repetitions) {
	for(int run = 0; run < repetitions; ++run) {
		for(int i = 0; i < size; ++i) {
			a[i] += b[i] * c[i];
		}
	}
}

float *init(int size, int value){
    float *array = malloc(size*sizeof(float));
    for(int i = 0; i < size; i++){
        array[i] = value < 0 ? i : value;
    }
    return array;
}

int compare(float *a, float *b, int size){
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
    float *a = init(vectorSize, 0);
    float *a2 = init(vectorSize, 0);
    float *b = init(vectorSize, 1);
    float *c = init(vectorSize, -1);
    double startTime;
	double endTime;
    startTime = omp_get_wtime();
    calcSimd(a, b, c, vectorSize, repetitions);
    endTime = omp_get_wtime();
	printf("%f\n", endTime - startTime);
    calc(a2, b, c, vectorSize, repetitions);
    printf("Check %s\n", compare(a, a2, vectorSize) ? "true" : "false");
    free(a);
    free(b);
    free(c);
    return EXIT_SUCCESS;
}