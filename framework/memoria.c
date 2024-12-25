#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "clave.h"
#include "def.h"
#include "memoria.h"

void *creo_memoria(int size, int *r_id_memoria, int clave_base)
{
    void *ptr_memoria;
    int id_memoria;
    id_memoria = shmget(creo_clave(clave_base), size, 0777 | IPC_CREAT);
    if (id_memoria == -1)
    {
        printf("No consigo id para memoria compartida\n");
        exit(0);
    }
    ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);
    if (ptr_memoria == NULL)
    {
        printf("No consigo memoria compartida\n");
        exit(0);
    }
    *r_id_memoria = id_memoria;

    return ptr_memoria;
}

void inicializar_memoria(void *ptr_memoria, const char *data, int size)
{
    char *memoria = (char *)ptr_memoria;
    int i;
    printf("Inicializando memoria compartida...\n");
    for (i = 0; i < size; i++)
    {
        memoria[i] = data[i];
    }
    printf("Memoria compartida inicializada.\n");
}

void leer_memoria(void *ptr_memoria, int size)
{
    char *memoria = (char *)ptr_memoria;
    int i;

    printf("Leyendo memoria compartida:\n");
    for (i = 0; i < size; i++)
    {
        printf("%c", memoria[i]);
    }
    printf("\n");
}

void desvincular_memoria(void *memoria)
{
    if (shmdt(memoria) == -1)
    {
        perror("Error al desvincular memoria compartida");
        exit(1);
    }
    printf("Memoria compartida desvinculada correctamente.\n");
}

void eliminar_memoria(int id_memoria)
{
    if (shmctl(id_memoria, IPC_RMID, NULL) == -1)
    {
        perror("Error al eliminar memoria compartida");
        exit(1);
    }
    printf("Memoria compartida eliminada correctamente.\n");
}
