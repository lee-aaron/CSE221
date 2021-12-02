#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "rtt_client.h"
#include "rtt_server.h"
#include "bandwidth_client.h"
#include "bandwidth_server.h"
#include "overhead_client.h"
#include "overhead_server.h"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Please add which test you want to run\n");
    exit(1);
  }

  if (strcmp(argv[1], "rtt_c") == 0)
  {
    if (argc < 4)
    {
      printf("Please add IP address and port of server to test\n");
      exit(1);
    }
    char *ip = argv[2];
    int port = atoi(argv[3]);
    start_c(ip, port);
    exit(0);
  }

  if (strcmp(argv[1], "rtt_s") == 0)
  {
    start_s(argc, argv);
    exit(0);
  }

  if (strcmp(argv[1], "bw_c") == 0)
  {
    if (argc < 4)
    {
      printf("Please add IP address and port of server to test\n");
      exit(1);
    }
    char *ip = argv[2];
    int port = atoi(argv[3]);
    bw_client(ip, port);
    exit(0);
  }

  if (strcmp(argv[1], "bw_s") == 0)
  {
    if (argc < 4)
    {
      printf("Please add IP address and port of server to test\n");
      exit(1);
    }
    char *ip = argv[2];
    int port = atoi(argv[3]);
    bw_server(ip, port);
    exit(0);
  }

  if (strcmp(argv[1], "conn_c") == 0)
  {
    if (argc < 4)
    {
      printf("Please add IP address and port of server to test\n");
      exit(1);
    }
    char *ip = argv[2];
    int port = atoi(argv[3]);
    overhead_client(ip, port);
    exit(0);
  }

  if (strcmp(argv[1], "conn_s") == 0)
  {
    if (argc < 4)
    {
      printf("Please add IP address and port of server to test\n");
      exit(1);
    }
    char *ip = argv[2];
    int port = atoi(argv[3]);
    overhead_server(ip, port);
    exit(0);
  }
}
