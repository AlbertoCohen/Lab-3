#include "funciones.h"
#include "definiciones.h"

#define MAX_CLIENTE 10
 
void procesar_evento(int id_cola_mensajes, mensaje msg, int *saldos)
{
	char 	cadena[LARGO_TMENSAJE];
	int 	count = 0;
	int	cliente=0;
	int 	importe=0;
	char 	*token;
	int	i;

	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_CONSULTA_SALDO:
			printf("Consulta saldo\n");
			cliente = atoi(msg.char_mensaje); 
			if (cliente >= 0 && cliente <MAX_CLIENTE)
			{
				sprintf(cadena, "%d|%d", cliente, saldos[cliente]);
				printf("%s\n", cadena);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_SALDO, cadena);
			}
			else
			{
				sprintf(cadena, "%d|NO EXISTE", cliente);
				printf("%s\n", cadena);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_SALDO_NOK, cadena);
			}
		break;	
		case EVT_DEPOSITO:
			printf("Deposito\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						cliente=atoi(token);
						printf("CLI:%d", cliente);
					break; 
					case 1:
						importe=atoi(token);
						printf(" IMP:%d\n", importe); 
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			if (cliente >= 0 && cliente <MAX_CLIENTE)
			{
				saldos[cliente]+=importe;
				sprintf(cadena, "%d|%d", cliente, saldos[cliente]);
				printf("%s\n", cadena);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_OK, cadena);
			}
			else
			{
				sprintf(cadena, "%d|NO EXISTE", cliente);
				printf("%s\n", cadena);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_NOK, cadena);
			}
		break;
		case EVT_EXTRACCION:
			printf("Extraccion\n");
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						cliente=atoi(token);
						printf("CLI:%d", cliente);
					break; 
					case 1:
						importe=atoi(token);
						printf(" IMP:%d\n", importe); 
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			if (cliente >= 0 && cliente <MAX_CLIENTE)
			{
				if(saldos[cliente]>=importe)
				{ 				
					saldos[cliente]-=importe;
					sprintf(cadena, "%d|%d", cliente, saldos[cliente]);
					printf("%s\n", cadena);
					enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_OK, cadena);
				}
				else
				{ 
					sprintf(cadena, "%d|SALDO INSUFICIENTE", cliente);
					printf("%s\n", cadena);
					enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, cadena);
				}
			}
			else
			{
				sprintf(cadena, "%d|NO EXISTE", cliente);
				printf("%s\n", cadena);
				enviar_mensaje(id_cola_mensajes , msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, cadena);
			}
		break;
		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printf("------------------------------\n");
	for(i=0; i<MAX_CLIENTE; i++)
				printf("[%d]$%d\n", i, saldos[i]);
}
		
int main()
{
	int 			id_cola_mensajes;
	int			i;
	int 			saldos[MAX_CLIENTE]={0};

	mensaje			msg;

	
	int cantidad = 0;
	
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes); //Borra todos los mensajes que haya en la cola.

	while(1)
	{
		recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);
		procesar_evento(id_cola_mensajes, msg, saldos);
		
	};
	
	return 0;
}



