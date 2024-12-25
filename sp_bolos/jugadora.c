#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "def.h"
#include "jugadorT.h"
#include "global.h"
#include "mensaje.h"

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int i, cant_jugadores;
    pthread_t *idHilo;
    tjugador *datos_thread;
    pthread_attr_t atributos;

    printf("Ingrese cantidad de jugadores: \n");
    scanf("%d", &cant_jugadores);
    printf("Cantidad de jugadores %d \n\n", cant_jugadores);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    datos_thread = (tjugador *)malloc(sizeof(tjugador) * cant_jugadores);
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cant_jugadores);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < cant_jugadores; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        datos_thread[i].cant_jugadores = cant_jugadores;

        pthread_create(&idHilo[i], &atributos, &ThreadJugador, &datos_thread[i]);
    }

    for (i = 0; i < cant_jugadores; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("Finalizo el jugador: %d \n", datos_thread[i].nro_jugador);
    }

    free(idHilo);
    free(datos_thread);

    return 0;
}
