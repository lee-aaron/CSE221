#ifndef UTILS
#define UTILS
#include <stdint.h>

void write_to_file(const char *filename, double *results, int length);
void append_to_file(const char *filename, double result);
void delete_file(const char *filename);

extern uint64_t tstart, tend;

void read_start();
void read_end();

#endif
