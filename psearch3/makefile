CC=gcc

output: main.o utilities.o
	$(CC) -pthread main.o utilities.o -o output -lrt

main.o: main.c utilities.o
	$(CC) -c main.c

utilities.o: utilities.c utilities.h
	$(CC) -c utilities.c

clean:
	rm *.o *.t output.txt output
