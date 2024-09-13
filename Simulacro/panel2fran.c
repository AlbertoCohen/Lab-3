#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "unistd.h"
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"

int main(int argc, char *argv[]){
	int id_semaforo;
	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
    srand(time(NULL));

	inAbrirArchivo("aviones.dat", "w"); /*limpio el archivo la primera vez*/
	inCerrarArchivo();
	
	
	while(1){
		espera_semaforo(id_semaforo);
		inAbrirArchivo("aviones.dat", "a+");
		inLeerArchivoCompleto();
		inCerrarArchivo();
		usleep(500*1000); 
		levanta_semaforo(id_semaforo);
	}

	
	return 0;
}
