#ifndef MEASUREMENT
#define MEASUREMENT
#include <stdint.h>

double get_average(double *results, int num);
double get_sd(double *results, int num);
double read_overhead(int num, double cps);
double loop_overhead(int num, double cps);

#endif
