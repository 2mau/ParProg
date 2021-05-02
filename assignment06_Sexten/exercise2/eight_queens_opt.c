// Algorithm from https://gist.github.com/rohit-nsit08/1183731

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 12

int sol = 0;

void printsol(int* arr) {
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
	for(int j = 0; j < row; j++) {
		if(arr[row] == arr[j]) {
			return 0;
		}
		if(abs(arr[row] - arr[j]) == (row - j)) {
			return 0;
		}
	}
	return 1;
}

int solveSerial(int* arr, int row) {
	int count = 0;
	for(int column = 0; column < N; column++) {
		arr[row] = column;
		if(check(arr, row)) {
			if(row == N - 1) {
				count++;
#pragma omp atomic
				sol++;
			} else {
				count += solveSerial(arr, row + 1);
			}
		}
	}
	return count;
}

int solve(int* arr, int row) {
	int count = 0;
	if(row > 3) {
		count += solveSerial(arr, row);
	} else {
#pragma omp parallel for
		for(int column = 0; column < N; column++) {
			int* newArr = malloc(sizeof(int) * N);
			memcpy(newArr, arr, sizeof(int) * N);
			newArr[row] = column;
			if(check(newArr, row)) {
				if(row == N - 1) {
					#pragma omp atomic
					count++;
					#pragma omp atomic
					sol++;
				} else {
					#pragma omp atomic
					count += solve(newArr, row + 1);
				}
			}
			free(newArr);
		}
	}
	return count;
}

void queens() {
	int* arr = malloc(sizeof(int) * N);
	for(int i = 1; i < N; i++) {
		arr[i] = -1;
	}
	int count = 0;
	count = solve(arr, 0);
	free(arr);
	printf("Count %d\n", count);
	printf("Sol %d\n", sol);
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