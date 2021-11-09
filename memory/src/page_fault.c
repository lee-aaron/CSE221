#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <math.h>
#include "page_fault.h"
#include "utils.h"

void fault_time(int num, double cps)
{
  char filename[] = "page_fault_time.txt";
  delete_file(filename);

  int offset = 0;
  char c;
  double times[num];
  int pagesize = getpagesize();

  printf("%d byte pages\n", pagesize);

  for (int i = 0; i < num; i++)
  {
#if __APPLE__
    system("sync; sudo purge");
#else
    system("sync; echo 3 > /proc/sys/vm/drop_caches");
#endif
    void *mem = mmap(NULL, pagesize, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, offset);
    if (mem == MAP_FAILED) {
      perror("mmap");
      exit(1);
    }
    offset += pagesize;
    read_start();
    for (int j = 0; j < pagesize; j++)
    {
      c = *((char *)mem + j);
    }
    read_end();
    double cycles = (double)(tend - tstart);
    times[i] = cycles / (cps / 1e9);
    munmap(mem, pagesize);
  }

  write_fault_time(filename, times, num);

  printf("Done running Page Fault Time\n");
}