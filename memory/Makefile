CC = g++
CFLAGS = -Wall -g -pthread -lm -O0
OBJ = src/obj

all: $(OBJ)/main.o $(OBJ)/utils.o $(OBJ)/access_time.o
	cd src;\
	$(CC) $(CFLAGS) -I. obj/*.o -o mem_main

$(OBJ)/main.o: src/main.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../main.c

$(OBJ)/utils.o: src/utils.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../utils.c

$(OBJ)/access_time.o: src/access_time.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../access_time.c

results:
	rm -rf src/results

clean:
	rm -rf $(OBJ)/*.o;\
	rm -f src/mem_main
