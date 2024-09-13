#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"

struct avion
{
int nro_avion;
char ciudad[LARGO];
}avion;

int main() {
    char cadena[LARGO];
    FILE *lista;
    int id_semaforo;
    id_semaforo = creo_semaforo();
    while (1) {
        espera_semaforo(id_semaforo);

        lista = abrirArchivoA("aviones.txt");
        if (lista != NULL) {
            avion.nro_avion =rand();    
            scanf("%s", avion.ciudad);

            escribirEnBuffer(cadena, LARGO, "Nro avion: %d Ciudad: %s\n", avion.nro_avion, avion.ciudad);
            escribirEnArchivo(lista, cadena);
            cerrarArchivo(lista);
            printf("\nESPERAMOS\n");

        }else {
            manejarError("Error al abrir el aviones.txt");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CARGA * 1000);
    }

    return 0;
}
