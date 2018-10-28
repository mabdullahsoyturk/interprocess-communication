output: main.o utilities.o
	gcc main.o utilities.o -o output

main.o: main.c
	gcc -c main.c

utilities.o: utilities.c utilities.h
	gcc -c utilities.c

clean:
	rm *.o *.t output.txt output
