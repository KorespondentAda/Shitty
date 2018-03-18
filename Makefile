
INCLUDE = ./include/
CODE 	= ./src/
CPP 	= ./cpp/
OBJ 	= main.o bitmap.o bitmapdef.o
EXE 	= test
CC 		= g++
CFLAGS 	= -std=c++11 -Wall -c

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

bitmapdef.o: $(CPP)bitmapdef.cpp $(CPP)bitmapdef.hpp 
	$(CC) $(CFLAGS) $(CPP)bitmapdef.cpp

bitmap.o: $(CPP)bitmap.cpp $(CPP)bitmap.hpp $(CPP)bitmapdef.hpp
	$(CC) $(CFLAGS) $(CPP)bitmap.cpp

main.o: $(CPP)main.cpp $(CPP)bitmap.hpp $(CPP)bitmapdef.hpp
	$(CC) $(CFLAGS) $(CPP)main.cpp

clean:
	rm $(OBJ) $(EXE)
	