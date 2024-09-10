# Con CC = gcc-4.1
CC = gcc
CFLAGS = -Wall -std=gnu89 -pedantic-errors -Wall
HEADERS = -I./


all : reina hormiga

hormiga : Hormiga.c definiciones.h GestionSemaforos.c GestionSemaforos.h GestionMemoria.c GestionMemoria.h GestionMensajes.c GestionMensajes.h Aleatorios.c  Aleatorios.h
	$(CC) -o hormiga Hormiga.c GestionSemaforos.c GestionMemoria.c GestionMensajes.c Aleatorios.c  -pthread $(CFLAGS) $(HEADERS)

reina : Reina.c definiciones.h GestionSemaforos.c GestionSemaforos.h GestionMemoria.c GestionMemoria.h GestionMensajes.c GestionMensajes.h Aleatorios.c  Aleatorios.h
	$(CC) -o reina Reina.c GestionSemaforos.c GestionMemoria.c GestionMensajes.c Aleatorios.c  $(CFLAGS) $(HEADERS)
	
clean: 
	rm -rf *o reina hormiga *~
