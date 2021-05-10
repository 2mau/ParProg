#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define REPETITIONS 1000000

float* init(int size){
    float d = 2.0;
    float* array = (float *) malloc((size) * sizeof(float));
    for(int32_t i = 0 ; i < size; i++){
        if(i == 0){
            array[i] = 1;
        }
        else array[i] = i;
    }
    return array;
}

int main(int argc, char* argv[]){

if (argc != 2){
    printf("\nPlease pass the size of array as commandline parameter\n");
    exit(-1);
}

int size = atoi(argv[1]);
float* a = init(size);
float* b = init(size);
float* c = init(size);
double startTime = omp_get_wtime();
for(int run = 0; run < REPETITIONS; ++run) {
    for(int i = 0; i < size; ++i) {
        a[i] += b[i] * c[i];
    }
}
double endTime = omp_get_wtime();
printf("time: %2.4f seconds\n", endTime-startTime);

printf("%.4f, %.4f, %.4f \n",a[0],a[size/2],a[size-1]);

free(a);
free(b);
free(c);
return EXIT_SUCCESS;
}