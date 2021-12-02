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

void start_server(char *ip, int port)
{
  int server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0)
  {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("bind");
    exit(1);
  }

  if (listen(server_sock, 5) < 0)
  {
    perror("listen");
    exit(1);
  }

  while (1)
  {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock < 0)
    {
      perror("accept");
      exit(1);
    }

    char *client_ip = inet_ntoa(client_addr.sin_addr);
    uint16_t client_port = ntohs(client_addr.sin_port);
    printf("New connection from %s:%d\n", client_ip, client_port);

    uint64_t SIZE = 32 * 1e6;
    uint64_t count = 500;
    for (uint64_t i = 0; i < count; i++)
    {
      char *msg = (char *)malloc(SIZE * sizeof(char));
      if (!msg)
      {
        perror("malloc");
        exit(1);
      }

      memset(msg, 'a', SIZE);
      uint64_t total_sent = 0;
      while (total_sent < SIZE)
      {
        uint64_t sent = send(client_sock, msg + total_sent, SIZE - total_sent, 0);
        if (sent < 0)
        {
          perror("send");
          exit(1);
        }
        total_sent += sent;
      }
    }

    printf("Closing connection to %s:%d\n", client_ip, client_port);
    close(client_sock);
  }
  close(server_sock);
}

int bw_server(char *ip, int port)
{
  printf("Starting server on %s:%d\n", ip, port);
  start_server(ip, port);
  return 0;
}