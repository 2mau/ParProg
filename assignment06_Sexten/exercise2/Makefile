CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -g -O3

.PHONY: all
all: eight_queens eight_queens_par eight_queens_opt

.PHONY: clean
clean:
	$(RM) eight_queens eight_queens_par eight_queens_opt

ex3: eight_queens.c eight_queens_par.c eight_queens_opt.c
