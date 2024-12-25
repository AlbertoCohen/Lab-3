#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "mosquitosT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *Threadmosquito(void *parametro)
{
    int nro_mosquito;
    int done = 0;
    int i;
    int id_cola_mensajes;
    int cant_mosquitos;
    int numero;
    char cadena[50];
    mensaje msg;

    tmosquito *datos_thread = (tmosquito *)parametro;
    nro_mosquito = datos_thread->nro_mosquito;
    id_cola_mensajes = datos_thread->id_colamensaje;
    cant_mosquitos = datos_thread->cant_mosquitos;

    srand(time(NULL) + nro_mosquito);
    while (done == 0)
    {
        pthread_mutex_lock(&mutex);
        printf("\nMutex levantado\n");

        recibir_mensaje(id_cola_mensajes, MSG_MOSQUITO + nro_mosquito, &msg);

        switch (msg.int_evento)
        {
        case EVT_INICIO:
        case EVT_SIGA:
            if (nro_mosquito == 0 || nro_mosquito == 1)
            {
                numero = ((rand() % (HASTAM - DESDEM + 1)) + DESDEM);
            }
            else if (nro_mosquito == 2)
            {
                numero = ((rand() % (HASTAH - DESDEH + 1)) + DESDEH);
            }

            datos_thread->metros_avanzados += numero;

            if (nro_mosquito == 0 || nro_mosquito == 1)
            {
                printf("\nEl mosquito: %d recorrió en total: %d metros\n", nro_mosquito + 1, datos_thread->metros_avanzados);
            }
            else if (nro_mosquito == 2)
            {
                printf("\nEl humo recorrió en total: %d metros\n", datos_thread->metros_avanzados);
            }

            sprintf(cadena, "%d", datos_thread->metros_avanzados);
            enviar_mensaje(id_cola_mensajes, MSG_PISTA, MSG_MOSQUITO + nro_mosquito, EVT_METROS, cadena);
            break;

        case EVT_FINALIZAR:
            printf("\nMosquito:%d finalizó\n", nro_mosquito);
            done = 1;
            break;
        case EVT_FINALIZAR_CARRERA:
        for (i = 0; i < cant_mosquitos; i++)
            {
                enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + nro_mosquito, MSG_PISTA, EVT_FINALIZAR, "FINALIZAR");
            }
            break;

        default:
            printf("\nMosquito:%d Evento sin definir\n", nro_mosquito);
            break;
        }

        printf("\nMutex liberar\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_exit((void *)"Listo");
}
