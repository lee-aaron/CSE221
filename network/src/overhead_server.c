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

void conn_server(char *host, int port)
{
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    perror("socket");
    exit(1);
  }

  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    perror("bind");
    exit(1);
  }

  if (listen(sock, 5) < 0)
  {
    perror("listen");
    exit(1);
  }

  while (1)
  {
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int csock = accept(sock, (struct sockaddr *)&client, &len);
    if (csock < 0)
    {
      perror("accept");
      exit(1);
    }

    char *client_ip = inet_ntoa(client.sin_addr);
    uint16_t client_port = ntohs(client.sin_port);
    printf("New connection from %s:%d\n", client_ip, client_port);

    close(csock);
  }

  close(sock);
}

int overhead_server(char *ip, int port)
{
  printf("Starting server on %s:%d\n", ip, port);
  conn_server(ip, port);
  return 0;
}