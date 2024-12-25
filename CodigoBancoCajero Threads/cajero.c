#include <pthread.h>
#include "funciones.h"
#include "definiciones.h"

#define SALIR			0
#define CONSULTA_SALDO 		1
#define DEPOSITO 		2
#define EXTRACCION 		3
#define MAX_MENU		3

			int id_cola_mensajes;
pthread_mutex_t mutex;  

void procesar_evento(mensaje msg);
int menu();
int importe();
int cliente();
void consulta_saldo();
void extraccion();
void deposito();

void *funcionThreadRecibirMensajes (void *parametro)
{
	mensaje	msg;
	printf ("ThreadRecibirMensajes\n");
	while(1)
	{
		recibir_mensaje(id_cola_mensajes, MSG_CAJERO, &msg);
		pthread_mutex_lock (&mutex);
				procesar_evento(msg);
		pthread_mutex_unlock (&mutex);	
	};
	printf ("Hijo  : Termino\n");
	pthread_exit ((void *)"Listo");
}

void procesar_evento(mensaje msg)
{
	int count = 0;
	int cliente=0;
	int importe=0;
	char *token;
	char error[LARGO_TMENSAJE]={0};

	printf("\n------------------------------\n");
	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_RTA_SALDO:
		case EVT_RTA_DEPOSITO_OK:
		case EVT_RTA_EXTRACCION_OK:
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						cliente = atoi(token);
					break; 
					case 1:
						importe = atoi(token);						
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			printf("El saldo del cliente %d es de %d\n", cliente, importe);
		break;
		case EVT_RTA_SALDO_NOK:
		case EVT_RTA_DEPOSITO_NOK:
		case EVT_RTA_EXTRACCION_NOK:
			count = 0;
			token = NULL;
			token = strtok(msg.char_mensaje, "|");
			while (token != NULL)
			{
				switch (count)
				{
					case 0:
						cliente = atoi(token);
					break; 
					case 1:
						strcpy(error, token);						
					break;
				}
				token = strtok(NULL,"|");
				count++;
		    	}
			printf("Error %d %s\n", cliente, error);
		break;
			
		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printf("------------------------------\n");
}



int menu(void)
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tConsula\n");
    printf("2.\tDeposito\n");
    printf("3.\tExtraccion\n");
    printf("0.\tSalir\n\n");
    printf("Elija opcion: ");
    fflush(stdin);  
    while( (scanf(" %d", &opcion) != 1)
          || (opcion < 0)            
          || (opcion > MAX_MENU))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Elija opcion: ");
    }
    return opcion;
}

int importe()
{ 
    int importe = 0;
    fflush(stdin);  
    printf("Importe: ");
    while( (scanf(" %d", &importe) != 1))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Importe: ");
    }
    return importe;
} 

int cliente()
{ 
    int cliente = 0;
    fflush(stdin);  
    printf("Cliente: ");
    while( (scanf(" %d", &cliente) != 1))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Cliente: ");
    }
    return cliente;
} 

void consulta_saldo()
{
	char 	cadena[LARGO_TMENSAJE];
	int cli;
	mensaje	msg;
	printf("Consulta Saldo:\n");
	cli = cliente();
	sprintf(cadena, "%d", cli);
	pthread_mutex_lock (&mutex);
		enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_CONSULTA_SALDO, cadena);
	pthread_mutex_unlock (&mutex);
}

void deposito()
{
	char 	cadena[LARGO_TMENSAJE];
	int imp;
	int cli;
	mensaje	msg;
	printf("Deposito:\n");
	cli = cliente();	
	imp = importe();
	sprintf(cadena, "|%d|%d", cli, imp);
	pthread_mutex_lock (&mutex);
		enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_DEPOSITO, cadena);
	pthread_mutex_unlock (&mutex);
}

void extraccion()
{

	char 	cadena[LARGO_TMENSAJE];
	int imp;
	int cli;
	mensaje	msg;
	printf("Extraccion:\n");
	cli = cliente();
	imp = importe();
	sprintf(cadena, "|%d|%d", cli, imp);
	pthread_mutex_lock (&mutex);
		enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_EXTRACCION, cadena);
	pthread_mutex_unlock (&mutex);
}

int main()
{
	int 			opcion;    
	int 			id_memoria_codigos;
	mensaje			msg;
	int 			codigo;
	int				cantidad;
	char 			cadena[LARGO_TMENSAJE];

	pthread_t 		idHilo;
	pthread_attr_t 	atributos;

	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	if (pthread_create (&idHilo, &atributos, funcionThreadRecibirMensajes, NULL)!= 0)
	{
		perror ("No puedo crear thread");
		exit (-1);
	}

	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	
	pthread_mutex_init (&mutex, NULL);
	
	opcion = menu();  

	while(opcion!= SALIR)   
	{
		switch(opcion)
		{
			case CONSULTA_SALDO: 
			    consulta_saldo();
			    break;
			case DEPOSITO: 
    			    deposito();
			    break;
			case EXTRACCION: 
    			    extraccion();
			    break;
			case SALIR: 
			    printf("Salir:\n");
			    break;
			default:    
			    printf("Opcion no valida\n");
		}
		opcion = menu(); 
	}
	
	return 0;
}

    
