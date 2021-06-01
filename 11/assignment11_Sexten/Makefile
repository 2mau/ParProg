CC=gcc
CC_FLAGS=-g -std=gnu11 -Wall -Wextra -O3


.PHONEY: all
all: a

SRC=$(wildcard *.c)

real: $(SRC)
	@$(CC) $(CC_FLAGS) $(SRC) -o real

.PHONEY: clean
clean:
	@rm a

.PHONEY: run
run: all
	@echo "all:"
	@./a
	@echo
