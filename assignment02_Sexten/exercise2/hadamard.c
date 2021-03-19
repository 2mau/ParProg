#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

void hadamard(int32_t a[N][N], int32_t b[N][N], int32_t c[N][N], int choice) {
	for(size_t i = 0; i < N; ++i) {
		for(size_t j = 0; j < N; ++j) {
			if(choice) {
				c[j][i] = a[j][i] * b[j][i];
			} else {
				c[i][j] = a[i][j] * b[i][j];
			}
		}
	}
}

int main(int argc, char* argv[]) {
	int choice;

	if(argc == 2) {
		choice = 1;
		printf("snippet 2: %i\n", choice);
	} else {
		choice = 0;
		printf("snippet 1: %i\n", choice);
	}

	int32_t a[N][N];
	int32_t b[N][N];
	int32_t c[N][N];

	hadamard(a, b, c, choice);

	return EXIT_SUCCESS;
}
