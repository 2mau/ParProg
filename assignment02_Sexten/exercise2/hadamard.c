#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define N 10

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

int cacheMisses(int blocksize, int setsize, int cachesize, int n, int choise){
    int cachelines = cachesize/blocksize;
    int sets = cachelines/setsize;
    int entriesPerBlock = blocksize/sizeof(int32_t);
    int matrixsize = n*n;
    int misses;
    //columns bevore rows: 11, 12, 13, 21, 22, ...
    if(!choise){
        int blocksPerMatrix = matrixsize/entriesPerBlock;
        //round-up
        if(matrixsize % entriesPerBlock){
            blocksPerMatrix += 1;
        }
        //Since every block is in the cache once
        misses = 2*blocksPerMatrix; 
    }
    else{

    }
    return misses;
}

int main(int argc, char* argv[]) {
	int choise;
	if(argc == 2) {
		choise = 1;
	} else {
		choise = 0;
	}
    printf("Choise: %i\n", choise);
    int a[N][N];
    int b[N][N];
    int c[N][N];
    /*for(int i=0; i<N; i++) {
      for(int j=0; j<N;j++) {
          a[i][j] = rand();
          b[i][j] = rand();
      }
    }*/
    hadamard(a, b, c, choise);
    //printf("%i\n", cacheMisses(12, 2, 24, 10, 0));
    return 0;
}