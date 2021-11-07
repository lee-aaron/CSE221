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

void fault_time(int num)
{
  char filename[] = "page_fault_time.txt";
  // deletes file if it is not empty
  delete_file(filename);

  int fd = open(filename, O_RDONLY);
  int pagesize = getpagesize();
  int size = pagesize*num;

  printf("%d byte pages\n", pagesize);
  printf("Calling mmap on %d bytes\n", size);

  void * mem = mmap(0, size, PROT_NONE, MAP_PRIVATE, fd, 0);
  
  char c;

  read_start();
  for(int i=0; i<size; i+=pagesize)
  {
    c = *((char *)mem+i);
  }
  read_end();
  double cycles = (double)(tend - tstart)/(double)num;

  write_fault_time(filename, cycles);

  printf("Done running Page Fault Time\n");
}