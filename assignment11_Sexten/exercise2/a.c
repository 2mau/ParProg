#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

#define N 100000000

int *a;
int *b;

// Assume N is odd

void original(){
  for (int i = 0; i < N - 1; ++i) {
      a[i] = b[i] + b[i + 1];
  }
}

void trans(){
  // Apply loop unrolling
  for (int i = 0; i < N - 1; i=i+2) {
      a[i] = b[i] + b[i + 1];
      a[i+1] = b[i+1] + b[i + 1 + 1];
  }
}

void init(){
  a = malloc(N*sizeof(int));
  b = malloc(N*sizeof(int));
}

int main(int argc, char **argv){

  init();

  if(argc > 1){
    printf("%s", argv[1]);
    double startTime_original = omp_get_wtime();
    original();
    double endTime_original = omp_get_wtime();
    printf("original time: %f\n", endTime_original - startTime_original);
  } else{
    double startTime_trans = omp_get_wtime();
    trans();
    double endTime_trans = omp_get_wtime();
    printf("trans time: %f\n", endTime_trans - startTime_trans);
  }

	
	
}
