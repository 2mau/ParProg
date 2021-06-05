#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

void a(unsigned c1) {
    unsigned c2 = 32 * c1;
    printf("a): %u\n", c2);
}

void a_solution(unsigned c1) {
    // Assembly looks the same probably because of optimizations.
    unsigned c2 = c1 << 5;
    printf("a)*: %u\n", c2);
}

void b(unsigned c1) {
    unsigned c2 = 15 * c1;
    printf("b): %u\n", c2);
}

void b_solution(unsigned c1) {
   // Assembly looks the same probably because of optimizations.
    unsigned c2 =  (c1<<4) - c1;
    printf("b*): %u\n", c2);
}

void c(unsigned c1) {
    unsigned c2 = 96 * c1;
    printf("c): %u\n", c2);
}

void c_solution(unsigned c1) {
    // Works if one addition and two shifts are more effective than a single multiplication (on local machine it is faster)
    // Interesting is that it uses imul and doesnt need a lea instruction ? which makes it faster
    unsigned c2 = (c1 << 6) + (c1 << 5);
    printf("c*): %u\n", c2);
}

void d(unsigned c1) {
    // uses mulsd and preforms a transformation back to unsigned 
    unsigned c2 = 0.125 * c1;
    printf("d): %u\n", c2);
}

void d_solution(unsigned c1) {
    // always faster because of shift
    unsigned c2 =  c1 >> 3;
    printf("d*): %u\n", c2);
}

void e(unsigned *a) {
    // uses two adds
    unsigned sum_fifth = 0;
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[5 * i];
    }
    printf("e): %u\n", sum_fifth);
}

void e_solution(unsigned *a) {
    // Uses SIMD add for the sum and uses registers (pxor) and movd. It is interesting that the original might be also stored in memory. 
    unsigned T = 0;
    unsigned sum_fifth = 0;
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[T];
        T += 5;
    }
    printf("e*): %u\n", sum_fifth);
}


void f(double *a) {
    for (int i = 0; i < N; ++i) {
        a[i] += i / 5.3;
    }
   printf("f):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}

void f_solution(double *a) {
    // inverse multiplication with an intersting artifact. Seems to be in registers
    double T = 1/5.3;
    for (int i = 0; i < N; ++i) {
        a[i] += (i * T);
    }
    
    printf("f*):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}
//original time: 0.000665
//     new time: 0.000494

void g(float c1) {
    //xorps 
    float c2 = -1 * c1;
    printf("g): %f\n", c2);
}


void g_solution(float c1) {
    // Should not be really done because of portability issues and violation of aliasing rules. it uses a single or which seems to be less overhead
    *(int*)&c1 |= 0x80000000;
    float c2 = c1;
    printf("g*): %f\n", c2);
}

int main(void) {
    return EXIT_SUCCESS;
}
