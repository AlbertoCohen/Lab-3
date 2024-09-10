CC = gcc
CFLAGS = -Wall -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c
SRH = archivos.h clave.h semaforos.h

all: productor consumidor clean

productor: productor.c $(SRC) $(SRH)
	$(CC) -o productor productor.c $(SRC) $(CFLAGS) $(HEADERS)

consumidor: consumidor.c $(SRC) $(SRH)
	$(CC) -o consumidor consumidor.c $(SRC) $(CFLAGS) $(HEADERS)

clean:
	rm -f *.o productor consumidor
