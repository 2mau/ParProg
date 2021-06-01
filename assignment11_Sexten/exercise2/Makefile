CC=gcc
CC_FLAGS=-g -std=gnu11 -Wall -Wextra -O3


.PHONEY: all
all: a

SRC=$(wildcard *.c)

a: $(SRC)
	@$(CC) $(CC_FLAGS) $(SRC)

.PHONEY: clean
clean:
	@rm a

.PHONEY: run
run: all
	@echo "all:"
	@./a
	@echo
