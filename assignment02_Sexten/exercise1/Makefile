CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3 -fopenmp

.PHONY: all
all: mandelbrot mandelbrot_parallel

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot.png
	$(RM) mandelbrot_parallel mandelbrot_parallel.png

mandelbrot: mandelbrot.c
mandelbrot_parallel: mandelbrot_parallel.c
