#ifndef _finalistasT
#define _finalistasT
typedef struct tipo_finalista
{
    int nro_finalista;
    int id_colamensaje;
    int cant_finalistas;
    int puntos;

} tfinalista;

typedef enum
{
    MSG_NADIE,
    MSG_CANCHA,
    MSG_FINALISTA
} Destinos;

typedef enum
{
    EVT_NINGUNO,
    EVT_PUNTO,
    EVT_FUERA,
    EVT_INICIO,
    EVT_SIGA,
    EVT_FINALIZAR

} Eventos;

void *Threadfinalista(void *parametro);

#endif
