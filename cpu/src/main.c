#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "measurement.h"
#include "procedure.h"
#include "syscall.h"
#include "switch.h"
#include "utils.h"

int main(int argc, char **argv)
{
  read_start();
  sleep(10);
  read_end();
  double cps = (double)(tend - tstart) / 10.0;
  printf("Cycles per second: %f\n", cps);

  int num = 1000;
  read_overhead(num, cps);
  loop_overhead(num, cps);
  for (int i = 0; i <= 7; i++) {
    procedure_overhead(num, i, cps);
  }
  syscall_overhead(num, cps);
  switch_overhead(num, cps);
  create_overhead(num, cps);
  switch_overhead_c(num, cps);
  create_overhead_c(num, cps);
}
