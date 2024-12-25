#include "mensaje.h"
#include "def.h"
#include <pthread.h>
#include <stdio.h>   
#include <stdlib.h>   
#include <time.h>    

int main(int argc, char *argv[])
{
	int pienso_un_numero;
	int id_cola_mensajes;
	int numero_recibido;
	int nro_jugador;
	int cant_jugadores;
	int done = 0;
	mensaje msg;

	srand(time(NULL));
	pienso_un_numero = (rand() % (DESDE - HASTA + 1)) + DESDE;

	printf("Pense este numero %d\n", pienso_un_numero);

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);

	while (done == 0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PIENSO, &msg); 
	
		nro_jugador = msg.int_rte - MSG_JUGADOR;	

		switch (msg.int_evento)
		{
		case EVT_NUMERO:

			numero_recibido = atoi(msg.char_mensaje);

			if (numero_recibido == pienso_un_numero)
			{
				enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_PIENSO, EVT_ACERTO, "FINALIZAR");
				printf("Jugador:%d ", nro_jugador);
				printf("Has ganado! con el número %d ", numero_recibido);
				done = 1;
			}
			else
			{
				enviar_mensaje(id_cola_mensajes, MSG_JUGADOR, MSG_PIENSO, EVT_NO_ACERTO, "FINALIZAR");
			}

			break;
		default:
			printf("\nPienso:%d Evento sin definir\n", nro_jugador);
			break;
		}
	};

	return 0;
}
