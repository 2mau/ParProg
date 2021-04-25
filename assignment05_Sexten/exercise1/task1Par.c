#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n,int m)
{
if (n == 0 || m == 0) return 1;
int x, y,z;
#pragma omp task shared(x)
{
x = fib(m-1,n);
}
#pragma omp task shared(y)
{
y = fib(m-1,n-1);
}

z = fib(m,n-1);

#pragma omp taskwait
return x+y+z;
}

int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("\nPlease pass the size of array as commandline parameter\n");
        exit(-1);
    }
    int N = atoi(argv[1]);
    double startTime = omp_get_wtime();
    int paths = fib(N,N);
    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime-startTime);
    printf("Paths: %d\n",paths);


return EXIT_SUCCESS; 
} 

