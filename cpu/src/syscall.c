#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"
#include "measurement.h"

double syscall_overhead(int num) {
    uint64_t *results = (uint64_t *)malloc(num * sizeof(uint64_t));
    memset(results, 0, num * sizeof(uint64_t));

    int fds[2];
    if (pipe(fds) < 0) {
        perror("pipe");
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        char msg[40];
        int pid = fork();
        if (pid == 0) {
            unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
            asm volatile("cpuid\n\t"
                         "rdtsc\n\t"
                         "mov %%edx, %0\n\t"
                         "mov %%eax, %1\n\t"
                         : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

            getpid();

            asm volatile("rdtscp\n\t"
                         "mov %%edx, %0\n\t"
                         "mov %%eax, %1\n\t"
                         "cpuid\n\t"
                         : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

            uint64_t tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            uint64_t tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            uint64_t rslt = tend - tstart;
            snprintf(msg, sizeof(msg), "%lu", rslt);
            write(fds[1], msg, sizeof(msg));
            _exit(0);
        } else {
            read(fds[0], msg, sizeof(msg));
            results[i] = atol(msg);
            waitpid(pid, NULL, 0);
        }
    }
    write_to_file("syscall_overhead.txt", results, num);

    double avg = get_average(results, num);
    printf("System Call Overhead: %f\n", avg);
    printf("Standard Deviation: %f\n", get_sd(results, num));
    free(results);
    return avg;
}
