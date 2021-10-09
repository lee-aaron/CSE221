#define _XOPEN_SOURCE 600

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ucontext.h>

#include "measurement.h"

#define MEM 64000

uint64_t one_switch() {
    ucontext_t ctx_main, ctx_thread;
    static int thread_id = 0;

    printf("Creating main context\n");
    getcontext(&ctx_main);
    ctx_main.uc_link = 0;
    ctx_main.uc_stack.ss_sp = malloc(MEM);
    ctx_main.uc_stack.ss_size = MEM;
    ctx_main.uc_stack.ss_flags = 0;
    printf("Main context created\n");

    printf("Creating thread context\n");
    getcontext(&ctx_thread);
    ctx_thread.uc_link = 0;
    ctx_thread.uc_stack.ss_sp = malloc(MEM);
    ctx_thread.uc_stack.ss_size = MEM;
    ctx_thread.uc_stack.ss_flags = 0;
    printf("Thread context created\n");

    unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
    asm volatile("cpuid\n\t"
                 "rdtsc\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

    //Context Switch here
    printf("Swapping to thread\n");
    swapcontext(&ctx_main, &ctx_thread);
    printf("Swap complete\n");

    asm volatile("rdtscp\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "cpuid\n\t"
                 : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");


    uint64_t tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
    uint64_t tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
    uint64_t rslt = tend - tstart;

    return rslt;
}

double switch_overhead(int num) {
    ucontext_t ctx_main, ctx_thread;
    static int thread_id = 0;
    uint64_t *results = (uint64_t *)malloc(num * sizeof(uint64_t));
    memset(results, 0, num * sizeof(uint64_t));

    for (int i = 0; i < num; i++) {
        results[i] = one_switch();
        _exit(0);
    }

    double avg = get_average(results, num);
    printf("Context Switch Overhead: %f\n", avg);
    printf("Standard Deviation: %f\n", get_sd(results, num));
    free(results);
    return avg;
}
