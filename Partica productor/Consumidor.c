#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"


int main() {
    char cadena[LARGO];
    int cant_producto = 0;
    FILE *consumidor;
    
    int id_semaforo;
    id_semaforo = creo_semaforo();
    
    while (1) {
        espera_semaforo(id_semaforo);
        
        consumidor = abrirArchivoR("producto.txt");
        if (consumidor != NULL) {
            printf("\nCONSUMIMOS\n");
            while (!esFinalArchivo(consumidor)) {
                if (leerDesdeArchivo(consumidor, cadena, LARGO)) {
                    printf("%s\n", cadena);
                    usleep(INTERVALO_PRODUCTO * 1000);
                    cant_producto++;
                }
            }
            cerrarArchivo(consumidor);
            if (cant_producto > 0) {
                printf("\nBORRAMOS\n");
                eliminarArchivo("producto.txt");
                cant_producto = 0;
            }
        } else {
            manejarError("Error al abrir producto.txt");
        }
        
        printf("\nESPERAMOS\n");
        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_PARTIDA * 1000);
    }
    
    return 0;
}
