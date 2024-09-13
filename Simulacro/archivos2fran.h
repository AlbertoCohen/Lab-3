#ifndef _ARCHIVOS
#define _ARCHIVOS

int inAbrirArchivo(char *nombreArchivo, char *modo);
void inCerrarArchivo();
int inRenombrarArchivo(char *nombreViejoArchivo, char *nombreNuevoArchivo);
int inEscribirArchivo(char *szTexto); /*este esta mal, no se pq pero no me funciona*/
void inLeerArchivoCompleto(); /*este esta mal, tengo que hacer que devuelva una linea del archivo.  despues en mi main lo llamaré en un bucle para que se muestren todas las lineas que quiero*/

#endif
