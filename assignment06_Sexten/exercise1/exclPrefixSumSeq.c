#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int32_t * prefixSum(int32_t* arr, int32_t n, int32_t* b){
    b[0] = 0;
    for(int32_t i = 1; i < n; i++) {
        b[i] = b[i - 1] + arr[i + 1];
    }
    return b;
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