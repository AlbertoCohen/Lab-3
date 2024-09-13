#include <sys/ipc.h>
#include <sys/sem.h>
#include "clave.h"
#include <stdio.h>
#include "semaforos.h"
#include "def.h"
#include <unistd.h>

int main(void)
{
int id_semaforo;
id_semaforo = creo_semaforo();
inicia_semaforo(id_semaforo, VERDE);
while(1)
{
espera_semaforo(id_semaforo);
printf("Seccion critica\n");
sleep (1);
levanta_semaforo(id_semaforo);
sleep (10);
}
return 0;
}
