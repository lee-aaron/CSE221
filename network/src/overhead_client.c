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

void conn_client(char *host, int port)
{
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(host);
  server.sin_port = htons(port);

  uint64_t count = 500;
  double setup[count];
  double teardown[count];
  char filename[] = "conn_local.txt";

  for (uint64_t i = 0; i < count; i++)
  {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
      perror("socket");
      exit(1);
    }

    read_start();
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      perror("connect");
      exit(1);
    }
    read_end();
    setup[i] = (tend - tstart);

    read_start();
    close(sock);
    read_end();
    teardown[i] = (tend - tstart);
  }

  conn_write_to_file(filename, setup, teardown, count);
}

int overhead_client(char *ip, int port)
{
  printf("Connecting to server at %s:%d\n", ip, port);
  conn_client(ip, port);
  return 0;
}