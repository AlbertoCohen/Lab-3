#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "def.h"
#include "clienteT.h"
#include "global.h"
#include "mensaje.h"

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    borrar_mensajes(id_cola_mensajes);
    int i, cant_clientes;
    pthread_t *idHilo;
    tcliente *datos_thread;
    pthread_attr_t atributos;

    printf("Ingrese cantidad de clientes: \n");
    scanf("%d", &cant_clientes);
    printf("Cantidad de clientes %d \n\n", cant_clientes);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    datos_thread = (tcliente *)malloc(sizeof(tcliente) * cant_clientes);
    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cant_clientes);

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < cant_clientes; i++)
    {
        datos_thread[i].nro_cliente = i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        datos_thread[i].cant_clientes = cant_clientes;

        pthread_create(&idHilo[i], &atributos, &Threadcliente, &datos_thread[i]);
    }

    for (i = 0; i < cant_clientes; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("Salio el cliente: %d \n", datos_thread[i].nro_cliente);
    }

    free(idHilo);
    free(datos_thread);

    return 0;
}
