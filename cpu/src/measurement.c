#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "measurement.h"
#include "utils.h"

double loop_avg(double* results, int num)
{
  double avg = 0;
  for (int i = 0; i < num; i++)
  {
    avg += results[i];
  }
  avg /= num;
  return avg;
}

double loop_sd(double* results, int num)
{
  double avg = loop_avg(results, num);
  double sd = 0;
  for (int i = 0; i < num; i++)
  {
    sd += pow(results[i] - avg, 2);
  }
  sd /= num;
  sd = sqrt(sd);
  return sd;
}

double read_overhead(int num)
{
  char filename[] = "read_overhead.txt";
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

  double avg = get_average(results, num);
  printf("Average Read Overhead: %f\n", avg);
  printf("Standard Deviation for Read Overhead: %f\n", get_sd(results, num));
  write_to_file(filename, results, num);
  free(results);
  return avg;
}

double loop_overhead(int num)
{
  char filename[] = "loop_overhead.txt";
  delete_file(filename);
  unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
  uint64_t tstart, tend;
  double *results = (double *)malloc(num * sizeof(double));
  memset(results, 0, num * sizeof(double));

  for (int i = 0; i < num; i++)
  {
    asm volatile("cpuid\n\t"
                 "rdtsc\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

    for (int j = 0; j < num; j++)
    {
    }

    asm volatile("rdtscp\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "cpuid\n\t"
                 : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

    tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
    tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
    double avg = (double) (tend - tstart) / (double) num;
    results[i] = avg;
    append_to_file(filename, avg);
  }
  
  double avg = loop_avg(results, num);
  printf("Average Loop Overhead: %f\n", avg);
  printf("Standard Deviation for Loop Overhead: %f\n", loop_sd(results, num));
  return 0;
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

double get_sd(uint64_t *results, int length)
{
  double avg = get_average(results, length);
  double sd = 0.0;
  for (int i = 0; i < length; i++)
  {
    sd += pow(results[i] - avg, 2);
  }
  sd /= length;
  return sqrt(sd);
}