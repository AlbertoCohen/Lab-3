#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "archivos.h"
#include "def.h"

// Función para abrir un archivo con el modo indicado.
FILE *abrirArchivo(const char *nombre, const char *modo) {
    FILE *fp = fopen(nombre, modo);
    if (fp == NULL) {
        manejarError("Error al abrir archivo.");
    }
    return fp;
}

// Función específica para abrir un archivo en modo escritura.
FILE *abrirArchivoW(const char *nombre) {
    return abrirArchivo(nombre, "w");
}

// Función específica para abrir un archivo en modo lectura.
FILE *abrirArchivoR(const char *nombre) {
    return abrirArchivo(nombre, "r");
}

// Función específica para abrir un archivo en modo agregar.
FILE *abrirArchivoA(const char *nombre) {
    return abrirArchivo(nombre, "a");
}

// Función para cerrar un archivo.
void cerrarArchivo(FILE *fp) {
    if (fp != NULL) {
        fclose(fp);
    } else {
        manejarError("El archivo ya está cerrado o es NULL.");
    }
}

// Función que lee el contenido de un archivo línea por línea y lo imprime en pantalla.
void leerTodoElArchivo(FILE *fp) {
    char linea[LARGO];

    while (fgets(linea, LARGO, fp) != NULL) {
        printf("%s", linea);
    }

    if (feof(fp)) {
        printf("Fin del archivo alcanzado.\n");
    } else {
        manejarError("Error al leer el archivo.");
    }
}

// Función para leer datos específicos desde un archivo con un formato dado.
void leerDesdeArchivo(const char *nombreArchivo, const char *formato, int num_vars, ...) {
    FILE *fp = abrirArchivoR(nombreArchivo);  // Usar la función para abrir en modo lectura.
    if (fp == NULL) {
        return;  // Error ya manejado por `abrirArchivoR`.
    }

    char linea[LARGO];
    if (fgets(linea, LARGO, fp) == NULL) {
        if (feof(fp)) {
            printf("Fin del archivo alcanzado.\n");
        } else {
            manejarError("Error al leer el archivo.");
        }
        cerrarArchivo(fp);
        return;
    }

    if (num_vars > 0) {
        va_list args;
        va_start(args, num_vars);

        char *token = strtok(linea, " ");
        for (int i = 0; i < num_vars && token != NULL; i++) {
            void *var = va_arg(args, void *);

            if (strchr(formato, 'd') != NULL) {
                *(int *)var = atoi(token);
            } else if (strchr(formato, 'f') != NULL) {
                *(float *)var = atof(token);
            } else if (strchr(formato, 'c') != NULL) {
                *(char *)var = token[0];
            }

            token = strtok(NULL, " ");
        }

        va_end(args);
    } else {
        printf("%s", linea);
    }
    cerrarArchivo(fp);  // Cerrar el archivo tras la lectura.
}

// Función para escribir en un archivo utilizando argumentos variables.
void escribirEnArchivo(FILE *fp, const char *formato, ...) {
    if (fp == NULL) {
        manejarError("Archivo no abierto para escritura.");
        return;
    }

    va_list args;
    va_start(args, formato);
    if (vfprintf(fp, formato, args) < 0) {
        manejarError("Error al escribir en el archivo.");
    }
    va_end(args);
}

// Función para escribir en un buffer utilizando formato variable.
void escribirEnBuffer(char *buffer, size_t tamanoBuffer, const char *formato, ...) {
    va_list args;
    va_start(args, formato);
    vsnprintf(buffer, tamanoBuffer, formato, args);  // vsnprintf asegura que no se desborde el buffer.
    va_end(args);
}

// Función que comprueba si se ha alcanzado el final de un archivo.
int FinalArchivo(FILE *archivo) {
    return feof(archivo);
}

// Función para eliminar un archivo.
void eliminarArchivo(const char *nombreArchivo) {
    if (remove(nombreArchivo) == 0) {
        printf("Archivo eliminado correctamente.\n");
    } else {
        manejarError("Error al eliminar el archivo");
    }
}

// Función para renombrar un archivo.
void renombrarArchivo(const char *nombreActual, const char *nuevoNombre) {
    if (rename(nombreActual, nuevoNombre) == 0) {
        printf("Archivo renombrado correctamente.\n");
    } else {
        manejarError("Error al renombrar el archivo");
    }
}

// Función para manejar errores y mostrar el mensaje correspondiente.
void manejarError(const char *mensaje) {
    perror(mensaje);
}
