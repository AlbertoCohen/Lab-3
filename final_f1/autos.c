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

int main(int argc, char *argv[])
{
    int cant_autos = 5;
    int i;
    const char *marcas[] = {"Ferrari", "McLaren", "Mercedes", "Red Bull", "Renault"};

    int id_cola_mensajes;

    pthread_t *idHilo;
    tauto *datos_thread;
    pthread_attr_t atributos;

    int id_memoria;
    memcop *memoria = NULL;

    memoria = (memcop *)creo_memoria(sizeof(memcop) * CANTIDAD, &id_memoria, CLAVE_BASE);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    datos_thread = (tauto *)malloc(sizeof(tauto) * cant_autos);
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cant_autos);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);


    while (memoria->iniciador != 1)
    {
        usleep(1);
    }

    srand(time(NULL));
    for (i = 0; i < cant_autos; i++)
    {
        datos_thread[i].nro_auto = i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        datos_thread[i].cant_autos = cant_autos;
        datos_thread[i].metros_avanzados = 0;
        strcpy(datos_thread[i].marca, marcas[rand() % 5]);
        pthread_create(&idHilo[i], &atributos, &Threadauto, &datos_thread[i]);
        enviar_mensaje(id_cola_mensajes, MSG_AUTO + i, MSG_PISTA, EVT_INICIO, "CORRE");
    }

    for (i = 0; i < cant_autos; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("Finalizó el auto: %d\n", datos_thread[i].nro_auto + 1);
    }

    free(idHilo);
    free(datos_thread);

    desvincular_memoria((void *)memoria);
    eliminar_memoria(id_memoria);
    return 0;
}
