# Assignment 9 for May 25th, 2021


## Exercise 1 (1 Point)

### Description

Consider the following individual code snippets, and analyze them regarding dependencies. 


````
for (int i=0; i < n-1; i++) {
    x[i] = (y[i] + x[i+1]) / 7;
}
````

````
for (int i=0; i < n; i++) {
    a = (x[i] + y[i]) / (i+1);
    z[i] = a;
}

f = sqrt(a + k);

````

````
for (int i=0; i < n; i++) {
   x[i] = y[i] * 2 + b * i;
}


for (int i=0; i < n; i++) {
   y[i] = x[i]  + a / (i+1);
}
````


### Tasks
Regarding each snippet
- What are the data dependencies?
- Parallelize and optimize the code


## Exercise 2 (1 Point)

### Description

In this exercise we try to parallelize loops which have data dependencies.
Look at the following individual code snippets.
a)
````

double factor = 1;

for (int i=0; i < n; i++) {
    x[i] = factor * y[i];
    factor = factor / 2;
}
````
b)
````
for (int i = 1; i<n; i++) {
    x[i] = (x[i] + y[i-1]) / 2;
    y[i] = y[i] + z[i] * 3;
}

````
c)

````
x[0] = x[0] + 5 * y[0];
for (int i = 1; i<n; i++) {
    x[i] = x[i] + 5 * y[i];
    if ( twice ) {
        x[i-1] = 2 * x[i-1]
    }
}

````

### Tasks

- Where are the data dependencies?
- How can you parallelize the loops?
- Implement the original and parallelized versions and compare their wall time for reasonable sizes and numbers of threads.


## Exercise 3 (1 Point)

### Description

````
for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < 4; ++j) {
        a[i + 2][j - 1] = b * a[i][j] + 4;
    }
}
````

### Tasks 
- What type of dependence is represented in this code snippet?

| write <- read        |  iteration  | dependencies read | dependencies write |
|----------------------|-------------|-------------------|--------------------|
| ([2][0]) <- ([0][1]) | iter (1, 1) | x | x |
| ([2][1]) <- ([0][2]) | iter (1, 2) |            | x write 2,1 |
| ([2][2]) <- ([0][3]) | iter (1, 3) |            | y write 2,2 |
| ([3][0]) <- ([1][1]) | iter (2, 1) |            | |
| ([3][1]) <- ([1][2]) | iter (2, 2) |            | z write 3,1 |
| ([3][2]) <- ([1][3]) | iter (2, 3) |            | p write 3,2 |
| ([4][0]) <- ([2][1]) | iter (3, 1) | x read 2,1 | |
| ([4][1]) <- ([2][2]) | iter (3, 2) | y read 2,2 | write 4,1 |
| ([4][2]) <- ([2][3]) | iter (3, 3) |            | write 4,2 |
| ([5][0]) <- ([3][1]) | iter (4, 1) | z read 3,1 | |
| ([5][1]) <- ([3][2]) | iter (4, 2) | p read 3,2 | write 5,1 |
| ([5][2]) <- ([3][3]) | iter (4, 3) |            | write 5,2 |
| ([6][0]) <- ([4][1]) | iter (5, 1) | read 4,1   | |
| ([6][1]) <- ([4][2]) | iter (5, 2) | read 4,2   | write 6,1 |
| ([6][2]) <- ([4][3]) | iter (5, 3) |            | write 6,2 |
| ([7][0]) <- ([5][1]) | iter (6, 1) | read 5,1   | |
| ([7][1]) <- ([5][2]) | iter (6, 2) | read 5,2   | write 7,1 |
| ([7][2]) <- ([5][3]) | iter (6, 3) |            | write 7,2 |
| ([8][0]) <- ([6][1]) | iter (7, 1) | read 6,1   | |
| ([8][1]) <- ([6][2]) | iter (7, 2) | read 6,2   | write 8,1 |
| ([8][2]) <- ([6][3]) | iter (7, 3) |            | write 8,2 |


- For each iteration, give the corresponding distance and direction vectors
```
x,y,z true dependencies
x: distance vector [source = (1,2), sink = (3,1)]: (2,1), direction vector (<, =)
y: distance vector [source = (1,3), sink = (3,2)]: (2,1), direction vector (<, =)
z: distance vector [source = (2,2), sink = (4,1)]: (2,1), direction vector (<, =)
p: distance vector [source = (2,3), sink = (4,2)]: (2,1), direction vector (<, =)
```

- How would you parallelize this code? 
    ([even][x]): can be calculated by one thread  
    ([odd][x]): can be calculated by one thread  
    inner loop could be parallelized  
    or  
    compute [x][2] -> [x][1] -> [x][0] all steps alone can be easily parallelized

## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
