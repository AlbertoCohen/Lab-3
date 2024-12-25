#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "mensaje.h"
#include "def.h"
#include "clienteT.h"
#include "global.h"

void *Threadcliente(void *parametro)
{
	int nro_cliente;
	int id_cola_mensajes;
	int cant_clientes;

	int done = 0;
	int numero, saldo;
	int i;
	char cadena[50];
	mensaje msg;

	tcliente *datos_thread = (tcliente *)parametro;
	nro_cliente = datos_thread->nro_cliente;
	id_cola_mensajes = datos_thread->id_colamensaje;
	cant_clientes = datos_thread->cant_clientes;

	srand(time(NULL));

	while (done == 0)
	{
		pthread_mutex_lock(&mutex);
		evento = (rand() % (3 - 1 + 1)) + 1;
		numero = (rand() % (HASTA - DESDE + 1)) + DESDE;
		sprintf(cadena, "%d", numero);
		switch (numero)
		{
		case evento = 1:
			printf("El cliente %d va a consultar saldo", nro_cliente);
			enviar_mensaje(id_cola_mensajes, MSG_banco, MSG_cliente + nro_cliente, EVT_CONSULTA_SALDO, "Espero");
			break;
		case evento = 2:
			printf("El cliente %d va a depositar saldo", nro_cliente);
			enviar_mensaje(id_cola_mensajes, MSG_banco, MSG_cliente + nro_cliente, EVT_DEPOSITO, cadena);
			break;
		case evento = 3:
			printf("El cliente %d va a extraer saldo", nro_cliente);
			enviar_mensaje(id_cola_mensajes, MSG_banco, MSG_cliente + nro_cliente, EVT_EXTRACCION, cadena);
			break;
		default:
			printf("Cliente: %d evento sin definir\n", nro_jugador);
			break;
		}
		recibir_mensaje(id_cola_mensajes, MSG_cliente, &msg);

		switch (msg.int_evento)
		{

		case EVT_FINALIZAR:
			printf("CLiente:%d finalizo con %d\n", nro_jugador, saldo);
			done = 1;
			break;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	pthread_exit((void *)"Listo");
}
