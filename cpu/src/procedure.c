#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "procedure.h"
#include "measurement.h"
#include "utils.h"

void func0() {}
void func1(int a) {}
void func2(int a, int b) {}
void func3(int a, int b, int c) {}
void func4(int a, int b, int c, int d) {}
void func5(int a, int b, int c, int d, int e) {}
void func6(int a, int b, int c, int d, int e, int f) {}
void func7(int a, int b, int c, int d, int e, int f, int g) {}

double procedure_overhead(int num, int args)
{
  char filename[21];
  snprintf(filename, 21, "read_procedure_%d.txt", args);
  unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
  uint64_t tstart, tend;
  uint64_t *results = (uint64_t *)malloc(num * sizeof(uint64_t));
  memset(results, 0, num * sizeof(uint64_t));

  switch (args)
  {
  case 0:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func0();

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 1:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func1(0);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 2:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func2(0, 1);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 3:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func3(0, 1, 2);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 4:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func4(0, 1, 2, 3);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 5:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func5(0, 1, 2, 3, 4);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 6:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func6(0, 1, 2, 3, 4, 5);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  case 7:
    for (int i = 0; i < num; i++)
    {
      asm volatile("cpuid\n\t"
                   "rdtsc\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

      func7(0, 1, 2, 3, 4, 5, 6);

      asm volatile("rdtscp\n\t"
                   "mov %%edx, %0\n\t"
                   "mov %%eax, %1\n\t"
                   "cpuid\n\t"
                   : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

      tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
      tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
      results[i] = tend - tstart;
    }
    break;
  default:
    printf("Please specify a number from 0-7 to test.\n");
    return 0;
  }

  double avg = get_average(results, num);
  printf("Arguments: %d\n", args);
  printf("Average Procedure Overhead: %f\n", avg);
  printf("Standard Deviation: %f\n", get_sd(results, num));
  write_to_file(filename, results, num);
  free(results);
  return avg;
}
