#include "mensaje.h"
#include "def.h"
#include "memoria.h"
#include "global.h"
#include "lavarropasT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int cant_lavarropas = 3;
    int i;

    int id_cola_mensajes;

    pthread_t *idHilo;
    tlavarropa *datos_thread;
    pthread_attr_t atributos;

    int id_memoria;
    memcop *memoria = NULL;

    memoria = (memcop *)creo_memoria(sizeof(memcop) * CANTIDAD, &id_memoria, CLAVE_BASE);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    datos_thread = (tlavarropa *)malloc(sizeof(tlavarropa) * cant_lavarropas);
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cant_lavarropas);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    while (memoria->iniciador != 1)
    {
        usleep(1);
    }

    srand(time(NULL));
    for (i = 0; i < cant_lavarropas; i++)
    {
        datos_thread[i].nro_lavarropa = i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        datos_thread[i].cant_lavarropas = cant_lavarropas;

        pthread_create(&idHilo[i], &atributos, &Threadlavarropa, &datos_thread[i]);
        enviar_mensaje(id_cola_mensajes, MSG_LAVARROPA + i, MSG_MEGARROPA, EVT_INICIO, "CORRE");
    }

    for (i = 0; i < cant_lavarropas; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("Finalizó el lavarropa: %d\n", datos_thread[i].nro_lavarropa + 1);
    }

    free(idHilo);
    free(datos_thread);
    pthread_mutex_destroy(&mutex);

    desvincular_memoria((void *)memoria);
    eliminar_memoria(id_memoria);
    return 0;
}
