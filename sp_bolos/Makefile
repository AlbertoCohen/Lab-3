CC = gcc -pthread
CFLAGS = -Wall -Wextra -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c global.c memoria.c mensaje.c jugadorT.c
SRH = archivos.h clave.h semaforos.h global.h memoria.h mensaje.h jugadorT.h

all: clean jugador pienso

jugador: jugador.c $(SRC) $(SRH)
	$(CC) -o jugadores jugador.c $(SRC) $(CFLAGS) $(HEADERS)

pienso: pienso.c $(SRC) $(SRH)
	$(CC) -o pienso pienso.c $(SRC) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o pienso jugador *~
