#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"

int main() {
    char cadena[LARGO];
    int cant_producto = 0, cod_producto = 0, precio = 0, total = 0;
    FILE *ticket;

    int id_semaforo;
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1) {
        espera_semaforo(id_semaforo);

        ticket = abrirArchivoW("ticket.txt");
        if (ticket != NULL) {

            printf("\ningrese el codigo del producto: \n");
            scanf("%04d", &cod_producto);
            printf("\ningrese cant del producto: \n");
            scanf("%04d", &cant_producto);
            printf("\ningrese precio del producto: \n");
            scanf("%04d", &precio);

            total = cant_producto * precio;

            escribirEnBuffer(cadena, LARGO, "%d\n", total);
            printf("El total de la compra es: %d\n", total);
            escribirEnArchivo(ticket, cadena);


            cerrarArchivo(ticket);
            printf("\nGracias por su compra\n");

        } else {
            manejarError("Error al abrir el ticket.txt");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CARGA * 1000);
    }

    return 0;
}
