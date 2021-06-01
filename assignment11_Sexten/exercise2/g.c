#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

#define N 100000000

int *a;
int *b;
int *c;


void original(){
 for (int i = 0; i < N; ++i) {
    if (i % 2) {
        a[i] = b[i] + 4;
    } else {
        a[i] = c[i] + 5;
    }
  }
}

void trans(){
  // loop splitting
  // Loop splitting attempts to simplify a loop or eliminate dependencies by breaking it
  // into multiple loops which have the same bodies but iterate over different contiguous
  // portions of the index range. A useful special case is loop peeling,
  // which can simplify a loop with a problematic first iteration by performing that
  // iteration separately before entering the loop.

  for (int i = 1; i < N; i=i+2) {
      a[i] = b[i] + 4;
  }

  for (int i = 0; i < N; i=i+2) {
      a[i] = c[i] + 5;
  }
}

void init(){
  a = malloc(N*sizeof(int));
  b = malloc(N*sizeof(int));
  c = malloc(N*sizeof(int));
}

int main(){

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
