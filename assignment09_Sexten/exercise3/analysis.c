
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <omp.h>
#include <string.h>
#include <stdbool.h>

#define A_INNER 4
#define A_OUTER 1000

void init(int arr[A_OUTER][A_INNER]){
  for (int i = 0; i < A_OUTER; ++i) {
      for (int j = 0; j < A_INNER; ++j) {
        arr[i][j]=0;
      }
  }
}

bool compare(int a[A_OUTER][A_INNER], int a2[A_OUTER][A_INNER]){
  for (int i = 0; i < A_OUTER; ++i) {
      for (int j = 0; j < A_INNER; ++j) {
        //printf("[%d][%d]: a = %2d, a2 = %2d\n", i, j, a[i][j], a2[i][j]);
        if (a[i][j] != a2[i][j]) {
          printf("error [%d][%d],    %d != %d\n", i, j, a[i][j], a2[i][j]);
          return false;
        }
      }
  }

  printf("correct!\n");
  return true;
}

void orig(int a[A_OUTER][A_INNER], int b){
  for (int i = 0; i < A_OUTER-2; ++i) {
    for (int j = 1; j < A_INNER; ++j) {
        a[i + 2][j - 1] = b * a[i][j] + 4;
    }
  }
}

void noOpt(int a[A_OUTER][A_INNER], int b){
  for (int i = 1; i < A_OUTER-1; ++i) {
    for (int j = 1; j < A_INNER; ++j) {
        printf("([%d][%d]) <- ([%d][%d]) | distance (%d, %d)\n", i+1, j-1, i-1, j, i,j);
        a[i + 1][j - 1] = b * a[i - 1][j] + 4;
    }
  }
}

void opt(int a[A_OUTER][A_INNER], int b, int c){
  int j;
  j = c-1;

  // calc all [x][c-1]
  #pragma omp parallel for shared(j)
  for (int i = 1; i < A_OUTER-1; i++){
    a[i + 1][j - 1] = b * a[i - 1][j] + 4;
  }

  if (c == 2) return;
  opt(a, b, c-1);
}

int main(){
  int a[A_OUTER][A_INNER];
  int a2[A_OUTER][A_INNER];
  int a3[A_OUTER][A_INNER];

  const int b = 3;

  init(a);
  init(a2);
  init(a3);

  orig(a, b);
  noOpt(a2, b);
  opt(a3, b, A_INNER);

  compare(a, a2);
  compare(a2, a3);
}
