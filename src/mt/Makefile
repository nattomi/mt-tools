CC = gcc
CFLAGS = -Wall -pedantic -std=c99
EXEC = libmt.a
OBJS = io.o periods.o filter.o
SRCS = io.c periods.c filter.c

$(EXEC): $(OBJS)
	ar -cvq $(EXEC) $(OBJS)
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c
periods.o: periods.c periods.h
	$(CC) $(CFLAGS) -c periods.c
filter.o: filter.c filter.h
	$(CC) $(CFLAGS) -c filter.c
clean:
	rm -f *~
	rm -f *#
	rm -f ./$(EXEC)
	rm -f *.o
