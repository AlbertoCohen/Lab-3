#ifndef _lavarropasT
#define _lavarropasT
typedef struct tipo_lavarropa
{
    int nro_lavarropa;
    int id_colamensaje;
    int cant_lavarropas;

} tlavarropa;

typedef enum
{
    MSG_NADIE,
    MSG_MEGARROPA,
    MSG_LAVARROPA
} Destinos;

typedef enum
{
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_LAVADO,
    EVT_LAVA,
    EVT_FINALIZAR,
    EVT_FINALIZAR_LAVADOS
} Eventos;

void *Threadlavarropa(void *parametro);

#endif
