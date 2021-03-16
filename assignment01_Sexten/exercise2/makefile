CFLAGS = -std=gnu11 -fopenmp -Wall -Werror -Wextra -O3

.PHONY: all
all: fast medium slow

.PHONY: clean
clean:
	$(RM) fast medium slow

fast: fast.c

medium: medium.c

slow: slow.c
