CC = gcc -pthread
CFLAGS = -Wall -Wextra -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c global.c memoria.c mensaje.c mosquitosT.c
SRH = archivos.h clave.h semaforos.h global.h memoria.h mensaje.h mosquitosT.h

all: clean mosquito pista

mosquito: mosquitos.c $(SRC) $(SRH)
	$(CC) -o mosquito mosquitos.c $(SRC) $(CFLAGS) $(HEADERS)

pista: pista.c $(SRC) $(SRH)
	$(CC) -o pista pista.c $(SRC) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o pista mosquito *~
