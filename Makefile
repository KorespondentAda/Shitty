
INCLUDE = ./include/
CODE = ./src/
CPP = ./cpp/
OBJ = main.o bitmap.o
EXE = test
CC = gcc
CFLAGS = -std=c++11 -c -Wall

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

bitmap.o: $(CPP)bitmap.hpp $(CPP)bitmap.cpp $(CPP)bitmapdef.hpp $(CPP)bitmapdef.cpp
	$(CC) $(CFLAGS) $(CPP)bitmap.cpp $(CPP)bitmapdef.cpp

main.o: $(CPP)main.cpp $(CPP)bitmap.hpp $(CPP)bitmapdef.hpp
	$(CC) $(CFLAGS) $(CPP)main.cpp

clean:
	rm $(OBJ) $(EXE)
	