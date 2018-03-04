
INCLUDE = ./include/
CODE = ./src/
OBJ = main.o bitmap.o
EXE = test
CC = gcc
CFLAGS = -c -Wall

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

bitmap.o: $(INCLUDE)bitmap.h $(CODE)bitmap.c
	$(CC) $(CFLAGS) $(CODE)bitmap.c

main.o: $(CODE)main.c $(INCLUDE)bitmap.h
	$(CC) $(CFLAGS) $(CODE)main.c

clean:
	rm $(OBJ) $(EXE)
	