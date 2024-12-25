#include "mensaje.h"
#include "def.h"
#include "memoria.h"
#include "global.h"
#include "autosT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void *Threadauto(void *parametro)
{
    int nro_auto;
    int done = 0;
    int i;
    int id_cola_mensajes;
    int cant_autos;
    int numero;
    char marca[30];
    char cadena[50];
    mensaje msg;

    tauto *datos_thread = (tauto *)parametro;
    nro_auto = datos_thread->nro_auto;
    id_cola_mensajes = datos_thread->id_colamensaje;
    cant_autos = datos_thread->cant_autos;
    strcpy(marca, datos_thread->marca);

    srand(time(NULL) + nro_auto);
    while (done == 0)
    {
        pthread_mutex_lock(&mutex);
        printf("\nMutex levantado %d\n",nro_auto+1);

        recibir_mensaje(id_cola_mensajes, MSG_AUTO + nro_auto, &msg);

        switch (msg.int_evento)
        {
        case EVT_INICIO:
        case EVT_SIGA:
            if (strcmp(marca, "Ferrari") == 0 || strcmp(marca, "McLaren"))
            {
                numero = ((rand() % (HASTAFE - DESDEFE + 1)) + DESDEFE);
            }
            else
            {
                numero = ((rand() % (HASTAF - DESDEF + 1)) + DESDEF);
            }

            datos_thread->metros_avanzados += numero;

            printf("\nEl auto: %d recorrió en total: %d metros\n", nro_auto + 1, datos_thread->metros_avanzados);

            sprintf(cadena, "%d", datos_thread->metros_avanzados);
            enviar_mensaje(id_cola_mensajes, MSG_PISTA, MSG_AUTO + nro_auto, EVT_METROS, cadena);
            break;

        case EVT_BOXES:
            printf("\nEl auto: %d está en boxes y perderá un turno\n", nro_auto + 1);
            sleep(5);
            break;

        case EVT_FINALIZAR:
            printf("\nauto: %d finalizó\n", nro_auto + 1);
            done = 1;
            break;

        case EVT_FINALIZAR_CARRERA:
            for (i = 0; i < cant_autos; i++)
            {
                enviar_mensaje(id_cola_mensajes, MSG_AUTO + i, MSG_PISTA, EVT_FINALIZAR, "FINALIZAR");
            }
            break;

        default:
            printf("\nauto:%d Evento sin definir\n", nro_auto);
            break;
        }

        printf("\nMutex liberar %d\n",nro_auto+1);
        pthread_mutex_unlock(&mutex);
        sleep(10);
    }
    printf("\nMutex liberar despues de muerto \n");

    pthread_exit((void *)"Listo");
}
