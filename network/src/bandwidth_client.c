#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "utils.h"

void start_bw(char *ip, uint16_t port)
{
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  uint64_t count = 500;
  uint64_t total = 0;
  uint64_t SIZE = 32 * 1e6;

  double results[count];
  char filename[] = "bw_local.txt";

  int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (serv_sock < 0)
  {
    perror("socket creation");
    exit(1);
  }

  if (connect(serv_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    perror("server conn");
    exit(1);
  }

  for (uint64_t i = 0; i < count; i++)
  {
    char *msg = (char *) malloc(sizeof(char) * SIZE);
    memset(msg, 'a', SIZE);
    read_start();
    uint64_t bytes = recv(serv_sock, msg, SIZE, MSG_WAITALL);
    read_end();

    if (bytes < 0) {
      perror("recv");
      exit(1);
    }

    total += (tend - tstart);
    results[i] = (tend - tstart);
    free(msg);
  }

  write_to_file(filename, results, count);
  double avg_cycles = (double)total / (double)count;
  printf("Avg cycles: %f\n", avg_cycles);
  close(serv_sock);
}

int bw_client(char *ip, int port)
{
  printf("Connecting to server at %s:%d\n", ip, port);
  start_bw(ip, port);
  return 0;
}