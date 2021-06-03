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
int *d;
int *e;
int *f;

void original(){

  for (int i = 1; i < N - 2; ++i) {
      b[i] = a[i - 1] + 1;
      c[i] = 2 * a[i];
      d[i] = a[i + 1] + 2;
      e[i + 1] = a[i + 2] + 3;
      f[i + 1] = e[i] + 4;
  }
}

void trans(){
  b[1] = a[0] + 1;

  for (int i = 1; i < N - 2; ++i) {
      if(i < N-3) b[i+1] = a[i] + 1;
      c[i] = 2 * a[i];
      if(i > 1) d[i-1] = a[i] + 2;
      if(i > 2) e[i-1] = a[i] + 3;
      if(i > 1) f[i] = e[i-1] + 4;
  }
  d[N-3] = a[N-2] + 2;
  e[N-2] = a[N-1] + 3;
  f[N-2] = e[N-1] + 4;
}

void init(){
  a = malloc(N*sizeof(int));
  b = malloc(N*sizeof(int));
  c = malloc(N*sizeof(int));
  d = malloc(N*sizeof(int));
  e = malloc(N*sizeof(int));
  f = malloc(N*sizeof(int));
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
