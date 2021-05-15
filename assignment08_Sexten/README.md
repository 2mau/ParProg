# Assignment 8 for May 18th, 2021

The goal of this assignment is to work with data and control dependencies.

## Exercise 1 (1 Point)

### Description

Consider the following, individual code examples in the context of dependence analysis, race conditions, and parallelization:

```C
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
}
```

```C
a[0] = 0;
#pragma omp parallel
{
    #pragma omp for nowait
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
}
```

```C
#pragma omp parallel for
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```

```C
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++) {
    x = f * b[i];
    a[i] = x - 7;
}
a[0] = x; 
```
```C
sum = 0; 
#pragma omp parallel for
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```

### Tasks

- For each example, investigate whether it is parallelized correctly or whether there are any dependencies, and how any potential parallelization mistakes can be solved while keeping the parallelism. Are there multiple solutions and if so, what are their advantages and disadvantages?

## Exercise 2 (1 Point)

### Description

- Compilers often perform dependence analysis as a pre-step in order to safely perform optimizations such as vectorization in a second step. In this exercise, we will look at the first step only, namely compiler capabilities and reporting.

### Tasks
Compile the given program [analysis.c](analysis.c) with gcc 8.2.0 and the flags `-O2 -ftree-vectorize -fopt-info-vec-all`.

- -ftree-vectorize
  - Perform vectorization on trees. This flag enables -ftree-loop-vectorize and -ftree-slp-vectorize if not explicitly specified.
- -fopt-info-vec-all`
  - Enable dumps from all vectorization optimizations

Examine the output. 
- What information about dependence analysis can you find in the output?
- Can you identify any information pointing to successful or unsuccessful vectorization?
- Does the compiler perform any analysis beyond checking for dependencies and semantic correctness?

## Exercise 3 (1 Point)

### Description

Investigate the following given code examples along with their task.

### Tasks

- Investigate the given code excerpt. Can this code be safely parallelized manually? Can this code be safely parallelized by the compiler?
    ```C
    void copy(double* x, double* y) {
        for(int i = 0; i < 1024; i++) {
            x[i] = y[i];
        }
    }
    ```

Can be parallelized by the compiler and manually. There is no data dependence between x and y, also there is obviously no control dependence.

- Normalize the following loop nest:
    ```C
    for (int i=4; i<=N; i+=7) {
        for (int j=0; j<=N; j+=3) {
            A[i] = 0;
        }
    }
    ```

In this specific case one could just remove the inner loop since it is doing the same operation (with no side effects) over and over again.
```C
for(int In = 1; In <= (N-4+7)/7; In++){
    A[In*7-7+4]
}
```

For completeness here also the Inner Loop is normalized

```C
for(int In = 1; In <= (N-4+7)/7; In++){
    for(int Jn = 1; Jn <= (N-0+3)/3; Jn++){
        A[In*7-7+4]
    }
}
```
- Does the following code excerpt hold any dependencies? If not, how would you parallelize it? If yes, what are the distance and direction vectors?
    ```C
    for(int i = 1; i < N; i++) {
        for(int j = 1; j < M; j++) {
            for(int k = 1; k < L; k++) {
                a[i+1][j][k-1] = a[i][j][k] + 5;
            }
        }
    }
    ```
There is the True Dependency a[i].

For a[2][1][1]; S1[1][1][2] $\delta$ S1[2][1][1]
For a[3][1][1]; S1[2][1][2] $\delta$ S1[3][1][1]
...
...
For a[N-1][M][L-2]; S1[N-2][M][L-1] $\delta$ S1[N-1][M][L-2]
Distance Vector (1,0,-1) = S1[N-1][M][L-2] - S1[N-2][M][L-1]
Direction Vector (<,=,>)

Regardless of the dependencies parallelizing the second for loop would still work since the dependency is only loop carried over the first and third loop.

## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
