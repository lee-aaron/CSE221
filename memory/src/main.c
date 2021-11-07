#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "access_time.h"
#include "bandwidth.h"
#include "page_fault.h"
#include "utils.h"

int main(int argc, char **argv)
{
  read_start();
  sleep(10);
  read_end();
  double cycle_per_s = (double)(tend - tstart) / 10.0;

  int num = 100;
  access_time(num);
  read_bandwidth(100, cycle_per_s);
  write_bandwidth(100, cycle_per_s);
  printf("Start running Page Fault Time\n");
  fault_time(num);
}
