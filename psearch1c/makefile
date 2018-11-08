CC=gcc

psearch1c: main.o
	$(CC) -pthread main.o -o psearch1c

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o output.txt psearch1c
