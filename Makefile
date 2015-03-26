CC = gcc -I ./include

# edit the define flag’s parameter to select an allocation policy:
#	1) WORST_FIT (default)
#	2) FIRST_FIT
#	3) BEST_FIT
CFLAGS = -std=gnu99 -Wall -g -D WORST_FIT #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = memory-test

all: $(EXECS)

$(OBJ)/allocator.o: dlist.h allocator.h allocator.c
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

$(OBJ)/readline.o: $(INC)/readline.h $(SRC)/readline.c
	$(CC) $(CFLAGS) -c $(SRC)/readline.c -o $(OBJ)/readline.o

memory-test: $(SRC)/memory-test.c $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o
	$(CC) $(CFLAGS) $(SRC)/memory-test.c $(OBJ)/allocator.o $(OBJ)/dnode.o $(OBJ)/dlist.o -o $(BIN)/memory-test

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~
