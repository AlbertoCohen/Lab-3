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

int main(int argc, char *argv[]){
    FILE *lista;
    int id_semaforo;
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1) {
        espera_semaforo(id_semaforo);
        lista = abrirArchivoR("aviones.txt");

        if (lista != NULL) {
            printf("\nActualizamos: \n");
            leerTodoElArchivo(lista);
            cerrarArchivo(lista);
            lista = abrirArchivoW("aviones.txt");
            cerrarArchivo(lista);
        } else {
            manejarError("Error al abrir la lista.txt");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CARGA * 1000);
    }

    return 0;
}
