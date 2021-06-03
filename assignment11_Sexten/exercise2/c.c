#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

#define N 100000000

double *a;

void original(){
  for (int i = 0; i < N; ++i) {
      a[i] *= hypot(0.3, 0.4);
  }
}

void trans(){
  // Loop invariant code-motion
  double tmp = hypot(0.3, 0.4);
  for (int i = 0; i < N; ++i) {
      a[i] *= tmp;
  }
}

void init(){
  a = malloc(N*sizeof(double));
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
