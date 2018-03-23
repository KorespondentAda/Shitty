
INCLUDE = ./include/
CODE 	= ./src/
OBJ 	= main.o bitmap.o bitmapdef.o
EXE 	= BitmapReader
CC 		= g++
CFLAGS 	= -std=c++11 -Wall -O3 -c

#$(CXX) is default registred C++ compiler, maybe change on this?
all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp $(INCLUDE)bitmap.hpp $(INCLUDE)bitmapdef.hpp
	$(CXX) $(CFLAGS) $(CODE)main.cpp

bitmap.o: $(CODE)bitmap.cpp $(INCLUDE)bitmap.hpp $(INCLUDE)bitmapdef.hpp
	$(CXX) $(CFLAGS) $(CODE)bitmap.cpp

bitmapdef.o: $(CODE)bitmapdef.cpp $(INCLUDE)bitmapdef.hpp 
	$(CXX) $(CFLAGS) $(CODE)bitmapdef.cpp

clean:
	rm $(OBJ) $(EXE)
	