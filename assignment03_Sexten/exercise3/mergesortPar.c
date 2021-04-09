#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



int main(int argc, char** argv){
    if (argc != 2){
        printf("\nPlease pass the size of array as commandline parameter\n");
        exit(-1);
    }
    int32_t size = atoi(argv[1]);




    return EXIT_SUCCESS;
}