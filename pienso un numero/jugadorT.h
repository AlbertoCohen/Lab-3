#ifndef _JUGADORT
#define _JUGADORT
typedef struct tipo_jugador
{
    int nro_jugador;
    int id_colamensaje;
    int cant_jugadores;
} tjugador;

typedef enum {
    MSG_NADIE,
    MSG_PIENSO,
    MSG_JUGADOR
} Destinos;

typedef enum {
    EVT_NINGUNO,
    EVT_NUMERO,
    EVT_ACERTO,
    EVT_NO_ACERTO,
    EVT_FINALIZAR
} Eventos;


void *ThreadJugador(void *parametro);

#endif
