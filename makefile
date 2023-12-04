CC = gcc
CFLAGS = -Wall -g
all: biginteger
biginteger: main.o biginteger.o
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c biginteger.h
	$(CC) $(CFLAGS) -c $<
bigint_operations.o: biginteger.c biginteger.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o biginteger
