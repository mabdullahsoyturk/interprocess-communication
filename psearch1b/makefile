CC=gcc

psearch1b: main.o
	$(CC) -pthread main.o -o psearch1b

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output.txt psearch1b
