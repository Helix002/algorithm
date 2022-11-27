CFLAGS=-g
CC=gcc

PROG=sort

all: $(PROG)

sort: sort_test.o sort.o
	$(CC) $(CFLAGS) -o sort sort_test.o sort.o 

sort.o: sort.h

clean:
	rm -f *.o $(PROG)