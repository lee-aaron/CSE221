#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "utils.h"

void write_to_file(const char *filename, uint64_t *results, int length)
{
  char location[256] = "./src/results/";
  strncat(location, filename, strlen(filename));

  FILE *fp = fopen(location, "w");
  for (int i = 0; i < length; i++) {
    fprintf(fp, "%ld\n", results[i]);
  }
  fclose(fp);
}
