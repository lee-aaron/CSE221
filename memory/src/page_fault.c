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

  int fd = open("test.txt", O_RDONLY);
  fcntl(fd, F_NOCACHE, 1);
  struct stat stats;
  fstat(fd, &stats);
  int filesize = stats.st_size;
  
  printf("%d byte pages\n", pagesize);
  printf("file test.txt @ %d bytes\n", filesize);

  for (int i = 0; i < num; i++) {
    if(offset > filesize)
    {
      break;
    }
    void * mem = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, offset);
    if(mem == MAP_FAILED) printf("Map Failed\n");
    offset+=pagesize;
    read_start();
    c = *((char *)mem);
    read_end();
    double cycles = (double)(tend - tstart);
    times[i] = cycles / (cps / 1e9);
    munmap(mem, pagesize);   
  }

  write_fault_time(filename, times, num);

  printf("Done running Page Fault Time\n");
}