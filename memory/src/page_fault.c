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
  // deletes file if it is not empty
  //delete_file(filename);

  int fd = open("test.txt", O_RDONLY);
  int pagesize = getpagesize();
  struct stat stats;
  fstat(fd, &stats);
  int filesize = stats.st_size;
  int size = pagesize*num;

  printf("%d byte pages\n", pagesize);
  printf("file %s @ %d bytes\n", filename, filesize);

  if(size > filesize)
  {
    int pages = ceil((filesize)/(double)pagesize);
    size = pages*pagesize;
  }
  printf("Calling mmap on %d bytes\n", size);

  void * mem = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);

  read_start();
  char c;
  for(int i=0; i<size; i+=pagesize)
  {
    for(int j=0; j < pagesize; j++) {
      c = *((char *)mem+i+j);
    }
  }
  read_end();
  double cycles = (double)(tend - tstart)/(double)num;
  printf("Number of cycles: %f\n", cycles);

  write_fault_time(filename, cycles / (cps / 1e9));

  printf("Done running Page Fault Time\n");
}