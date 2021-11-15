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

void start_server(char *ip, uint16_t port)
{
  int server_sock, client_sock;
  struct sockaddr_in server, client;
  uint64_t count = 1000;

  int addrlen = sizeof(server);
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0)
  {
    perror("socket creation");
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_port = htons(port);

  if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    perror("bind");
    exit(1);
  }

  if (listen(server_sock, 3) < 0)
  {
    perror("listen");
    exit(1);
  }
  char data[1024];

  while (1)
  {

    client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t *)&addrlen);

    if (client_sock < 0)
    {
      perror("client accept");
      exit(1);
    }

    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client.sin_addr, ipstr, sizeof(ipstr));
    printf("client connected from %s:%d\n", ipstr, ntohs(client.sin_port));

    for (uint64_t i = 0; i < count; ++i)
    {
      recv(client_sock, &data, 1024, 0);
      send(client_sock, &data, 1024, 0);
    }
  }
}

int start_s(int argc, char **argv)
{
  char *server_ip = argv[2];
  uint16_t server_port = atoi(argv[3]);

  printf("Starting server at %s:%d\n", server_ip, server_port);

  start_server(server_ip, server_port);

  return 0;
}