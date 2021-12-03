#ifndef UTILS_H
#define UTILS_H

extern uint64_t tstart, tend;

void read_start();
void read_end();

void write_to_file(const char *filename, uintmax_t total, uint64_t size);
void delete_file(const char *filename);
void create_file(const char *filename, uint64_t size);

#endif