CC = gcc -pthread
CFLAGS = -Wall -Wextra -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c global.c memoria.c mensaje.c finalistasT.c
SRH = archivos.h clave.h semaforos.h global.h memoria.h mensaje.h finalistasT.h

all: clean finalista cancha

finalista: finalistas.c $(SRC) $(SRH)
	$(CC) -o finalista finalistas.c $(SRC) $(CFLAGS) $(HEADERS)

cancha: cancha.c $(SRC) $(SRH)
	$(CC) -o cancha cancha.c $(SRC) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o cancha finalista *~
