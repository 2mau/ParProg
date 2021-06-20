#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// allows the user to specify the problem size at compile time
#ifndef N
        #define N 3
#endif

#define IND(x, y) (y * N + x)


void printMatrix(double* m) {

        for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                        printf("%.1f ", m[IND(i,j)]);
                }
                printf("\n");
        }
        printf("\n");
}


int main() {

    // This benchmark is computing the symmetric rank k operation
    //              B = A * A^T + B
    // where A is a upper triangular and unit (1 along the diagonal)

    double* A = aligned_alloc(32,sizeof(double) * N * N);
    double* B = aligned_alloc(32,sizeof(double) * N * N);
    double* C = aligned_alloc(32,sizeof(double) * N * N);

    // initialize matrices
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            A[IND(i,j)] = (i==j)?1:0;
            B[IND(i,j)] = i*j;
            C[IND(i,j)] = 0;
        }
    }

    printf("A:\n"); printMatrix(A);
   printf("B:\n"); printMatrix(B);

    double timeStart = omp_get_wtime();

    // conduct multiplication
    long i = 0;
    long j = 0;
    long k = 0;
#pragma omp parallel for shared(A,B,C) private (i,j,k) 
    for ( i = 0; i < N; ++i) {
        for ( j = 0; j < N; ++j) {
            #pragma omp simd aligned(A,B,C : 32)
            for ( k = 0; k < N; k+=2) {
                C[IND(i,j)] += A[IND(i,k)] * B[IND(k,j)];
                C[IND(i,j)] += A[IND(i,k+1)] * B[IND(k+1,j)];
            }
        }
    }



    double timeEnd = omp_get_wtime();

    printf("C:\n"); printMatrix(C);

    printf("time: %f\n", timeEnd-timeStart);

    free(A);
    free(B);
    free(C);

    return EXIT_SUCCESS;
}
