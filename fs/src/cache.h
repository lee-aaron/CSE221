#ifndef CACHE_H
#define CACHE_H
#include <inttypes.h>

void cache_size(const char *filename, uint64_t size);
void init_test(char filenames[10][1024]);

#endif