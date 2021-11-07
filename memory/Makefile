CC = g++
CFLAGS = -Wall -g -pthread -lm -O0
OBJ = src/obj

all: $(OBJ)/main.o $(OBJ)/utils.o $(OBJ)/access_time.o $(OBJ)/bandwidth.o $(OBJ)/page_fault.o 
	cd src;\
	$(CC) $(CFLAGS) -I. obj/*.o -o mem_main

$(OBJ)/main.o: src/main.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../main.c

$(OBJ)/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c -Isrc $< -o $@

results:
	rm -rf src/results

clean:
	rm -rf $(OBJ)/*.o;\
	rm -f src/mem_main
