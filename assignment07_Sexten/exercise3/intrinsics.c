#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <xmmintrin.h>

void calcSimd(float *a, float * b, float *c, int size, long repetitions) {

	for(int run = 0; run < repetitions; ++run) {
		for(int i = 0; i < size; i=i+4) {
        float* a_mem_adr = &a[i];
        __m128  ai4 = _mm_load_ps (a_mem_adr);
        __m128  bi4 = _mm_load_ps (&b[i]);
        __m128  ci4 = _mm_load_ps (&c[i]);
         _mm_store_ps(a_mem_adr, _mm_add_ps(ai4, _mm_mul_ps(bi4, ci4)));
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
    float *array = aligned_alloc(16, size*sizeof(float));
    for(int i = 0; i < size; i++){
        array[i] = value < 0 ? i : value;
    }
    return array;
}

int main(int argc, char *argv[]){
    long repetitions = 1e6;
    int vectorSize = 2048;
    float *a = init(vectorSize, 0);
    float *b = init(vectorSize, 1);
    float *c = init(vectorSize, -1);

    if (argc == 1) {
        printf("simd");
        calcSimd(a, b, c, vectorSize, repetitions);
    } else {
        printf("seq");
        calc(a, b, c, vectorSize, repetitions);
    }

    //startTime = omp_get_wtime();
    //endTime = omp_get_wtime();

    free(a);
    free(b);
    free(c);
    return EXIT_SUCCESS;
}
