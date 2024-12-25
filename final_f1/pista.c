#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "memoria.h"
#include "autosT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    int nro_auto;
    int i, numero;
    int aleatorio;
    int cant_autos = 5;
    int numero_recibido;
    int long_pista = 295;
    int intervalo[10] = {0};

    int done = 0;
    int id_cola_mensajes;
    mensaje msg;

    int id_memoria;
    memcop *memoria = NULL;

    memoria = (memcop *)creo_memoria(sizeof(memcop) * CANTIDAD, &id_memoria, CLAVE_BASE);

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    borrar_mensajes(id_cola_mensajes);
    memoria->iniciador = 1;


    while (done == 0)
    {
        recibir_mensaje(id_cola_mensajes, MSG_PISTA, &msg);

        nro_auto = msg.int_rte - MSG_AUTO;

        switch (msg.int_evento)
        {
        case EVT_METROS:
            numero_recibido = atoi(msg.char_mensaje);

            if (numero_recibido <= long_pista)
            {
                numero = ((rand() % (HASTAP - DESDEP + 1)) + DESDEP);
                if (numero == 1)
                {
                    if ((numero_recibido > 50 && numero_recibido <= 100 && intervalo[nro_auto] == 0) ||
                        (numero_recibido > 100 && numero_recibido <= 150 && intervalo[nro_auto] == 1) ||
                        (numero_recibido > 150 && numero_recibido <= 200 && intervalo[nro_auto] == 2) ||
                        (numero_recibido > 250 && intervalo[nro_auto] == 3))
                    {
                        intervalo[nro_auto] = intervalo[nro_auto] + 1;
                        numero = ((rand() % (HASTAB - DESDEB + 1)) + DESDEB);
                        if (numero == 1)
                        {
                            enviar_mensaje(id_cola_mensajes, MSG_AUTO, MSG_PISTA, EVT_BOXES, "ESTAS EN BOXES");
                        }
                    }
                    else
                    {
                        enviar_mensaje(id_cola_mensajes, MSG_AUTO, MSG_PISTA, EVT_SIGA, "CORRE");
                    }
                    printf("\nEl auto: %d recorrió en total: %d metros\n", nro_auto + 1, numero_recibido);
                }
                else
                {
                    printf("\nEl auto numero %d choco y quedo elimando \n", nro_auto + 1);
                    enviar_mensaje(id_cola_mensajes, MSG_AUTO, MSG_PISTA, EVT_FINALIZAR, "FINALIZAR");
                }
            }
            else if (numero_recibido > long_pista)
            {
                enviar_mensaje(id_cola_mensajes, MSG_AUTO + nro_auto, MSG_PISTA, EVT_FINALIZAR_CARRERA, "FINALIZAR");
                printf("Ganó el auto: %d con %d metros recorridos\n", nro_auto + 1, numero_recibido);
                done = 1;
            }

            break;
        default:
            printf("\nauto: %d Evento sin definir\n", nro_auto);
            break;
        }
    }

    usleep(500 * 1000);

    desvincular_memoria((void *)memoria);
    eliminar_memoria(id_memoria);

    return 0;
}
