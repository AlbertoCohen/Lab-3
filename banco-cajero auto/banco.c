#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mensaje.h"
#include "def.h"
#include "clienteT.h"

int main(int argc, char *argv[])
{
	typedef struct cliente
	{
		int cliente;
		int saldo = 0;
	} scliente;

	int id_cola_mensajes;
	int nro_cliente;
	int cant_clientes;
	mensaje msg;

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	


	recibir_mensaje(id_cola_mensajes, MSG_banco, &msg);

	nro_cliente = msg.int_rte - MSG_cliente;

	switch (msg.int_evento)
	{
	case EVT_RTA_SALDO:

	case EVT_RTA_SALDO_NOK:

	case EVT_RTA_DEPOSITO_OK:

	case EVT_RTA_DEPOSITO_NOK:

	case EVT_RTA_EXTRACCION_OK:

	case EVT_RTA_EXTRACCION_NOK:
	}
	sleep(1);
};

return 0;
}
