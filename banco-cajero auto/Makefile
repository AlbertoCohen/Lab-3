CC = gcc -pthread
CFLAGS = -Wall -Wextra -std=gnu89 -pedantic-errors
HEADERS = -I./
SRC = archivos.c clave.c semaforos.c global.c memoria.c mensaje.c clienteT.c
SRH = archivos.h clave.h semaforos.h global.h memoria.h mensaje.h clienteT.h

all: clean cliente banco

cliente: cliente.c $(SRC) $(SRH)
	$(CC) -o clientees cliente.c $(SRC) $(CFLAGS) $(HEADERS)

banco: banco.c $(SRC) $(SRH)
	$(CC) -o banco banco.c $(SRC) $(CFLAGS) $(HEADERS)

clean: 
	rm -rf *o banco cliente *~
