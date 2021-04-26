#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int SerialDelannoy(int m,int n){
    if(m  == 0 || n == 0){
        return 1;
    }
    else return SerialDelannoy(m-1,n) + SerialDelannoy(m-1,n-1)+SerialDelannoy(m,n-1);
}

int delannoy(int n,int m) {
    if (n == 0 || m == 0) return 1;
    if(n < 6|| m < 6) return SerialDelannoy(m,n);

    int x, y,z;
    
        #pragma omp task shared(x,y)
        {
        x = delannoy(m-1,n);
        y = delannoy(m-1,n-1);
            }



        z = delannoy(m,n-1);
    
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
    #pragma omp parallel
	{
    #pragma omp master
    delannoy(N,N);
    }
    double endTime = omp_get_wtime();
    printf("%2.4f\n", endTime-startTime);
    


return EXIT_SUCCESS; 
} 

