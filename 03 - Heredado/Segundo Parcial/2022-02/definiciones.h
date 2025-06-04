#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#include <pthread.h>

#define CANTIDAD_PATEADORES 5
#define ESPERA_JUGADOR 1000

typedef struct juego
{
    int id_cola_mensajes;
    int nro_jugador;
    int resultado_tiro;
    pthread_mutex_t *mutex;
} t_juego;

typedef enum
{
    MSG_NADIE,    /* 0*/
    MSG_ARQUERO,  /* 1*/
    MSG_PATEADOR  /* 2 Cada hilo le suma uno a este define.*/
} Destinos;

typedef enum
{
    EVT_NINGUNO,   /* 0 */
    EVT_TIRO,      /* 1 */
    EVT_GOL,       /* 2 */
    EVT_PALO,      /* 3 */
    EVT_TRAVESANO, /* 4 */
    EVT_FUERA      /* 5 */
} Eventos;

#endif
