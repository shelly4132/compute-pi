#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{
    double pi = 0.0;
    double diff = 0.0;
    double error = 0.0;

    if (argc < 2) return -1;

    int N = atoi(argv[1]);

    // Baseline
    pi = compute_pi_baseline(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);


    // OpenMP with 2 threads
    pi = compute_pi_openmp(N, 2);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);


    // OpenMP with 4 threads
    pi = compute_pi_openmp(N, 4);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);


    // AVX SIMD
    compute_pi_avx(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf,", error);


    // AVX SIMD + Loop unrolling
    compute_pi_avx_unroll(N);
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf\n", error);

    return 0;
}
