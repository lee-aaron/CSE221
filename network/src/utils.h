#ifndef UTILS
#define UTILS

extern uint64_t tstart, tend;

void read_start();
void read_end();

void write_to_file(const char *filename, double *results, int length);
void conn_write_to_file(const char *filename, double *setup, double *teardown, int length);
void delete_file(const char *filename);

#endif