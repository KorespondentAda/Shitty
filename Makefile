
INCLUDE = ./include/
CODE 	= ./src/
OBJ 	= main.o bitmap.o bitmapdef.o
EXE 	= BitmapReader
CC 		= g++
CFLAGS 	= -std=c++11 -Wall -O3 -c

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp $(INCLUDE)bitmap.hpp $(INCLUDE)bitmapdef.hpp
	$(CC) $(CFLAGS) $(CODE)main.cpp

bitmap.o: $(CODE)bitmap.cpp $(INCLUDE)bitmap.hpp $(INCLUDE)bitmapdef.hpp
	$(CC) $(CFLAGS) $(CODE)bitmap.cpp

bitmapdef.o: $(CODE)bitmapdef.cpp $(INCLUDE)bitmapdef.hpp 
	$(CC) $(CFLAGS) $(CODE)bitmapdef.cpp

clean:
	rm $(OBJ) $(EXE)
	