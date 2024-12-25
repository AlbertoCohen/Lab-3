#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "finalistasT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int cant_finalistas = 2;
    int i;
    int id_cola_mensajes;
    char cadena[30];
    

    pthread_t *idHilo;
    tfinalista *datos_thread;
    pthread_attr_t atributos;

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    datos_thread = (tfinalista *)malloc(sizeof(tfinalista) * cant_finalistas);
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cant_finalistas);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    sprintf(cadena, "%d", 0);
    for (i = 0; i < cant_finalistas; i++)
    {
        datos_thread[i].nro_finalista = i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        datos_thread[i].cant_finalistas = cant_finalistas;
        datos_thread[i].puntos = 0;
        pthread_create(&idHilo[i], &atributos, &Threadfinalista, &datos_thread[i]);
        enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + i, MSG_CANCHA, EVT_INICIO, cadena);
    }

    for (i = 0; i < cant_finalistas; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("Finalizó el finalista: %d\n", datos_thread[i].nro_finalista);
    }

    free(idHilo);
    free(datos_thread);
    return 0;
}
