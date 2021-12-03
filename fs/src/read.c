#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"
#include "read.h"

#define BLOCKSIZE 4096

void seq_test(const char *filename, uint64_t size)
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
      perror("sequential read");
      exit(1);
    }
    total += tend - tstart;
  }

  close(fd);
  free(buf);
  char file[] = "read.txt";
  write_to_file(file, (total/count), size);
}

void rand_test(const char *filename, uint64_t size)
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

  uintmax_t total = 0;
  fd = open(filename, O_RDONLY);
  if (fd < 0)
  {
    perror("open");
    exit(1);
  }

  for (uintmax_t i = count; i > 0; i--)
  {
    lseek(fd, (i-1)*BLOCKSIZE, SEEK_SET);
    read_start();
    uint64_t read_bytes = read(fd, buf, BLOCKSIZE);
    read_end();
    if (read_bytes <= 0)
    {
      perror("reverse read");
      exit(1);
    }
    total += tend - tstart;
  }

  close(fd);
  free(buf);
  char file[] = "read.txt";
  write_to_file(file, (total/count), size);
}

void read_test(char filenames[][1024], int flag)
{
  int ARRAY_SIZE = 13;
  uint64_t size[ARRAY_SIZE];
  for (int i = 1; i <= ARRAY_SIZE; i++)
  {
    size[i - 1] = i;
    create_file(filenames[i - 1], i);
  }

  delete_file("read.txt");

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    printf("Running test %d\n", i);
    if (flag==0)
      seq_test(filenames[i], size[i]);
    else
      rand_test(filenames[i], size[i]);
  }
}