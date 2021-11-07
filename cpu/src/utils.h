#ifndef UTILS
#define UTILS
#include <stdint.h>

void write_to_file(const char *filename, uint64_t *results, int length);
void append_to_file(const char *filename, double result);
void delete_file(const char *filename);

#endif
