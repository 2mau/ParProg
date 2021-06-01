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
  int sum = 0;
  int min = a[0];

  for (int i = 1; i < N; ++i) {
      min = (a[i] < min) ? a[i] : min;
  }
  for (int i = 0; i < N; ++i) {
      sum += a[i];
  }
}

void trans(){
  // loop peeling and fusion
  // Loop peeling is a special case of loop splitting which splits any problematic first (or last) few iterations
  // from the loop and performs them outside of the loop body.
  int sum = a[0];
  int min = a[0];

  for (int i = 1; i < N; ++i) {
      min = (a[i] < min) ? a[i] : min;
      sum += a[i];
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
