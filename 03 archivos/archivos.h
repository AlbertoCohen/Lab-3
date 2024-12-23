#ifndef _ARCHIVOS
#define _ARCHIVOS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

FILE* abrirArchivoW(const char *nombre);
FILE* abrirArchivoR(const char *nombre);
FILE* abrirArchivoA(const char *nombre);
FILE* abrirArchivoWPlus(const char *nombre);
FILE* abrirArchivoRPlus(const char *nombre);
FILE* abrirArchivoAPlus(const char *nombre);
void cerrarArchivo(FILE *fp);
int leerDesdeArchivo(FILE *fp, const char *formato, ...);
void escribirEnArchivo(FILE *fp, const char *formato, ...);
void escribirEnBuffer(char *buffer, size_t tamanoBuffer, const char *formato, ...);
int FinalArchivo(FILE *archivo);
void eliminarArchivo(const char *nombreArchivo);
void renombrarArchivo(const char *nombreActual, const char *nuevoNombre);
void manejarError(const char *mensaje);

#endif
