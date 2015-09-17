CC=gcc
CFLAGS=-ljson -lm

all: mtforward1d genfreqs

mtforward1d: mtforward1d.c
	$(CC) -o mtforward1d mtforward1d.c $(CFLAGS)

genfreqs: genfreqs.c
	$(CC) -o genfreqs genfreqs.c -ljson

