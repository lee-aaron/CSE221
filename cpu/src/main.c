#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "measurement.h"
#include "procedure.h"
#include "syscall.h"
#include "switch.h"

int main(int argc, char **argv)
{
  int num = 1000;
  read_overhead(num);
  loop_overhead(num);
  for (int i = 0; i <= 7; i++) {
    procedure_overhead(num, i);
  }
  syscall_overhead(num);
  switch_overhead(num);
}
