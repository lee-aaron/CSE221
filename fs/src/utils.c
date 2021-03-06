#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "utils.h"

static unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
uint64_t tstart, tend;

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

void write_to_file(const char *filename, uintmax_t total, uint64_t size)
{
  char location[256] = "./src/results/";
  strncat(location, filename, strlen(filename));

  FILE *fp = fopen(location, "a");
  if (NULL != fp)
  {
    fprintf(fp, "%2ld %ld\n", size, total);
    fclose(fp);
  }
}

void create_file(const char *filename, uint64_t size)
{
  FILE *fp = fopen(filename, "a");
  if (fp != NULL)
  {
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) != 0)
    {
      fclose(fp);
      return;
    }
    fclose(fp);
  }

  fp = fopen(filename, "w");
  if (fp == NULL)
  {
    perror("fopen");
    exit(1);
  }
  fseek(fp, size * 1024 * 1024 * 1024 - 1, SEEK_SET);
  fputc('\0', fp);
  fclose(fp);
}

void create_file_kb(const char *filename, uint64_t size)
{
  FILE *fp = fopen(filename, "a");
  if (fp != NULL)
  {
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) != 0)
    {
      fclose(fp);
      return;
    }
    fclose(fp);
  }

  fp = fopen(filename, "w");
  if (fp == NULL)
  {
    perror("fopen");
    exit(1);
  }
  fseek(fp, size * 8192 - 1, SEEK_SET);
  fputc('\0', fp);
  fclose(fp);
}

void clear_cache() {
#if __APPLE__
  system("sync; sudo purge");
#else
  system("sync; echo 3 > /proc/sys/vm/drop_caches");
#endif
}
