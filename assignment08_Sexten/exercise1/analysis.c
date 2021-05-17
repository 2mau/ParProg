#include <stdio.h>

#define SIZE 1024

int main(int argc, char** argv) {

        int a[SIZE];
        int b[SIZE];

        // vectozied
        for(int i = 0; i < SIZE; ++i) {
                a[i] = argc;
        }

        // vectozied
        for(int i = 0; i < SIZE; ++i) {
                b[i] = a[i];
        }

        // vectozied
        for(int i = 4; i < SIZE; ++i) {
                a[i-4] = a[i];
        }

        /*
        analysis.c:22: note: ===== analyze_loop_nest =====
        analysis.c:22: note: === vect_analyze_loop_form ===
        analysis.c:22: note: === get_loop_niters ===
        analysis.c:22: note: ==> get_loop_niters:1022
        analysis.c:22: note: === vect_analyze_data_refs ===

        analysis.c:22: note: get vectype with 4 units of type int
        analysis.c:22: note: vectype: vector(4) int
        analysis.c:22: note: not vectorized: not suitable for gather load _25 = a[_24];

        analysis.c:22: note: bad data references.
        data not aligned? (gather load)
        */
        for(int i = 1; i < SIZE-1; ++i) {
                a[i] = a[i%argc];
        }

        /*
        analysis.c:27: note: ===== analyze_loop_nest =====
        analysis.c:27: note: === vect_analyze_loop_form ===
        analysis.c:27: note: === get_loop_niters ===
        analysis.c:27: note: ==> get_loop_niters:1024
        analysis.c:27: note: === vect_analyze_data_refs ===

        analysis.c:27: note: not vectorized: loop contains function calls or data references that cannot be analyzed
        analysis.c:27: note: bad data references.
        */
        // output data to prevent compiler from removing any code
        for(int i = 0; i < SIZE; ++i) {
                printf("%d ", a[i]);
                printf("%d ", b[i]);
        }
        printf("\n");

        return 0;
}
