#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "measurement.h"

double read_overhead(int num)
{
  unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
  uint64_t tstart, tend;
  uint64_t *results = (uint64_t *)malloc(num * sizeof(uint64_t));
  memset(results, 0, num * sizeof(uint64_t));

  for (int i = 0; i < num; i++)
  {
    asm volatile("cpuid\n\t"
                 "rdtsc\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

    asm volatile("rdtscp\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "cpuid\n\t"
                 : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

    tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
    tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
    results[i] = tend - tstart;
  }

  free(results);
  double avg = get_average(results, num);
  printf("Average: %f\n", avg);
  return avg;
}

double get_average(uint64_t *results, int length)
{
  uint64_t sum = 0;
  for (int i = 0; i < length; i++)
  {
    sum += results[i];
  }
  return (double)sum / length;
}