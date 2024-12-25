#include "mensaje.h"
#include "def.h"
#include "global.h"
#include "mosquitosT.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int long_pista = 95;
    int nro_mosquito;
    int i;
    int mosquito_uno = 0, mosquito_dos = 0, humo = 0;
    int cant_mosquitos = 3;
    int numero_recibido;

    int done = 0;
    int id_cola_mensajes;
    mensaje msg;

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    borrar_mensajes(id_cola_mensajes);

    printf("Longitud de la pista: %d metros\n", long_pista);

    while (done == 0)
    {
        recibir_mensaje(id_cola_mensajes, MSG_PISTA, &msg);

        nro_mosquito = msg.int_rte - MSG_MOSQUITO;

        switch (msg.int_evento)
        {
        case EVT_METROS:
            numero_recibido = atoi(msg.char_mensaje);
            if (numero_recibido <= long_pista)
            {
                if (nro_mosquito == 0)
                {
                    printf("\nEl mosquito: %d recorrió en total: %d metros\n", nro_mosquito + 1, numero_recibido);
                    mosquito_uno = numero_recibido;
                }
                else if (nro_mosquito == 1)
                {
                    printf("\nEl mosquito: %d recorrió en total: %d metros\n", nro_mosquito + 1, numero_recibido);
                    mosquito_dos = numero_recibido;
                }
                else if (nro_mosquito == 2)
                {
                    printf("\nEl humo recorrió en total: %d metros\n", numero_recibido);
                    humo = numero_recibido;

                    if (humo > mosquito_uno)
                    {
                        printf("\nEl humo mató al mosquito uno\n");
                        enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + 0, MSG_PISTA, EVT_FINALIZAR, "FINALIZAR");
                    }
                    if (humo > mosquito_dos)
                    {
                        printf("\nEl humo mató al mosquito dos\n");
                        enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + 1, MSG_PISTA, EVT_FINALIZAR, "FINALIZAR");
                    }
                    
                    for (i = 0; i < cant_mosquitos; i++)
                    {
                        enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + i, MSG_PISTA, EVT_SIGA, "CORRE");
                    }
                }
            }

            if (numero_recibido > long_pista)
            {
                enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + nro_mosquito, MSG_PISTA, EVT_FINALIZAR_CARRERA, "FINALIZAR");
                printf("Ganó el mosquito: %d con %d metros recorridos\n", nro_mosquito, numero_recibido);
                done = 1;
            }
            break;
        default:
            printf("\nMosquito: %d Evento sin definir\n", nro_mosquito);
            break;
        }
    }
    sleep(2);
    return 0;
}
