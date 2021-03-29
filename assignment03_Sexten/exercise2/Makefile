CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -g -O3

.PHONY: all
all: ex2 ex2_opt reduction

.PHONY: clean
clean:
	$(RM) ex2 ex2_opt reduction

ex2: ex2.c
ex2_opt: ex2_opt.c
reduction: reduction.c
