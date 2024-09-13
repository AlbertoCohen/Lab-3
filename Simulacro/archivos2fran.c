#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "def.h"
#include "archivos.h"


FILE *fp;

int inAbrirArchivo(char *nombreArchivo, char *modo){ /*modo sería w+, a+, etcetc*/
    fp = fopen(nombreArchivo, modo); /*devuelve puntero*/
    if(fp == NULL){
        printf("Error apertura de archivo\n");
        return FALSE;
    } else {
        return TRUE;
    }
}

void inCerrarArchivo(){ /*cerrar archivo*/
    fclose(fp);
}

int inRenombrarArchivo(char *nombreViejoArchivo, char *nombreNuevoArchivo) { /*renombra el un archivo con el nombre viejo y el nombre nuevo */
    return rename(nombreViejoArchivo, nombreNuevoArchivo);
}

int inEscribirArchivo(char *szTexto){ /*este está mal, no se pq no funciona*/
    return fprintf(fp, "%s", szTexto);
}

void inLeerArchivoCompleto(){  /*este esta mal, tengo que hacer que devuelva una linea del archivo.  despues en mi main lo llamaré en un bucle para que se muestren todas las lineas que quiero*/
    char linea[100];
    while (fgets(linea, sizeof(linea), fp)) {
        printf("%s", linea);
    }
}
