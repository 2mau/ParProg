#include <math.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 64 * 10
#define BLOCK_SIZE 64/sizeof(double)

double** a;
double** b;
double** c;
double** c2;

void original() {
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			for(int k = 0; k < N; ++k) {
				c[i][j] = a[i][k] * b[k][j];
			}
		}
	}
}

void trans() {
	// loop tiling
	 for(unsigned int ib = 0; ib < N-BLOCK_SIZE; ib += BLOCK_SIZE) {
		for(unsigned int jb = 0; jb < N-BLOCK_SIZE; jb += BLOCK_SIZE) {
			for(unsigned int kb = 0; kb < N-BLOCK_SIZE; kb += BLOCK_SIZE) {
				for(unsigned int i = ib; i < ib + BLOCK_SIZE; ++i) {
					for(unsigned int j = jb; j < jb + BLOCK_SIZE; ++j) {
						for(unsigned int k = kb; k < kb + BLOCK_SIZE; ++k) {
							c[i][j] = a[i][k] * b[k][j];
						}
					}
				}
			}
		}
	}
}

void init() {
	a = (double**)malloc(N * sizeof(double*));
	b = (double**)malloc(N * sizeof(double*));
	c = (double**)malloc(N * sizeof(double*));
	c2 = (double**)malloc(N * sizeof(double*));

	for(int i = 0; i < N; i++) {
		a[i] = (double*)calloc(N, sizeof(double));
		b[i] = (double*)calloc(N, sizeof(double));
		c[i] = (double*)calloc(N, sizeof(double));
		c2[i] = (double*)calloc(N, sizeof(double));
	}

	int count = 0;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++) {
			count++;
			a[i][j] = count;
			b[i][j] = count;
			c[i][j] = count;
			c2[i][j] = count;
		}
}

int main() {
  printf("Started");

	init();

	double startTime_original = omp_get_wtime();
	original();
	double endTime_original = omp_get_wtime();

	double startTime_trans = omp_get_wtime();
	trans();
	double endTime_trans = omp_get_wtime();

	printf("original time: %f\n", endTime_original - startTime_original);
	printf("trans time: %f\n", endTime_trans - startTime_trans);
}
