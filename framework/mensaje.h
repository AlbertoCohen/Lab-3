#ifndef _MENSAJE
#define _MENSAJE

typedef struct {
    long long_dest;
    int int_rte;
    int int_evento;
    char char_mensaje[50];
} mensaje;

int creo_id_cola_mensajes(int clave);
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char *rpCharMsg);
int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje *rMsg);
int borrar_mensajes(int id_cola_mensajes);

#endif
