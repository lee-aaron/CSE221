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

void start_client(char *ip, uint16_t port)
{
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  uint64_t count = 1000;
  uint64_t total;
  char data[1024] = "abc";

  double results[count];
  char filename[] = "rtt_local.txt";

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

  total = 0;
  for (uint64_t i = 0; i < count; i++)
  {

    read_start();
    send(serv_sock, &data, sizeof(data), 0);
    recv(serv_sock, &data, sizeof(data), 0);
    read_end();
    total += (tend - tstart);
    results[i] = (tend - tstart);
  }

  write_to_file(filename, results, count);
  double avg_cycles = (double)total / (double)count;
  printf("Avg cycles: %f\n", avg_cycles);
}

int start_c(char *ip, int port)
{
  printf("Connecting to server at %s:%d\n", ip, port);
  start_client(ip, port);
  return 0;
}