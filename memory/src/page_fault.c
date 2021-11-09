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

typedef long long int num;

FILE *fp;

void readone(num *x) { fscanf(fp, "%lld ", x); }
void readunsigned(unsigned long long *x) { fscanf(fp, "%llu ", x); }
void readstr(char *x) { fscanf(fp, "%s ", x); }
void readchar(char *x) { fscanf(fp, "%c ", x); }

void printone(char *name, num x) { printf("%20s: %lld\n", name, x); }
void printonex(char *name, num x) { printf("%20s: %016llx\n", name, x); }
void printunsigned(char *name, unsigned long long x) { printf("%20s: %llu\n", name, x); }
void printchar(char *name, char x) { printf("%20s: %c\n", name, x); }
void printstr(char *name, char *x) { printf("%20s: %s\n", name, x); }

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
    void *mem = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, offset);
    if (mem == MAP_FAILED)
      perror("mmap");
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

  int pid = getpid();
  char buff[1024];
  sprintf(buff, "/proc/%d/stat", pid);

  fp = fopen(buff, "r");
  if (fp == NULL)
  {
    perror("fopen");
    exit(1);
  }

  long long int pidt;
  char tcomm[PATH_MAX];
  char state;

  long long int ppid;
  long long int pgid;
  long long int sid;
  long long int tty_nr;
  long long int tty_pgrp;

  long long int flags;
  long long int min_flt;
  long long int cmin_flt;
  long long int maj_flt;
  long long int cmaj_flt;

  readone(&pidt);
  readstr(tcomm);
  readchar(&state);
  readone(&ppid);
  readone(&pgid);
  readone(&sid);
  readone(&tty_nr);
  readone(&tty_pgrp);
  readone(&flags);
  readone(&min_flt);
  readone(&cmin_flt);
  readone(&maj_flt);
  readone(&cmaj_flt);

  printone("pid", pid);
  printstr("tcomm", tcomm);
  printchar("state", state);
  printone("ppid", ppid);
  printone("pgid", pgid);
  printone("sid", sid);
  printone("tty_nr", tty_nr);
  printone("tty_pgrp", tty_pgrp);
  printone("flags", flags);
  printone("min_flt", min_flt);
  printone("cmin_flt", cmin_flt);
  printone("maj_flt", maj_flt);
  printone("cmaj_flt", cmaj_flt);
  fclose(fp);

  write_fault_time(filename, times, num);

  printf("Done running Page Fault Time\n");
}