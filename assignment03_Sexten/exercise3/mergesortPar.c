//Copyright for iterative merge sort: https://www.geeksforgeeks.org/iterative-merge-sort/
//Modifications: allocated arrays due to size, random init, test for sort, datatypes

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>
int32_t size;

/* Iterative C program for merge sort */
#include<stdlib.h>
#include<stdio.h>
 
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r);
 
// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }
 
 
/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int32_t arr[], int32_t n)
{
   int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
   int left_start; // For picking starting index of left subarray
                   // to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       #pragma omp parallel for num_threads(1)
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting
           // point of right
           int mid = min(left_start + curr_size - 1, n-1);
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           merge(arr, left_start, mid, right_end);
       }
   }
}


 
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int32_t arr[], int32_t l, int32_t m, int32_t r)
{
    int32_t i, j, k;
    int32_t n1 = m - l + 1;
    int32_t n2 =  r - m;
 
    /* create temp arrays */
    int32_t* L = (int32_t *) malloc(n1 * sizeof(int32_t));
    int32_t* R = (int32_t *) malloc(n2 * sizeof(int32_t));
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1+ j];
    }
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    for (;i < n1;i++, k++)
    {
        arr[k] = L[i];
    }
 
    /* Copy the remaining elements of R[], if there are any */
    for (;j < n2;j++,k++)
    {
        arr[k] = R[j];
    }
    free(L);
    free(R);
}

int32_t* initWithRandom(int32_t size){
    unsigned int seed = (unsigned int ) time(NULL); 
    int32_t* array = (int32_t *) malloc(size * sizeof(int32_t));
    for(int32_t i = 0 ; i < size; i++){
        array[i] = rand_r(&seed);
    }
    return array;
}

void printArray(int32_t A[], int32_t size)
{
    int32_t i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int32_t isArraySorted(int32_t* s, int32_t n) {
  int j = 1, k = 1, i = 0;

  while ((j == 1 || k == 1) && i < n - 1) {
    if (s[i] > s[i+1]){
      j = 0;
    }
    i++;
  }

  if (j == 1)
    return 1;
  else
    return 0;
}

int main(int argc, char** argv){
    if (argc <= 1){
        printf("\nPlease pass the size of array as commandline parameter\n");
        exit(-1);
    }
    size = atoi(argv[1]);
    int32_t* array = initWithRandom(size);
    double start_time = omp_get_wtime();
    mergeSort(array,size);
    double end_time = omp_get_wtime();
	printf("Time: %2.2f seconds\n", end_time - start_time);
   // printArray(array,size);
    int r = isArraySorted(array,size);
    if(r == 1){
        printf("Succesfully sorted\n");
    }
    else printf("Sort failed\n");
    free(array);

    return EXIT_SUCCESS;
}