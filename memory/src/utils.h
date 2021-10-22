#ifndef UTILS
#define UTILS
#include <stdint.h>

void write_to_file(const char *filename, uint64_t *results, int length);
void write_access_time(const char *filename, uint64_t stride, uint64_t size, double time);
void delete_file(const char *filename);

extern unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
extern uint64_t tstart, tend;

void read_start();
void read_end();

#endif
