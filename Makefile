LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
BIN=./bin

CC=gcc

FLAGS= -Wall -ansi

INCFLAGS = -I$(INCLUDE)

all: $(BIN)/fish-shell

$(BIN)/fish-shell: $(OBJ)/exec.o $(OBJ)/funcs.o $(OBJ)/fish.o
	$(CC) $(FLAGS) $(SRC)/fish-shell.c $(OBJ)/exec.o $(OBJ)/funcs.o $(OBJ)/fish.o $(INCFLAGS) -o $(BIN)/fish-shell
	
$(OBJ)/exec.o: $(SRC)/exec.c $(INCLUDE)/exec.h $(OBJ)/funcs.o
	$(CC) $(FLAGS) -c $(SRC)/exec.c $(OBJ)/funcs.o $(INCFLAGS) -o $(OBJ)/exec.o

$(OBJ)/funcs.o: $(SRC)/funcs.c $(INCLUDE)/funcs.h
	$(CC) $(FLAGS) -c $(SRC)/funcs.c $(INCFLAGS) -o $(OBJ)/funcs.o

$(OBJ)/fish.o: $(SRC)/fish.c $(INCLUDE)/fish.h
	$(CC) $(FLAGS) -c $(SRC)/fish.c $(INCFLAGS) -o $(OBJ)/fish.o
