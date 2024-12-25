#ifndef _mosquitosT
#define _mosquitosT
typedef struct tipo_mosquito
{
    int nro_mosquito;
    int id_colamensaje;
    int cant_mosquitos;
    int metros_avanzados;

} tmosquito;

typedef enum
{
    MSG_NADIE,
    MSG_PISTA,
    MSG_MOSQUITO
} Destinos;
typedef enum
{
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_METROS,
    EVT_SIGA,
    EVT_FINALIZAR,
    EVT_FINALIZAR_CARRERA
} Eventos;

void *Threadmosquito(void *parametro);

#endif
