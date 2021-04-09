CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -g -O3

.PHONY: all
all: mergesort mergesortPar

.PHONY: clean
clean:
	$(RM) mergesort mergesortPar

mergesort: mergesort.c
mergesortPar: mergesortPar.c

