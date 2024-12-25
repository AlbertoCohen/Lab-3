#ifndef _autosT
#define _autosT
typedef struct tipo_auto
{
    int nro_auto;
    int id_colamensaje;
    int cant_autos;
    int metros_avanzados;
    char marca[30];

} tauto;

typedef enum
{
    MSG_NADIE,
    MSG_PISTA,
    MSG_AUTO
} Destinos;
typedef enum
{
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_METROS,
    EVT_SIGA,
    EVT_BOXES,
    EVT_PISTA,
    EVT_FINALIZAR,
    EVT_FINALIZAR_CARRERA
} Eventos;

void *Threadauto(void *parametro);

#endif
