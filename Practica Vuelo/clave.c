#include <sys/ipc.h>
#include "clave.h"
#include "def.h"
#include "stdlib.h"
key_t creo_clave(void) {
key_t clave;
clave = ftok ("/bin/ls",CLAVE_BASE);
if (clave == (key_t)-1)
{
printf("No puedo conseguir clave semáforo, mem compartida, etc.\n");
exit(0);
}
return clave;
}