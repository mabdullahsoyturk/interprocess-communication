CC=gcc

psearch2dslave: main.o
	$(CC) -pthread main.o -o psearch2dslave -lrt

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o psearch2dslave
