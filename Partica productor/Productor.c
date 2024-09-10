#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"

int main() {
    char cadena[LARGO];
    int nro_producto = 0, nro_partida = 0;
    FILE *productor;

    int id_semaforo;
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1) {
        espera_semaforo(id_semaforo);

        printf("\nPRODUCIMOS-PARTIDA-%04d\n", nro_partida);
        productor = abrirArchivoA("producto.txt");
        if (productor != NULL) {
            for (nro_producto = 0; nro_producto < CANTIDAD_PARTIDA; nro_producto++) {
                escribirEnBuffer(cadena, LARGO, "PRODUCTO-%04d-%04d\n", nro_partida, nro_producto);
                printf("%s", cadena);
                escribirEnArchivo(productor, cadena);
                usleep(INTERVALO_PRODUCTO * 1000);
            }
            cerrarArchivo(productor);
            nro_partida++;
            printf("\nESPERAMOS\n");
        } else {
            manejarError("Error al abrir producto.txt");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_PARTIDA * 1000);
    }

    return 0;
}
