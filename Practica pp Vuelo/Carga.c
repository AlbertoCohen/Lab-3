#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"

int main() {
    char cadena[LARGO];
    int nro_vuelo = 0, nro_pasajeros=0;
    FILE *lote;

    int id_semaforo;
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1) {
        espera_semaforo(id_semaforo);

        lote = abrirArchivoW("lote.dat");
        if (lote != NULL) {
            do{
                nro_vuelo=rand() % CANT_VUELO +1;
                if (nro_vuelo > 0){
                    nro_pasajeros=rand (500 - 150 + 1 ) + 150;
                    nro_vuelo += 1000;
                    escribirEnBuffer(cadena, LARGO, "Nro vuelo: - %04d Cant pasajeros: -%04d\n", nro_vuelo, nro_psajeros);
                    printf("%s", cadena);
                    escribirEnArchivo(lote, cadena);
                }
            } while (nro_vuelo > 0);

            cerrarArchivo(lote);
            printf("\nESPERAMOS\n");

        } else {
            manejarError("Error al abrir el lote.dat");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CARGA * 1000);
    }

    return 0;
}
