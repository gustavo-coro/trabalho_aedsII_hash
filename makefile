all: main

main: main.o hash.o list.o
	gcc -o main main.o hash.o list.o

main.o: main.c hash.h list.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

hash.o: hash.c hash.h
	gcc -o hash.o hash.c -c -W -Wall -ansi -pedantic

list.o: list.c list.h
	gcc -o list.o list.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ main