#ifndef MEASUREMENT
#define MEASUREMENT
#include <stdint.h>

double get_average(uint64_t *results, int num);
double get_sd(uint64_t *results, int num);
double read_overhead(int num);
double loop_overhead(int num);

#endif
