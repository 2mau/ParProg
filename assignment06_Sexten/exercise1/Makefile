CFLAGS = -std=gnu11  -Wextra  -O3 -fopenmp 

.PHONY: all
all: exclPrefixSumSeq exclPrefixSumPar

.PHONY: clean
clean:
	$(RM) exclPrefixSumSeq exclPrefixSumPar

exclPrefixSumSeq: exclPrefixSumSeq.c

exclPrefixSumPar: exclPrefixSumPar.c -lm
