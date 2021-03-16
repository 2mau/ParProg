#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);

#pragma omp parallel
	{
		// printf("I am thread %d out of %d threads.\n", omp_get_thread_num(),
		// omp_get_num_threads());

#pragma omp for
		for(int Py = 0; Py < Y; Py++) {
			double cy = ((float)Py / Y) * 2 - 1;
			for(int Px = 0; Px < X; Px++) {
				double x = 0.0;
				double y = 0.0;
				int iteration = 0;
				double cx = ((float)Px / X) * 3.5 - 2.5;

				while(x * x + y * y <= 2 * 2 && iteration < MAX_ITER) {
					double x_tmp = x * x - y * y + cx;
					y = 2 * x * y + cy;
					x = x_tmp;
					iteration = iteration + 1;
				}

				double norm_iteration = ((double)iteration) / MAX_ITER * 255;
				image[Py][Px] = norm_iteration;
			}
		}
	}

	gettimeofday(&end, NULL);
	double elapsed_time = (end.tv_sec + end.tv_usec * 1e-6) - (start.tv_sec + start.tv_usec * 1e-6);
	printf("calculation took: %f seconds.\n", elapsed_time);
}

int main() {
	uint8_t image[Y][X];

	calc_mandelbrot(image);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}
