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


int original(){
  int sum_a = 0;
  int sum_b = 0;
  int sum_c = 0;
  for (int i = 0; i < N; ++i) {
      sum_a += a[i];
      sum_b += b[i];
      sum_c += c[i];
  }


  return sum_a + sum_b + sum_c;
}

int trans(){
  int sum_a = 0;
  int sum_b = 0;
  int sum_c = 0;

  // loop fision || can be better if the cache can be used more efficiently
  for (int i = 0; i < N; ++i) {
      sum_a += a[i];
  }
  for (int i = 0; i < N; ++i) {
      sum_b += b[i];
  }
  for (int i = 0; i < N; ++i) {
      sum_c += c[i];
  }


  return sum_a + sum_b + sum_c;
}

void init(){
  a = malloc(N*sizeof(int));
  b = malloc(N*sizeof(int));
  c = malloc(N*sizeof(int));
}

int main(){

  init();

  double startTime_original = omp_get_wtime();
  int res = original();
	double endTime_original = omp_get_wtime();


  double startTime_trans = omp_get_wtime();
  int res_trans = trans();
  double endTime_trans = omp_get_wtime();

	printf("original time: %f\n", endTime_original - startTime_original);
	printf("trans time: %f\n", endTime_trans - startTime_trans);
  printf("res: %d, res_trans %d", res, res_trans);
}
