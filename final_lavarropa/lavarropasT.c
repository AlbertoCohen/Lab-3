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

void *Threadlavarropa(void *parametro)

{
    int nro_lavarropa;
    int done = 0;
    int i;
    int id_cola_mensajes;
    int cant_lavarropas;

    int color = 0;
    const char *telas[] = {"Nylon", "Algodon"};
    int ropa_lavar = 0;
    int ropa_lavar_total = 0;
    int precio = 0;
    int precio_total = 0;
    int tiempo = 0;
    int tiempo_total = 0;
    int lavados = 0;
    char tela[10];
    unsigned int seed = time(NULL) + nro_lavarropa;

    char cadena[50];
    mensaje msg;

    tlavarropa *datos_thread = (tlavarropa *)parametro;
    nro_lavarropa = datos_thread->nro_lavarropa;
    id_cola_mensajes = datos_thread->id_colamensaje;
    cant_lavarropas = datos_thread->cant_lavarropas;

    while (done == 0)
    {
        recibir_mensaje(id_cola_mensajes, MSG_LAVARROPA + nro_lavarropa, &msg);
        pthread_mutex_lock(&mutex);
        printf("\nMutex levantado %d\n", nro_lavarropa + 1);

        ropa_lavar = ((rand_r(&seed) % (HASTAR - DESDER + 1)) + DESDER);
        color = ((rand_r(&seed) % (HASTAP - DESDEP + 1)) + DESDEP);
        strcpy(tela, telas[rand_r(&seed) % 2]);
        precio = 0;
        tiempo = 0;

        switch (msg.int_evento)
        {
        case EVT_INICIO:
        case EVT_LAVA:

            for (i = 0; i < ropa_lavar; i++)
            {
                if (strcmp(tela, "Nylon") == 0)
                {
                    tiempo = tiempo + 300;
                    precio = precio + 6;
                }
                else if (strcmp(tela, "Algodon") == 0)
                {
                    tiempo = tiempo + 600;
                    precio = precio + 8;
                }
                if (color == 2)
                {
                    precio = precio + 1;
                }
            }
            precio_total = precio_total + precio;
            tiempo_total = tiempo_total + tiempo;
            ropa_lavar_total = ropa_lavar_total + ropa_lavar;
            lavados++;
            printf("\nEl lavarropa: %d lavo %d \n", nro_lavarropa + 1, ropa_lavar);
            printf("\nEl lavarropa: %d tardara %d usegundos\n", nro_lavarropa + 1, tiempo);
            printf("\nEl lavarropa: %d tiene un coste de %d en este lavado\n", nro_lavarropa + 1, precio);

            sprintf(cadena, "%d", precio);
            enviar_mensaje(id_cola_mensajes, MSG_MEGARROPA, MSG_LAVARROPA + nro_lavarropa, EVT_LAVADO, cadena);
            break;

        case EVT_FINALIZAR:
            printf("\nlavarropa: %d finalizó\n", nro_lavarropa + 1);
            done = 1;
            break;

        case EVT_FINALIZAR_LAVADOS:
            for (i = 0; i < cant_lavarropas; i++)
            {
                enviar_mensaje(id_cola_mensajes, MSG_LAVARROPA + i, MSG_MEGARROPA, EVT_FINALIZAR, "FINALIZAR");
            }
            break;

        default:
            printf("\nlavarropa:%d Evento sin definir\n", nro_lavarropa);
            break;
        }

        printf("\nMutex liberar %d\n", nro_lavarropa + 1);
        pthread_mutex_unlock(&mutex);
        usleep(tiempo * 1000);
    }
    printf("\nLavarropa %d lavo en total: %d lavados\n", nro_lavarropa + 1, lavados);
    printf("\nLavarropa %d lavo en total: %d ropas\n", nro_lavarropa + 1, ropa_lavar_total);
    printf("\nLavarropa %d recibio en total: %d pesos\n", nro_lavarropa + 1, precio_total);
    printf("\nLavarropa %d tardo en total: %d usegundos \n", nro_lavarropa + 1, tiempo_total);

    pthread_exit((void *)"Listo");
}
