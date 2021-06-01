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
      if (N % 2) {
          a[i] = b[i] + 5;
      } else {
          a[i] = c[i] + 5;
      }
  }
}

void trans(){
  if (N % 2) {
    for (int i = 0; i < N; ++i) {
            a[i] = b[i] + 5;
    }
  } else {
    for (int i = 0; i < N; ++i) {
            a[i] = c[i] + 5;
    }
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
