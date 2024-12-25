CC 		= g++ 

all : cajero banco

banco : banco.c funciones.h definiciones.h funciones.o
	cc -o banco banco.c funciones.o 

cajero : cajero.c funciones.h definiciones.h funciones.o
	cc -o cajero cajero.c funciones.o -pthread

funciones.o : funciones.c funciones.h
	cc -c funciones.c
	
clean: 
	rm -rf *o cajero banco *~
	
