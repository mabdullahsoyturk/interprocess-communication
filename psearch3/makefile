CC=gcc

psearch3: main.o
	$(CC) -pthread main.o -o psearch3 -lrt

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output.txt psearch3
