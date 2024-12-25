CC = gcc
CFLAGS = -Wall -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c memoria.c
SRH = archivos.h clave.h semaforos.h memoria.h

all: clean cajas derivador
cajas: cajas.c $(SRC) $(SRH)
	$(CC) -o cajas cajas.c $(SRC) $(CFLAGS) $(HEADERS)

derivador: derivador.c $(SRC) $(SRH)
	$(CC) -o derivador derivador.c $(SRC) $(CFLAGS) $(HEADERS)

clean: 
	rm -f *.o cajas derivador

