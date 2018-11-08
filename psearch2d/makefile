CC=gcc

psearch2d: main.o
	$(CC) -pthread main.o -o psearch2d -lrt

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output.txt psearch2d
