#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define N 1000

void hadamard(int32_t a[N][N],int32_t b[N][N],int32_t c[N][N], int choise) {
	for(size_t i = 0; i < N; ++i) {
		for(size_t j = 0; j < N; ++j) {
            if(choise){
               c[j][i] = a[j][i] * b[j][i]; 
            } else{
               c[i][j] = a[i][j] * b[i][j];
            }
		}
	}
}

int main(int argc, char* argv[]) {
	int choise;
	if(argc == 2) {
		choise = 1;
	} else {
		choise = 0;
	}
    printf("Choise: %i\n", choise);
    int32_t a[N][N];
    int32_t b[N][N];
    int32_t c[N][N];
    hadamard(a, b, c, choise);
    return EXIT_SUCCESS;
}