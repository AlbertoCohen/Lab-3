#ifndef _MEMORIA
#define _MEMORIA

void *creo_memoria(int size, int *r_id_memoria, int clave_base);
void inicializar_memoria(void *ptr_memoria, const char *data, int size);
void leer_memoria(void *ptr_memoria, int size);
void desvincular_memoria(void *memoria);
void eliminar_memoria(int id_memoria);

typedef struct tipo_dato
{
	int iniciador;
} memcop;

#endif
