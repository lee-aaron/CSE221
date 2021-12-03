#ifndef READ_H
#define READ_H
#include <inttypes.h>

void seq_test(const char *filename, uint64_t size);
void rand_test(const char *filename, uint64_t size);
void read_test(char filenames[][1024], int flag);

#endif