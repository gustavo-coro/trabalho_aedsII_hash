all: main

main: main.o hash.o
	gcc -o main main.o hash.o

main.o: main.c hash.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

hash.o: hash.c hash.h
	gcc -o hash.o hash.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ main