CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp

.PHONY: all
all: flush flush_o

.PHONY: clean
clean:
	$(RM) flush flush_o

flush: flush.c
flush_o: flush_o.c