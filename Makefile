CC = gcc
CFLAGS = -Wall -g -std=c99 -D_DEFAULT_SOURCE

objects = gps.o bicicleta.o log.o

gps: $(objects)
	$(CC) $(objects) -o gps

gps.o: gps.c
	$(CC) $(CFLAGS) -c gps.c

bicicleta.o: bicicleta.c bicicleta.h
	$(CC) $(CFLAGS) -c bicicleta.c

log.o: log.c log.h
	$(CC) $(CFLAGS) -c log.c

clean:
	rm -f $(objects) gps
