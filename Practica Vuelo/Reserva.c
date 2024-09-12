#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"


int main() {
    char cadena[LARGO];
   int nro_vuelo = 0, nro_pasajeros=0, cont=0, cont_lote=1;
   int nro_vuelot = 0, nro_pasajerost=0;
    FILE *lote;
    
    int id_semaforo;
    id_semaforo = creo_semaforo();
    
    while (1) {
        espera_semaforo(id_semaforo);
        
       lote = abrirArchivoR("lote.dat");
        if (lote != NULL) {
            printf("\nAnalizamos\n");
            while (!esFinalArchivo(lote)) {
                leerDesdeArchivo(lote, "%d %d", 2 , &nro_pasajerost, &nro_vuelot);
                nro_pasajeros+= nro_pasajerost;
                nro_vuelo+= nro_vuelo;
                cont++;
                printf("%d Nro vuelo: - %04d Cant pasajeros: -%04d\n",cont, nro_vuelo, nro_psajeros);
            }
            cerrarArchivo(lote);
            cont_lote++;
            escribirEnBuffer(cadena, LARGO,"lote %d",cont_lote);
            renombrarArchivo(lote,cadena);
            printf("Cerrado lote nro: %d", cont_lote);
        } else {
            manejarError("Error al abrir producto.txt");
        }
        
        printf("\nESPERAMOS\n");
        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CARGA * 1000);
    }
    
    return 0;
}
