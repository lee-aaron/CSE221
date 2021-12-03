#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "cache.h"
#include "read.h"
#include "contention.h"
#include "utils.h"

int main(int argc, char **argv)
{
  char filenames[16][1024];
  for (int i = 0; i < 13; i++) {
    sprintf(filenames[i], "src/files/file%d", i+1);
  }

  if (argc > 1 && strcmp(argv[1], "cache") == 0) {
    init_test(filenames);
  } else if (argc > 1 && strcmp(argv[1], "contention") == 0) {
    for (int i = 0; i < 16; i++) {
      sprintf(filenames[i], "src/files/cont%d", i);
    }
    delete_file("src/results/contention.txt");
    for (int i = 1; i <= 16; i++) {
      contention(filenames, i);
    }
  }

  if (argc > 1 && strcmp(argv[1], "seq") == 0) {
    read_test(filenames, 0);
  }

  if (argc > 1 && strcmp(argv[1], "rand") == 0) {
    read_test(filenames, 1);
  }

}
