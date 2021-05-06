CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -g -O1

.PHONY: all
all: simd simd_db

.PHONY: clean
clean:
	$(RM) simd simd_db

simd: simd.c
simd_db: simd_db.c