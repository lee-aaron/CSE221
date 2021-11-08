#ifndef UTILS
#define UTILS
#include <stdint.h>

void write_to_file(const char *filename, uint64_t *results, int length);
void write_to_file_d(const char *filename, double *results, int length);
void write_access_time(const char *filename, uint64_t stride, uint64_t size, double time);
void write_fault_time(const char *filename, double *times, int length);
void delete_file(const char *filename);

extern uint64_t tstart, tend;

void read_start();
void read_end();

#endif
