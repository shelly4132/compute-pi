CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx
EXECUTABLE = \
	time_test_baseline time_test_openmp_2 time_test_openmp_4 \
	time_test_avx time_test_avxunroll time_test_euler \
	benchmark_clock_gettime error computeci

default: computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DEULER -o time_test_euler -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DLEIBNIZ -o time_test_leibniz -lm
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime -lm
	$(CC) $(CFLAGS) computepi.o error.c -o error -lm
	$(CC) $(CFLAGS) computepi.o computeci.c -o computeci -lm

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
	time ./time_test_avx
	time ./time_test_avxunroll
	time ./time_test_euler
	time ./time_test_leibniz

gencsv: default
	for i in `seq 100 50000 1000000`; do \
		printf "%d," $$i;\
		./computeci $$i; \
		./benchmark_clock_gettime $$i; \
	done > result_clock_gettime.csv	

plot: result_clock_gettime.csv
	gnuplot scripts/runtime.gp

errcsv:
	for i in `seq 100 5000 1000000`; do \
		printf "%d," $$i;\
		./error $$i; \
	done > result_error_rate.csv

plot2: result_error_rate.csv
	gnuplot scripts/error_rate.gp

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv result_error_rate.csv ci.txt
