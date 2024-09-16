#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "archivos.h"
#include "def.h"

/* Función para abrir un archivo con el modo indicado. */
FILE *abrirArchivo(const char *nombre, const char *modo){
    FILE *fp; 
    fp = fopen(nombre, modo);
    if (fp == NULL){
        manejarError("Error al abrir archivo.");
    }
    return fp;
}

/* Función específica para abrir un archivo en modo escritura. */
FILE *abrirArchivoW(const char *nombre){
    return abrirArchivo(nombre, "w");
}

/* Función específica para abrir un archivo en modo lectura. */
FILE *abrirArchivoR(const char *nombre){
    return abrirArchivo(nombre, "r");
}

/* Función específica para abrir un archivo en modo agregar. */
FILE *abrirArchivoA(const char *nombre){
    return abrirArchivo(nombre, "a");
}

FILE* abrirArchivoWPlus(const char *nombre){
    return abrirArchivo(nombre, "w+");
}

FILE* abrirArchivoRPlus(const char *nombre){
    return abrirArchivo(nombre, "r+");
}

FILE* abrirArchivoAPlus(const char *nombre){
    return abrirArchivo(nombre, "a+");
}

/* Función para cerrar un archivo */
void cerrarArchivo(FILE *fp){
    if (fp != NULL){
        fclose(fp);
    }
    else{
        perror("Error: archivo NULL o ya cerrado");
    }
}

/* Función para leer y mostrar un archivo línea por línea. */
void leerTodoElArchivo(FILE *fp){
    char linea[LARGO];  

    while (fgets(linea, LARGO, fp) != NULL){
        printf("%s", linea);
    }

    if (feof(fp)){
        printf("Fin del archivo alcanzado.\n");
    }
    else{
        perror("Error al leer el archivo");
    }
}

/* Función para leer datos específicos desde un archivo con un formato dado. */
void leerDesdeArchivo(const char *nombreArchivo, const char *formato, int num_vars, ...){
    int i;  
    va_list args;
    FILE *fp; 
    char linea[LARGO];  
    char *token; 

    fp = abrirArchivoR(nombreArchivo);
    if (fp == NULL){
        return;
    }

    if (fgets(linea, LARGO, fp) == NULL){
        if (feof(fp)){
            printf("Fin del archivo alcanzado.\n");
        }
        else{
            perror("Error al leer el archivo");
        }
        cerrarArchivo(fp);
        return;
    }

    va_start(args, num_vars);

    token = strtok(linea, " ");
    
    for (i = 0; i < num_vars && token != NULL; i++){
        void *var = va_arg(args, void *);

        switch (formato[i]){
        case 'd':
            *(int *)var = atoi(token);
            break;
        case 'f':
            *(float *)var = atof(token);
            break;
        case 'c':
            *(char *)var = token[0];
            break;
        default:
            perror("Formato no reconocido");
            break;
        }
        token = strtok(NULL, " ");
    }

    va_end(args);
    cerrarArchivo(fp);
}

/* Función para escribir en un archivo con formato variable. */
void escribirEnArchivo(FILE *fp, const char *formato, ...){
    va_list args;
    if (fp == NULL){
        perror("Archivo no abierto para escritura");
        return;
    }

    va_start(args, formato);
    if (vfprintf(fp, formato, args) < 0){
        perror("Error al escribir en el archivo");
    }
    va_end(args);
}

/* Función para escribir en un buffer utilizando sprintf y protegiendo el tamaño del buffer */
void escribirEnBuffer(char *buffer, size_t tamanoBuffer, const char *formato, ...){
    va_list args;
    char *bufferTemporal;  
    int longitudEscrita;

    /* Asignamos dinámicamente el tamaño del buffer temporal */
    bufferTemporal = (char *)malloc(tamanoBuffer * sizeof(char));
    if (bufferTemporal == NULL) {
        perror("Error al asignar memoria para el buffer temporal");
        return;
    }

    va_start(args, formato);

    /* Escribimos el contenido en el buffer temporal */
    longitudEscrita = vsprintf(bufferTemporal, formato, args);

    /* Validamos si el contenido es mayor al tamaño del buffer */
    if (longitudEscrita >= tamanoBuffer){
        printf("Advertencia: se intentó escribir más de lo que el buffer puede contener. Se truncará la salida.\n");
        /* Si es mayor, copiamos solo hasta el tamaño del buffer menos 1 para dejar espacio para '\0' */
        strncpy(buffer, bufferTemporal, tamanoBuffer - 1);
        buffer[tamanoBuffer - 1] = '\0'; /* Nos aseguramos de que esté terminada en null */
    }
    else{
        /* Si la longitud es válida, copiamos todo al buffer original */
        strcpy(buffer, bufferTemporal);
    }

    va_end(args);

    /* Liberamos la memoria asignada dinámicamente */
    free(bufferTemporal);
}

/* Función que comprueba si se ha alcanzado el final de un archivo. */
int finalArchivo(FILE *archivo){
    return feof(archivo);
}

/* Función para eliminar un archivo. */
void eliminarArchivo(const char *nombreArchivo){
    if (remove(nombreArchivo) == 0){
        printf("Archivo eliminado correctamente.\n");
    }
    else{
        perror("Error al eliminar el archivo");
    }
}

/* Función para renombrar un archivo. */
void renombrarArchivo(const char *nombreActual, const char *nuevoNombre){
    if (rename(nombreActual, nuevoNombre) == 0){
        printf("Archivo renombrado correctamente.\n");
    }
    else{
        perror("Error al renombrar el archivo");
    }
}

/* Función para manejar errores y mostrar el mensaje correspondiente (optimizando uso de perror). */
void manejarError(const char *mensaje){
    perror(mensaje);
}
