#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "utils.h"

static unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
uint64_t tstart, tend;

void write_to_file(const char *filename, double *results, int length)
{
  char location[256] = "./src/results/";
  strncat(location, filename, strlen(filename));

  FILE *fp = fopen(location, "w");
  for (int i = 0; i < length; i++) {
    fprintf(fp, "%f\n", results[i]);
  }
  fclose(fp);
}

void append_to_file(const char *filename, double result)
{
  char location[256] = "./src/results/";
  strncat(location, filename, strlen(filename));

  FILE *fp = fopen(location, "a");
  fprintf(fp, "%f\n", result);
  fclose(fp);
}

void delete_file(const char *filename)
{
  char location[256] = "./src/results/";
  strncat(location, filename, strlen(filename));

  FILE *fp = fopen(location, "r");
  if (NULL != fp)
  {
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) > 0)
    {
      fclose(fp);
      remove(location);
    }
  }
}

void read_start()
{
  asm volatile("cpuid\n\t"
               "rdtsc\n\t"
               "mov %%edx, %0\n\t"
               "mov %%eax, %1\n\t"
               : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");
  tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
}

void read_end()
{
  asm volatile("rdtscp\n\t"
               "mov %%edx, %0\n\t"
               "mov %%eax, %1\n\t"
               "cpuid\n\t"
               : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");
  tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
}
