CC = gcc -pthread
CFLAGS = -Wall -Wextra -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c global.c memoria.c mensaje.c lavarropasT.c
SRH = archivos.h clave.h semaforos.h global.h memoria.h mensaje.h lavarropasT.h

all: clean lavarropa megarropa

lavarropa: lavarropas.c $(SRC) $(SRH)
	$(CC) -o lavarropa lavarropas.c $(SRC) $(CFLAGS) $(HEADERS)

megarropa: megarropa.c $(SRC) $(SRH)
	$(CC) -o megarropa megarropa.c $(SRC) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o megarropa lavarropa *~
