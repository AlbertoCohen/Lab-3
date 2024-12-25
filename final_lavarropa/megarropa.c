#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "lavarropasT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    int nro_lavarropa;

    int numero_recibido;
    int long_megarropa = 295;
    int intervalo[10] = {0};

    int precio = 0;
    int ordenes = 0;
    int llevados = 0;

    int done = 0;
    int id_cola_mensajes;
    mensaje msg;

    int id_memoria;
    memcop *memoria = NULL;

    memoria = (memcop *)creo_memoria(sizeof(memcop) * CANTIDAD, &id_memoria, CLAVE_BASE);

    srand(time(NULL));

    ordenes = ((rand() % (HASTAO - DESDEO + 1)) + DESDEO);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    borrar_mensajes(id_cola_mensajes);
    memoria->iniciador = 1;

    while (done == 0)
    {
        recibir_mensaje(id_cola_mensajes, MSG_MEGARROPA, &msg);

        nro_lavarropa = msg.int_rte - MSG_LAVARROPA;

        switch (msg.int_evento)
        {
        case EVT_LAVADO:
            numero_recibido = atoi(msg.char_mensaje);
            precio = precio + numero_recibido;
            if (ordenes > 0)
            {
                ordenes--;
                llevados++;
                enviar_mensaje(id_cola_mensajes, MSG_LAVARROPA+nro_lavarropa, MSG_MEGARROPA, EVT_LAVA, "LAVANDO");
                printf("\n Mensaje enviado lava al lavarropa: %d\n", nro_lavarropa + 1);
            }
            else
            {
                enviar_mensaje(id_cola_mensajes, MSG_LAVARROPA+nro_lavarropa, MSG_MEGARROPA, EVT_FINALIZAR_LAVADOS, "FINALIZAR");
                done = 1;
            }
            printf("\nLavados llevados: %d \n", llevados);
            printf("\nPesos recibidos hasta el momento: %d\n", precio);

            break;
        default:
            printf("\nLavarropa: %d Evento sin definir\n", nro_lavarropa + 1);
            break;
        }
    }

    usleep(500 * 1000);

    desvincular_memoria((void *)memoria);
    eliminar_memoria(id_memoria);

    return 0;
}
