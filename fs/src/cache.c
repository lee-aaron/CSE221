#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"
#include "cache.h"

#define BLOCKSIZE 4096

void cache_size(const char *filename, uint64_t size)
{
#if __APPLE__
  system("sync; sudo purge");
#else
  system("sync; echo 3 > /proc/sys/vm/drop_caches");
#endif

  int fd = open(filename, O_RDONLY);
  if (fd < 0)
  {
    perror("open");
    exit(1);
  }

  char *buf = (char *)malloc(BLOCKSIZE);
  uintmax_t count = (size * 1024 * 1024 * 1024 - 1) / BLOCKSIZE;

  for (uintmax_t i = 0; i < count; i++)
  {
    if (read(fd, buf, BLOCKSIZE) <= 0)
    {
      perror("initial read");
      exit(1);
    }
  }

  close(fd);

  uintmax_t total = 0;
  fd = open(filename, O_RDONLY);
  if (fd < 0)
  {
    perror("open");
    exit(1);
  }

  for (uintmax_t i = 0; i < count; i++)
  {
    read_start();
    uint64_t read_bytes = read(fd, buf, BLOCKSIZE);
    read_end();
    if (read_bytes <= 0)
    {
      perror("second read");
      exit(1);
    }
    total += tend - tstart;
  }

  close(fd);
  free(buf);
  char file[] = "cache.txt";
  write_to_file(file, total, size);
}

void create_file(const char *filename, uint64_t size)
{
  FILE *fp = fopen(filename, "r");
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

void init_test(char filenames[10][1024])
{
  int ARRAY_SIZE = 10;
  uint64_t size[ARRAY_SIZE];
  for (int i = 1; i <= ARRAY_SIZE; i++)
  {
    size[i - 1] = i;
    create_file(filenames[i - 1], i);
  }

  delete_file("cache.txt");

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    cache_size(filenames[i], size[i]);
  }
}