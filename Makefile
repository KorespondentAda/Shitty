
obj = main.o bitmap.o
exe = test

all: $(obj)
	gcc $(obj) -o $(exe)

bitmap.o: src/bitmap.h src/bitmap.c
	gcc -c src/bitmap.c

main.o: src/main.c src/bitmap.h
	gcc -c src/main.c

clean:
	rm $(obj) $(exe)
	