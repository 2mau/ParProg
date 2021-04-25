CFLAGS = -std=gnu11 -Wall -Wextra  -O3 -fopenmp

.PHONY: all
all: task1 task1Par

.PHONY: clean
clean:
	$(RM) task1 task1Par

threadAffinity: task1.c
task1Par : task1Par.c