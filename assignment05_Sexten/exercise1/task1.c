#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int delannoy(int m,int n){
    if(m  == 0 || n == 0){
        return 1;
    }
    else return delannoy(m-1,n) + delannoy(m-1,n-1)+delannoy(m,n-1);
}

int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("\nPlease pass the size of array as commandline parameter\n");
        exit(-1);
    }
    int N = atoi(argv[1]);
    double startTime = omp_get_wtime();
    int paths = delannoy(N,N);
    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime-startTime);
    printf("Paths: %d\n",paths);


return EXIT_SUCCESS; 
} 