#include <stdio.h>

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0
#define SAMPLE_SIZE 25

double compute_pi_baseline(size_t N);
double compute_pi_openmp(size_t N, int threads);
double compute_pi_avx(size_t N);
double compute_pi_avx_unroll(size_t N);
double compute_pi_euler(size_t N);
double compute_pi_leibniz(size_t N);
double compute_ci(double *min, double *max, double data[SAMPLE_SIZE]);

