#ifndef _clienteT
#define _clienteT
typedef struct tipo_cliente
{
    int nro_cliente;
    int id_colamensaje;
    int cant_clientes;
} tcliente;

typedef enum
{
    MSG_NADIE,
    MSG_BANCO,
    MSG_CLIENTE
} Destinos;

typedef enum
{
    EVT_NINGUNO,
    EVT_CONSULTA_SALDO,
    EVT_DEPOSITO,
    EVT_EXTRACCION,
    EVT_RTA_SALDO,
    EVT_RTA_SALDO_NOK,
    EVT_RTA_DEPOSITO_OK,
    EVT_RTA_DEPOSITO_NOK,
    EVT_RTA_EXTRACCION_OK,
    EVT_RTA_EXTRACCION_NOK,
    EVT_FINALIZAR
}Eventos;

void *Threadcliente(void *parametro);

#endif
