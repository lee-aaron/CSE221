CC = g++
CFLAGS = -Wall -g
OBJ = src/obj

all: $(OBJ)/main.o $(OBJ)/measurement.o $(OBJ)/procedure.o $(OBJ)/syscall.o $(OBJ)/switch.o
	cd src;\
	$(CC) $(CFLAGS) -I. obj/main.o obj/measurement.o obj/procedure.o obj/syscall.o obj/switch.o -o cpu_main

$(OBJ)/main.o: src/main.c
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../main.c

$(OBJ)/measurement.o: src/measurement.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../measurement.c

$(OBJ)/procedure.o: src/procedure.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../procedure.c

$(OBJ)/syscall.o: src/syscall.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../syscall.c

$(OBJ)/switch.o: src/switch.*
	cd $(OBJ);\
	$(CC) $(CFLAGS) -c -I../ ../switch.c

clean:
	rm -rf $(OBJ)/*.o;\
	rm -f src/cpu_main
