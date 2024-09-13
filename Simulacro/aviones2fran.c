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
	int numero_avion;
	char destino[MAX_CHAR];
	char escritura[MAX_CHAR];
	Avion avion;
	id_semaforo = creo_semaforo();
	srand(time(NULL));	

	if (argc != 2){
		printf("Error: debe proporcionar el numero del avion\n");
		printf("Uso: ./prog (numero avion)\n");
		return 0;
	}

	numero_avion =  atoi(argv[1]); /*variable intermedia entre los parametros y la asignacion de valores del struct*/
	avion.nro_avion = numero_avion; /*asigno valores al struct*/

	while(1){	
		espera_semaforo(id_semaforo);

		memset(destino,0x00,sizeof(destino)); /*reinicio variable*/
		memset(escritura,0x00,sizeof(escritura)); /*reinicio variable*/

		printf("ingrese la ciudad ");
		scanf("%s", destino);
		strcpy(avion.ciudad, destino);

		inAbrirArchivo("aviones.dat", "a+");

		snprintf(escritura, sizeof(escritura), "Avion %d hacia %s\n", avion.nro_avion, avion.ciudad);
		inEscribirArchivo(escritura);
		inCerrarArchivo();
		levanta_semaforo(id_semaforo);
	}
	
	return 0;
}
