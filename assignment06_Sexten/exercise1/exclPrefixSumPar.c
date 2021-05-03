#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


int32_t * prefixSum(int32_t* arr, int32_t n, int32_t* arrHelp){
    int numOfThreads;
    arr[0] = 0;
    #pragma omp parallel
    {
        numOfThreads = omp_get_num_threads();
        int32_t blocksize = n/omp_get_num_threads();
        int start = blocksize * (omp_get_thread_num());
        int end = start + blocksize -1;
        for(int j = start +1; j <= end ;j++){
            arr[j] = arr[j-1] + arr[j];
        }
        arrHelp[omp_get_thread_num()] = arr[end];
    }
    for(int i = 1; i < numOfThreads; i++){
        arrHelp[i] = arrHelp[i-1] + arrHelp[i];
    }
    
    #pragma omp parallel
    {
        int32_t blocksize = n/omp_get_num_threads();
        int start = blocksize * (omp_get_thread_num());
        int end = start + blocksize -1;
        for(int j = start; j <= end ;j++){
            arr[j] = arr[j] + arrHelp[omp_get_thread_num()-1];
        }
    }        
       return arr;
    }




int32_t* init(int32_t size){
    
    int32_t* array = (int32_t *) malloc(size * sizeof(int32_t));
    for(int32_t i = 0 ; i < size; i++){
        array[i] = 1;
    }
    return array;
}

int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("\nPlease pass the size of array as commandline parameter\n");
        exit(-1);
    }
    int N = atoi(argv[1]);
    int32_t* arr = init(N);
    int32_t* b = init(N);
    double startTime = omp_get_wtime();
    int32_t* result = prefixSum(arr,N,b);
    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime-startTime);
    printf("%d\n",result[N-1]);
    free(arr);
    free(b);


return EXIT_SUCCESS; 
} 