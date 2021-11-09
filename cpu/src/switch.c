#define _XOPEN_SOURCE 600

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include "measurement.h"
#include "utils.h"

void *helper(void *arg)
{
    return NULL;
}

double switch_overhead(int num, double cps)
{
    double *results = (double *)malloc(num * sizeof(double));
    memset(results, 0, num * sizeof(double));

    for (int i = 0; i < num; i++)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, &helper, NULL);
        unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
        asm volatile("cpuid\n\t"
                     "rdtsc\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

        pthread_join(thread, NULL);

        asm volatile("rdtscp\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     "cpuid\n\t"
                     : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

        uint64_t tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
        uint64_t tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
        results[i] = (double)(tend - tstart)/(cps / 1e9);
    }

    double avg = get_average(results, num);
    printf("Kernel Thread Switch Overhead: %f\n", avg);
    printf("Standard Deviation: %f\n", get_sd(results, num));
    write_to_file("switch_overhead.txt", results, num);
    free(results);
    return avg;
}

double create_overhead(int num, double cps)
{
    double *results = (double *)malloc(num * sizeof(double));
    memset(results, 0, num * sizeof(double));

    for (int i = 0; i < num; i++)
    {
        pthread_t thread;
        unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
        asm volatile("cpuid\n\t"
                     "rdtsc\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

        pthread_create(&thread, NULL, &helper, NULL);

        asm volatile("rdtscp\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     "cpuid\n\t"
                     : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

        uint64_t tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
        uint64_t tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
        results[i] = (double)(tend - tstart)/(cps / 1e9);
    }

    double avg = get_average(results, num);
    printf("Kernel Thread Creation Overhead: %f\n", avg);
    printf("Standard Deviation: %f\n", get_sd(results, num));
    write_to_file("create_overhead.txt", results, num);
    free(results);
    return avg;
}

double switch_overhead_c(int num, double cps)
{
    double *results = (double *)malloc(num * sizeof(double));
    memset(results, 0, num * sizeof(double));
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    };

    for (int i = 0; i < num; i++)
    {
        int pid = fork();
        unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
        if (pid != 0)
        {
            asm volatile("cpuid\n\t"
                         "rdtsc\n\t"
                         "mov %%edx, %0\n\t"
                         "mov %%eax, %1\n\t"
                         : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");
            read(pipefd[0], &cycles_high1, sizeof(unsigned));
            read(pipefd[0], &cycles_low1, sizeof(unsigned));
            waitpid(pid, NULL, 0);
            uint64_t tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
            uint64_t tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
            results[i] = (double)(tend - tstart)/(cps / 1e9);
        }
        else
        {
            asm volatile("rdtscp\n\t"
                         "mov %%edx, %0\n\t"
                         "mov %%eax, %1\n\t"
                         "cpuid\n\t"
                         : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");
            write(pipefd[1], &cycles_high1, sizeof(unsigned));
            write(pipefd[1], &cycles_low1, sizeof(unsigned));
            _exit(0);
        }
    }

    double avg = get_average(results, num);
    printf("Process Switch Overhead: %f\n", avg);
    printf("Standard Deviation: %f\n", get_sd(results, num));
    free(results);
    return avg;
}

double create_overhead_c(int num, double cps)
{
    double *results = (double *)malloc(num * sizeof(double));
    memset(results, 0, num * sizeof(double));

    for (int i = 0; i < num; i++)
    {
        unsigned cycles_high0, cycles_high1, cycles_low0, cycles_low1;
        asm volatile("cpuid\n\t"
                     "rdtsc\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     : "=r"(cycles_high0), "=r"(cycles_low0)::"%rax", "%rbx", "%rcx", "%rdx");

        int pid = fork();

        asm volatile("rdtscp\n\t"
                     "mov %%edx, %0\n\t"
                     "mov %%eax, %1\n\t"
                     "cpuid\n\t"
                     : "=r"(cycles_high1), "=r"(cycles_low1)::"%rax", "%rbx", "%rcx", "%rdx");

        if (pid == 0)
        {
            _exit(0);
        }

        wait(NULL);

        uint64_t tstart = (((uint64_t)cycles_high0 << 32) | cycles_low0);
        uint64_t tend = (((uint64_t)cycles_high1 << 32) | cycles_low1);
        results[i] = (double)(tend - tstart)/(cps / 1e9);
    }

    double avg = get_average(results, num);
    printf("Process Creation Overhead: %f\n", avg);
    printf("Standard Deviation: %f\n", get_sd(results, num));
    free(results);
    return avg;
}