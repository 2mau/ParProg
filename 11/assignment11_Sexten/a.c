#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 1000000

int a[N];
int b[N];

// Assume N is odd

void original(){
  for (int i = 0; i < N - 1; ++i) {
      a[i] = b[i] + b[i + 1];
  }
}

void trans(){
  for (int i = 0; i < N - 1; ++i) {
      a[i] = b[i] + b[i + 1];
      a[i+1] = b[i+1] + b[i + 1 + 1];
  }
}

void init(){
  a = calloc(N, sizeof(int))
  b = calloc(N, sizeof(int))
}

int main(){
  init();
  original();
  trans();
}
