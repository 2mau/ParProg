CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp

.PHONY: all
all: montecarlo_reduction montecarlo_atomic montecarlo_critical

.PHONY: clean
clean:
	$(RM) montecarlo_reduction montecarlo_atomic montecarlo_critical

montecarlo_critical: montecarlo_critical.c
montecarlo_atomic: montecarlo_atomic.c
montecarlo_reduction: montecarlo_reduction.c
