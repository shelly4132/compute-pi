#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 25;
    double time;
    double min, max;
    double sum = 0.0;

    FILE *fp = fopen("ci.txt", "r");


    // Baseline
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_baseline(N);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i--;
    }
    printf("%lf,", sum/(double)SAMPLE_SIZE);
    sum = 0.0;

    // OpenMP with 2 threads
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_openmp(N, 2);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i--;
    }
    printf("%lf,", sum/(double)SAMPLE_SIZE);
    sum = 0.0;


    // OpenMP with 4 threads
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_openmp(N, 4);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i--;
    }
    printf("%lf,", sum/(double)SAMPLE_SIZE);
    sum = 0.0;


    // AVX SIMD
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_avx(N);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i--;
    }
    printf("%lf,", sum/(double)SAMPLE_SIZE);
    sum = 0.0;


    // AVX SIMD + Loop unrolling
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_avx_unroll(N);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i--;
    }
    printf("%lf,", sum/(double)SAMPLE_SIZE);
    sum = 0.0;


/*    //Euler
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_euler(N);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i -= 1;
    }
    printf("%lf\n", sum/(double)SAMPLE_SIZE);
    sum = 0.0;
*/

    //Leibniz
    fscanf(fp, "%lf %lf", &min, &max);
    for(i = 0; i < loop; i++) {
        clock_gettime(CLOCK_ID, &start);
        compute_pi_leibniz(N);
        clock_gettime(CLOCK_ID, &end);
        time = (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ONE_SEC;
        if(time >= min && time <= max)
            sum += time;
        else
            i--;
    }
    printf("%lf\n", sum/(double)SAMPLE_SIZE);
    sum = 0.0;


    return 0;
}
