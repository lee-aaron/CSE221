#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "access_time.h"

void access_time(int num)
{
  char filename[] = "access_time.txt";
  // deletes file if it is not empty
  delete_file(filename);

  // array size start and end (base 2)
  uint64_t size_start = 10;
  uint64_t size_end = 28;

  // stride size start and end (base 2)
  uint64_t stride_start = 5;
  uint64_t stride_end = 10;

  // local vars, pointers for memory access / allocation
  int size, stride, i;
  int **arr;
  void **p;

  for (stride = (1 << stride_start); stride < (2 << stride_end); stride <<= 1)
  {
    for (size = (1 << size_start); size < (2 << size_end); size <<= 1)
    {
      arr = (int **)malloc(size);
      if (!arr) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
      }

      // set pointer at each stride interval
      for (i = 0; i + 1 < (int)(size / (stride * sizeof(*arr))); i++) {
        arr[i * stride] = (int *)(arr + (i + 1) * stride);
      }
      // set pointer to beginning
      arr[i*stride] = (int *)(arr);

      p = (void **)arr;

      // read time and access memory at each stride interval
      read_start();
      for (i = 0; i < num; i++)
      {
        p = (void **) *p;
      }
      read_end();
      double cycles = (double)(tend - tstart)/(double)num;
      write_access_time(filename, stride, size, cycles);
      free(arr);
    }
  }
  printf("Done running Access Time\n");
}