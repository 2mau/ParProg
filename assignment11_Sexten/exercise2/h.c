#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

#define N 64 * 10

double **a;
double **b;
double **c;
double **c2;


void original(){
  for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
          for (int k = 0; k < N; ++k) {
              c[i][j] = a[i][k] * b[k][j];
          }
      }
  }
}

void trans(){
  // loop tiling
  for (int i = 0; i < N; ++i) {
      for (int k = 0; k < N; ++k) {
          double a_tmp = a[i][k];
          for (int j = 0; j < N; ++j) {
              c2[i][j] =  a_tmp * b[k][j];
          }
      }
  }
}

void init(){
  a = (double **) malloc(N * sizeof(double *));
  b = (double **) malloc(N * sizeof(double *));
  c = (double **) malloc(N * sizeof(double *));
  c2 = (double **) malloc(N * sizeof(double *));

  for (int i=0; i<N; i++){
    a[i] = (double *)calloc(N, sizeof(double));
    b[i] = (double *)calloc(N, sizeof(double));
    c[i] = (double *)calloc(N, sizeof(double));
    c2[i] = (double *)calloc(N, sizeof(double));
  }

  int count = 0;
    for (int i = 0; i <  N; i++)
      for (int j = 0; j < N; j++){
         count++;
         a[i][j] = count;
         b[i][j] = count;
         c[i][j] = count;
         c2[i][j] = count;
      }

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
