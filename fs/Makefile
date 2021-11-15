CC = g++
CFLAGS = -Wall -g -pthread -lm -O0
OBJ = src/obj

all: $(OBJ)/main.o $(OBJ)/utils.o $(OBJ)/cache.o
	cd src;\
	$(CC) $(CFLAGS) -I. obj/*.o -o fs_main

$(OBJ)/main.o: src/main.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../main.c

$(OBJ)/cache.o: src/cache.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../cache.c

$(OBJ)/utils.o: src/utils.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../utils.c

results:
	rm -rf src/results

clean:
	rm -rf $(OBJ)/*.o;\
	rm -f src/fs_main
