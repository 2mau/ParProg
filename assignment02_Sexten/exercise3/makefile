CFLAGS = -std=gnu11 -Wall -Werror -Wextra -O3 -pthread

.PHONY: all
all: montecarlo_serial montecarlo_parallel

.PHONY: clean
clean:
	$(RM) montecarlo_serial montecarlo_parallel

montes: montecarlo_serial.c

montep: montecarlo_parallel.c
