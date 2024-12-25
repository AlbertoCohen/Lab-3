#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include "clave.h"
#include "def.h"  

key_t creo_clave(int clave_base) {
    key_t generated_key;
    generated_key = ftok("/bin/ls", clave_base);  
    if (generated_key == (key_t)-1) {
        printf("No puedo conseguir clave semáforo, mem compartida, etc.\n");
        exit(ROJO);
    }
    return generated_key;
}
