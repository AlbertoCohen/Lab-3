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
    int puntos_ganar = 11;
    int nro_finalista;
    int i = 0;
    int finalista_uno = 0, finalista_dos = 0;
    int numero_recibido, numero = 0;
    char cadena[50];

    int done = 0;
    int id_cola_mensajes;

    mensaje msg;

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    borrar_mensajes(id_cola_mensajes);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    printf("Puntos para ganar: %d\n", puntos_ganar);

    while (done == 0)
    {
        pthread_mutex_lock(&mutex);

        recibir_mensaje(id_cola_mensajes, MSG_CANCHA, &msg);

        nro_finalista = msg.int_rte - MSG_FINALISTA;
        numero_recibido = atoi(msg.char_mensaje);
        if (numero_recibido < puntos_ganar)
        {
            switch (msg.int_evento)
            {
            case EVT_PUNTO:

                if (nro_finalista == 0)
                {
                    printf("\n El finalista: %d anoto un punto!\n", nro_finalista + 1);
                    printf("\nEl finalista: %d anoto en total: %d puntos\n", nro_finalista + 1, numero_recibido);
                    printf("\n \n");
                    numero_recibido++;
                    finalista_uno = numero_recibido;
                    sprintf(cadena, "%d", finalista_uno);
                    enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, MSG_CANCHA, EVT_SIGA, cadena);
                }
                if (nro_finalista == 1)
                {
                    printf("\n El finalista: %d anoto un punto!\n", nro_finalista + 1);
                    printf("\nEl finalista: %d anoto en total: %d puntos\n", nro_finalista + 1, numero_recibido);
                    printf("\n \n");
                    numero_recibido++;
                    finalista_dos = numero_recibido;
                    sprintf(cadena, "%d", finalista_dos);
                    enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, MSG_CANCHA, EVT_SIGA, cadena);
                }
                break;
            case EVT_FUERA:
                printf("\n El finalista: %d erro, buena suerte la proxima\n", nro_finalista + 1);
                printf("\n \n");
                sprintf(cadena, "%d", numero_recibido);
                enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, MSG_CANCHA, EVT_SIGA, cadena);
                break;
            default:
                printf("\nfinalista: %d Evento sin definir\n", nro_finalista);
                break;
            }
        }
        else if (numero_recibido == puntos_ganar)
        {
            printf("Empataron! se sortea ganador\n");
            numero = ((rand() % (ROJO - VERDE + 1)) + VERDE);
            if (numero == 0)
            {
                printf("Ganó el finalista %d, felicidades!!\n", numero + 1);
                printf("El otro finalista quedo con %d puntos\n", finalista_dos);
            }
            if (numero == 1)
            {
                printf("Ganó el finalista %d, felicidades!!\n", numero + 1);
                printf("El otro finalista quedo con %d puntos\n", finalista_uno);
            }
            enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, MSG_CANCHA, EVT_FINALIZAR, "FINALIZAR");
            done = 1;
        }
        else
        {
            if (nro_finalista == 0)
            {
                printf("Ganó el finalista: %d felicidades!!\n", nro_finalista + 1);
                printf("El otro finalista quedo con %d puntos\n", finalista_dos);
            }
            if (nro_finalista == 1)
            {
                printf("Ganó el finalista: %d felicidades!!\n", nro_finalista + 1);
                printf("El otro finalista quedo con %d puntos\n", finalista_uno);
            }
            enviar_mensaje(id_cola_mensajes, MSG_FINALISTA + nro_finalista, MSG_CANCHA, EVT_FINALIZAR, "FINALIZAR");
            done = 1;
        }
        pthread_mutex_unlock(&mutex);
    }
    sleep(2);
    return 0;
}
