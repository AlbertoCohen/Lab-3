CC = gcc
CFLAGS = -Wall -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c
SRH = archivos.h clave.h semaforos.h

all: clean aviones panel

aviones: aviones.c $(SRC) $(SRH)
	$(CC) -o aviones aviones.c $(SRC) $(CFLAGS) $(HEADERS)

panel: panel.c $(SRC) $(SRH)
	$(CC) -o panel panel.c $(SRC) $(CFLAGS) $(HEADERS)

clean:
	rm -f *.o aviones panel

