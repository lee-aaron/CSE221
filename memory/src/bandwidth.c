#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

#define CACHELINE_SIZE 64
#define STRIDE (CACHELINE_SIZE / sizeof(int))
#define ARRAY_LEN (1 << 28)

void read_bandwidth(int num, double cps) {
    double results[num];

    for (int i = 0; i < num; i++) {
        int *arr = (int *)malloc(sizeof(int) * ARRAY_LEN);
        int sum = 0;
        read_start();
        for (int j = 0; j < ARRAY_LEN; j += STRIDE) {
            sum += arr[j];
        }
        read_end();
        free(arr);
        double bandwidth = ARRAY_LEN * sizeof(int) / ((tend - tstart) / cps);
        results[i] = bandwidth / 1e9;  // in GB/s
    }
    write_to_file_d("read_bandwidth.txt", results, num);
}

void write_bandwidth(int num, double cps) {
    double results[num];

    for (int i = 0; i < num; i++) {
        int *arr = (int *)malloc(sizeof(int) * ARRAY_LEN);
        read_start();
        for (int j = 0; j < ARRAY_LEN; j += STRIDE) {
            arr[j] = 1;
        }
        read_end();
        free(arr);
        double bandwidth = ARRAY_LEN * sizeof(int) / ((tend - tstart) / cps);
        results[i] = bandwidth / 1e9;  // in GB/s
    }
    write_to_file_d("write_bandwidth.txt", results, num);
}
