#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "cache.h"
#include "read.h"

int main(int argc, char **argv)
{
  char filenames[13][1024];
  for (int i = 0; i < 13; i++) {
    sprintf(filenames[i], "src/files/file%d", i+1);
  }

  if (argc > 1 && strcmp(argv[1], "cache") == 0) {
    init_test(filenames);
  }

  if (argc > 1 && strcmp(argv[1], "seq") == 0) {
    read_test(filenames, 0);
  }

  if (argc > 1 && strcmp(argv[1], "rand") == 0) {
    read_test(filenames, 1);
  }

}
