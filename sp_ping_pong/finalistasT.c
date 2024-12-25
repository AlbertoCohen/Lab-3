#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "finalistasT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *Threadfinalista(void *parametro)
{
    int nro_finalista;
    int done = 0;
    int i;
    int id_cola_mensajes;
    int cant_finalistas;
    int numero;
    int numero_recibido;
    char cadena[50];
    mensaje msg;

    tfinalista *datos_thread = (tfinalista *)parametro;
    nro_finalista = datos_thread->nro_finalista;
    id_cola_mensajes = datos_thread->id_colamensaje;
    cant_finalistas = datos_thread->cant_finalistas;

    srand(time(NULL) + pthread_self());
    while (done == 0)
    {
        pthread_mutex_lock(&mutex);
        printf("\nMutex levantado\n");

        recibir_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, &msg);
        numero_recibido = atoi(msg.char_mensaje);
        datos_thread->puntos = numero_recibido;
        switch (msg.int_evento)
        {
        case EVT_INICIO:
        case EVT_SIGA:

            numero = ((rand() % (HASTAP - DESDEP + 1)) + DESDEP);

            printf("\nEl finalista: %d anoto en total: %d puntos\n", nro_finalista + 1, datos_thread->puntos);
            printf("\nEl finalista: %d pega\n", nro_finalista);

            sprintf(cadena, "%d", datos_thread->puntos);
            enviar_mensaje(id_cola_mensajes, MSG_CANCHA, MSG_FINALISTA + nro_finalista, numero, cadena);
            break;

        case EVT_FINALIZAR:
            for (i = 0; i < cant_finalistas; i++)
            {
                enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, MSG_CANCHA, EVT_FINALIZAR, "FINALIZAR");
            }
            printf("\nEl finalista: %d finalizo\n", nro_finalista);
            break;

        default:
            printf("\nfinalista:%d Evento sin definir\n", nro_finalista);
            break;
        }

        printf("\nMutex liberar\n");
        printf("\n \n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_exit((void *)"Listo");
}
