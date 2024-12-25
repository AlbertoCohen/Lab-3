#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "archivos.h"
#include "clave.h"
#include "semaforos.h"

void proceso_caja(int id_semaforo, int tipo_caja);

int main(int argc, char *argv[]) {
    int tipo_caja, id_semaforo;
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <tipo_caja>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tipo_caja = atoi(argv[1]);
    id_semaforo = creo_semaforo();

    proceso_caja(id_semaforo, tipo_caja);

    return 0;
}

void proceso_caja(int id_semaforo, int tipo_caja) {
    FILE *ticket;
    int total = 0;

    while (1) {
        espera_semaforo(id_semaforo);

        ticket = abrirArchivoR("ticket.txt");
        if (ticket != NULL) {
            leerDesdeArchivo("ticket.txt", "d", 1, &total);
            cerrarArchivo(ticket);
            if (tipo_caja == 1 && total < 20000) {
                printf("\nEl total de la compra es: %d\n", total);
            } else if (tipo_caja == 2 && total >= 20000) {
                printf("\nEl total de la compra es: %d\n", total);
            }
        } else {
            manejarError("Error al abrir el ticket.txt");
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO_CARGA * 1000);
    }
}
