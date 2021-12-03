#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"
#include "contention.h"

const int BLOCKSIZE = 4096;

void read_file(char filenames[][1024], int file_count, int currfile) {
    const char *file = filenames[currfile];
    char buf[BLOCKSIZE];
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    clear_cache();

    size_t bytes = 0;
    int time = 0;
    while (1) {
        read_start();
        ssize_t n = read(fd, buf, BLOCKSIZE);
        read_end();
        if (n < 0) {
            perror("read");
            exit(1);
        } else if (n == 0) {
            break;
        }
        bytes += n;
        time += tend - tstart;
    }
    close(fd);
    if (currfile == 0) {
        double avgtime = (double)time / ((double)bytes / BLOCKSIZE);
        FILE *fout = fopen("src/results/contention.txt", "a");
        fprintf(fout, "%d %f\n", file_count, avgtime);
        fclose(fout);
    }
}

void contention(char filenames[][1024], int proc_count) {
    for (int i = 0; i < proc_count; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            read_file(filenames, proc_count, i);
            _exit(0);
        }
    }
    for (int i = 0; i < proc_count; i++) {
        wait(NULL);
    }
}
