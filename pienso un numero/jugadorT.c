#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "mensaje.h"
#include "def.h"
#include "jugadorT.h"
#include "global.h"

void *ThreadJugador(void *parametro)
{
	int nro_jugador;
	int id_cola_mensajes;
	int cant_jugadores;

	int done = 0;
	int numero;
	int cant_intentos = 0;
	int i;
	char cadena[50];
	mensaje msg;

	tjugador *datos_thread = (tjugador *)parametro;
	nro_jugador = datos_thread->nro_jugador;
	id_cola_mensajes = datos_thread->id_colamensaje;
	cant_jugadores = datos_thread->cant_jugadores;

	srand(time(NULL));

	while (done == 0)
	{
		pthread_mutex_lock(&mutex);
		printf("\nmutex levantado \n");
		numero = (rand() % (HASTA - DESDE + 1)) + DESDE;
		printf("\nJugador:%d Envia el numero:%d  A ver si le pegue!\n", nro_jugador, numero);

		sprintf(cadena, "%d", numero);

		enviar_mensaje(id_cola_mensajes, MSG_PIENSO, MSG_JUGADOR + nro_jugador, EVT_NUMERO, cadena);
		cant_intentos++;

		recibir_mensaje(id_cola_mensajes, MSG_JUGADOR, &msg);

		switch (msg.int_evento)
		{
		case EVT_ACERTO:
			printf("\nAcerte: Con %d Cantidad de intentos \n", cant_intentos);
			for (i = 0; i < cant_jugadores; i++)
			{
				enviar_mensaje(id_cola_mensajes, MSG_JUGADOR, MSG_JUGADOR + i, EVT_FINALIZAR, "FINALIZAR");
			}
			done = 1;
			break;
		case EVT_NO_ACERTO:
			printf("Jugador: %d Pucha, sigo intentando! \n", nro_jugador);
			break;
		case EVT_FINALIZAR:
			printf("\nJugador:%d Finalizo\n", nro_jugador);
			done = 1;
			break;
		default:
			printf("\nJugador:%d Evento sin definir\n", nro_jugador);
			break;
		}
		printf("\nmutex liberar \n");
		pthread_mutex_unlock (&mutex);
		sleep(1);
	}

	pthread_exit((void *)"Listo");
}
