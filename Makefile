
obj = main.o bmp.o
exe = test

all: $(obj)
	gcc $(obj) -o $(exe)

bmp.o: bmp.h bmp.c
	gcc -c bmp.c

main.o: main.c bmp.h
	gcc -c main.c

clean:
	rm $(obj) $(exe)
	