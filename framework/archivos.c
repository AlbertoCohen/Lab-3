#include "archivos.h"
#include "def.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *abrirArchivoW(const char *nombre)
{
    FILE *fp = fopen(nombre, "w");
    if (fp == NULL)
        manejarError("Error al abrir archivo para escritura.");
    return fp;
}

FILE *abrirArchivoR(const char *nombre)
{
    FILE *fp = fopen(nombre, "r");
    if (fp == NULL)
        manejarError("Error al abrir archivo para lectura.");
    return fp;
}

FILE *abrirArchivoA(const char *nombre)
{
    FILE *fp = fopen(nombre, "a");
    if (fp == NULL)
        manejarError("Error al abrir archivo para agregar.");
    return fp;
}

FILE *abrirArchivoWPlus(const char *nombre)
{
    FILE *fp = fopen(nombre, "w+");
    if (fp == NULL)
        manejarError("Error al abrir archivo para escritura.");
    return fp;
}

FILE *abrirArchivoRPlus(const char *nombre)
{
    FILE *fp = fopen(nombre, "r+");
    if (fp == NULL)
        manejarError("Error al abrir archivo para escritura.");
    return fp;
}

FILE *abrirArchivoAPlus(const char *nombre)
{
    FILE *fp = fopen(nombre, "a+");
    if (fp == NULL)
        manejarError("Error al abrir archivo para escritura.");
    return fp;
}

void cerrarArchivo(FILE *fp)
{
    if (fp != NULL)
        fclose(fp);
    else
        manejarError("El archivo ya está cerrado o es NULL.");
}

void leerDesdeArchivo(const char *nombreArchivo, const char *formato, int num_vars, ...)
{
    FILE *fp = fopen(nombreArchivo, "r");
    if (fp == NULL)
    {
        printf("Error: No se pudo abrir el archivo para lectura.\n");
        return;
    }

    char cadena[LARGO];
    if (fgets(cadena, LARGO, fp) == NULL)
    {
        if (feof(fp))
        {
            printf("Fin del archivo alcanzado.\n");
        }
        else
        {
            printf("Error al leer el archivo.\n");
        }
        fclose(fp);
        return;
    }

    if (num_vars > 0)
    {
        va_list args;
        va_start(args, num_vars);

        char *token = strtok(cadena, " ");
        for (int i = 0; i < num_vars && token != NULL; i++)
        {
            void *var = va_arg(args, void *);

            if (strchr(formato, 'd') != NULL)
            {
                *(int *)var = atoi(token);
            }
            else if (strchr(formato, 'f') != NULL)
            {
                *(float *)var = atof(token);
            }
            else if (strchr(formato, 'c') != NULL)
            {
                *(char *)var = token[0];
            }

            token = strtok(NULL, " ");
        }

        va_end(args);
    }
    else
    {
        printf("%s", cadena);
    }
}

void escribirEnArchivo(FILE *fp, const char *formato, ...)
{
    va_list args;
    if (fp == NULL)
    {
        manejarError("Archivo no abierto para escritura.");
        return;
    }
    va_start(args, formato);
    if (vfprintf(fp, formato, args) < 0)
        manejarError("Error al escribir en el archivo.");
    va_end(args);
}

void escribirEnBuffer(char *buffer, size_t tamanoBuffer, const char *formato, ...)
{
    va_list args;
    va_start(args, formato);
    vsnprintf(buffer, tamanoBuffer, formato, args);
    va_end(args);
}

int FinalArchivo(FILE *archivo)
{
    return feof(archivo);
}

void eliminarArchivo(const char *nombreArchivo)
{
    if (remove(nombreArchivo) == 0)
        printf("Archivo eliminado correctamente.\n");
    else
        manejarError("Error al eliminar el archivo");
}

void renombrarArchivo(const char *nombreActual, const char *nuevoNombre)
{
    if (rename(nombreActual, nuevoNombre) == 0)
        printf("Archivo renombrado correctamente.\n");
    else
        manejarError("Error al renombrar el archivo");
}

void manejarError(const char *mensaje)
{
    perror(mensaje);
}
