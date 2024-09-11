#include "archivos.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

FILE* abrirArchivoW(const char *nombre) {
    FILE *fp = fopen(nombre, "w");
    if (fp == NULL) manejarError("Error al abrir archivo para escritura.");
    return fp;
}

FILE* abrirArchivoR(const char *nombre) {
    FILE *fp = fopen(nombre, "r");
    if (fp == NULL) manejarError("Error al abrir archivo para lectura.");
    return fp;
}

FILE* abrirArchivoA(const char *nombre) {
    FILE *fp = fopen(nombre, "a");
    if (fp == NULL) manejarError("Error al abrir archivo para agregar.");
    return fp;
}

FILE* abrirArchivoWPlus(const char *nombre) {
    FILE *fp = fopen(nombre, "w+");
    if (fp == NULL) manejarError("Error al abrir archivo para escritura.");
    return fp;
}

FILE* abrirArchivoRPlus(const char *nombre) {
    FILE *fp = fopen(nombre, "r+");
    if (fp == NULL) manejarError("Error al abrir archivo para escritura.");
    return fp;
}

FILE* abrirArchivoAPlus(const char *nombre) {
    FILE *fp = fopen(nombre, "a+");
    if (fp == NULL) manejarError("Error al abrir archivo para escritura.");
    return fp;
}

void cerrarArchivo(FILE *fp) {
    if (fp != NULL) fclose(fp);
    else manejarError("El archivo ya está cerrado o es NULL.");
}

void leerDesdeArchivo(FILE *fp, const char *formato, ...) {
    if (fp == NULL) {
        printf("Error: Archivo no abierto para lectura.\n");
        return;
    }

    va_list args;
    va_start(args, formato);
    if (fscanf(fp, formato, args) == EOF) {
        if (feof(fp)) {
            printf("Fin del archivo alcanzado.\n");
        } else {
            printf("Error al leer el archivo.\n");
        }
    }
    va_end(args);
}

void escribirEnArchivo(FILE *fp, const char *formato, ...) {
    va_list args;
    if (fp == NULL) {
        manejarError("Archivo no abierto para escritura.");
        return;
    }
    va_start(args, formato);
    if (vfprintf(fp, formato, args) < 0) manejarError("Error al escribir en el archivo.");
    va_end(args);
}

void escribirEnBuffer(char *buffer, size_t tamanoBuffer, const char *formato, ...) {
    va_list args;
    va_start(args, formato);
    vsnprintf(buffer, tamanoBuffer, formato, args);
    va_end(args);
}

int FinalArchivo(FILE *archivo) {
    return feof(archivo);
}

void eliminarArchivo(const char *nombreArchivo) {
    if (remove(nombreArchivo) == 0) printf("Archivo eliminado correctamente.\n");
    else manejarError("Error al eliminar el archivo");
}

void renombrarArchivo(const char *nombreActual, const char *nuevoNombre) {
    if (rename(nombreActual, nuevoNombre) == 0) printf("Archivo renombrado correctamente.\n");
    else manejarError("Error al renombrar el archivo");
}

void manejarError(const char *mensaje) {
    perror(mensaje);
}
  
