// Algorithm from https://gist.github.com/rohit-nsit08/1183731

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 8

int sol = 0;

void printsol(int *arr) {
	int i, j;
	char crossboard[N][N];
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			crossboard[i][j] = '_';
		}
	}
	for(i = 0; i < N; i++) {
		crossboard[i][arr[i]] = 'q';
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%c ", crossboard[i][j]);
		}
		printf("\n");
	}
}

int check(int* arr, int row) {
  for(int j = 0; j < row; j++){
      if(arr[row] == arr[j]){
        return 0;
      }
      if(abs(arr[row] - arr[j]) == (row - j)){
        return 0;
      }
  }
  return 1;
}

int solve(int* arr, int row) {
	for(int column = 0; column < N; column++) {
		arr[row] = column;
		if(check(arr, row)) {
			if(row == N - 1) {
        		#pragma omp atomic
          			sol++;
			} else {
				solve(arr, row + 1);
			}
		}
	}
  return sol;
}

void queens() {
  #pragma omp parallel for
  for(int i = 0; i < N; i++){
    int *arr = malloc(sizeof(int)*N);
    for(int i = 1; i < N; i++){
      arr[i] = -1;
    }
	arr[0] = i; 
    solve(arr, 1);
  }
  printf("Count %d\n", sol);
}

int main() {
	double startTime;
	double endTime;
	startTime = omp_get_wtime();
	queens();
	endTime = omp_get_wtime();
	printf("time: %f\n", endTime - startTime);
	return 0;
}