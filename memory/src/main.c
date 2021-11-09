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
  printf("Cycles per second: %f\n", cycle_per_s);

  int num = 100;
  access_time(num, cycle_per_s);
  read_bandwidth(50, cycle_per_s);
  write_bandwidth(50, cycle_per_s);
  fault_time(num, cycle_per_s);
}
