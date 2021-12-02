CC = g++
CFLAGS = -Wall -g -pthread -lm -O0
OBJ = src/obj

all: $(OBJ)/main.o $(OBJ)/utils.o $(OBJ)/rtt_server.o $(OBJ)/rtt_client.o $(OBJ)/bandwidth_client.o $(OBJ)/bandwidth_server.o $(OBJ)/overhead_client.o $(OBJ)/overhead_server.o
	cd src;\
	$(CC) $(CFLAGS) -I. obj/*.o -o network_main

$(OBJ)/main.o: src/main.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../main.c

$(OBJ)/utils.o: src/utils.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../utils.c

$(OBJ)/rtt_client.o: src/rtt_client.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../rtt_client.c

$(OBJ)/rtt_server.o: src/rtt_server.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../rtt_server.c

$(OBJ)/bandwidth_client.o: src/bandwidth_client.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../bandwidth_client.c

$(OBJ)/bandwidth_server.o: src/bandwidth_server.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../bandwidth_server.c

$(OBJ)/overhead_client.o: src/overhead_client.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../overhead_client.c

$(OBJ)/overhead_server.o: src/overhead_server.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../overhead_server.c

results:
	rm -rf src/results

clean:
	rm -rf $(OBJ)/*.o;\
	rm -f src/network_main
