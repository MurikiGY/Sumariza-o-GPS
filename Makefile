CC = gcc
CFLAGS = -Wall -g -std=c99 -D_DEFAULT_SOURCE

objects = gps.o bicicleta.o log.o

all: gps

gps: $(objects)

gps.o: gps.c

bicicleta.o: bicicleta.c bicicleta.h

log.o: log.c log.h

clean:
	rm -f $(objects)

purge: clean
	rm gps
