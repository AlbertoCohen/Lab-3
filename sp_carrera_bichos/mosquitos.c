#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "mosquitosT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int cant_mosquitos = 3;
    int i;
    int id_cola_mensajes;

    pthread_t *idHilo;
    tmosquito *datos_thread;
    pthread_attr_t atributos;

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    datos_thread = (tmosquito *)malloc(sizeof(tmosquito) * cant_mosquitos);
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cant_mosquitos);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < cant_mosquitos; i++)
    {
        datos_thread[i].nro_mosquito = i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        datos_thread[i].cant_mosquitos = cant_mosquitos;
        datos_thread[i].metros_avanzados = 0; 
        pthread_create(&idHilo[i], &atributos, &Threadmosquito, &datos_thread[i]);
        enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + i, MSG_PISTA, EVT_INICIO, "CORRE");
    }

    for (i = 0; i < cant_mosquitos; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("Finalizó el mosquito: %d\n", datos_thread[i].nro_mosquito);
    }

    free(idHilo);
    free(datos_thread);
    return 0;
}
